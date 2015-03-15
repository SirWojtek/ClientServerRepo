
#include "MapContainer.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include <tmx/MapLoader.h>

namespace maps
{

MapContainer::MapContainer(std::string mapFolder) :
    tmxMapLoader_(std::make_shared<tmx::MapLoader>(mapFolder)),
    console_("MapContainer") {}

bool MapContainer::loadMap(const std::string filename)
{
    bool result = tmxMapLoader_->Load(filename);
    loadMapRenderTexture();

    console_.info << "Map loaded";
    return result;
}

void MapContainer::loadMapRenderTexture()
{
    sf::Vector2u mapSize = tmxMapLoader_->GetMapSize();

    mapTexture_.create(mapSize.x, mapSize.y);
    mapTexture_.clear();
    mapTexture_.draw(*tmxMapLoader_);
    mapTexture_.display();
}

const sf::Texture& MapContainer::getSfmlMap() const
{
    return mapTexture_.getTexture();
}

void MapContainer::updateViewport(const sf::FloatRect& area)
{
    tmxMapLoader_->UpdateQuadTree(area);
}

std::vector<tmx::MapObject*> MapContainer::getCollisionObjects(
        const sf::FloatRect& spriteArea) const
{
    return tmxMapLoader_->QueryQuadTree(spriteArea);
}

}
