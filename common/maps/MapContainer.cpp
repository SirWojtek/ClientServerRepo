
#include "MapContainer.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace maps
{

MapContainer::MapContainer(std::string mapFolder) :
    tmxMapLoader_(mapFolder),
    console_("MapContainer") {}

bool MapContainer::loadMap(const std::string filename)
{
    bool result = tmxMapLoader_.Load(filename);
    loadMapRenderTexture();

    console_.info << "Map loaded";
    return result;
}

void MapContainer::loadMapRenderTexture()
{
    sf::Vector2u mapSize = tmxMapLoader_.GetMapSize();

    mapTexture_.create(mapSize.x, mapSize.y);
    mapTexture_.clear();
    mapTexture_.draw(tmxMapLoader_);
    mapTexture_.display();
}

const sf::Texture& MapContainer::getSfmlMap() const
{
    return mapTexture_.getTexture();
}

void MapContainer::updateViewport(const sf::FloatRect& area)
{
    std::lock_guard<std::mutex> lock(loaderMutex_);
    tmxMapLoader_.UpdateQuadTree(area);
}

std::vector<tmx::MapObject*> MapContainer::getCollisionObjects(
        const sf::FloatRect& spriteArea)
{
    std::lock_guard<std::mutex> lock(loaderMutex_);
    return tmxMapLoader_.QueryQuadTree(spriteArea);
}

}
