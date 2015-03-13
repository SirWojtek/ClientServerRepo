
#include "MapContainer.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <tmx/MapLoader.h>

namespace maps
{

MapContainer::MapContainer(std::string mapFolder) :
    tmxMapLoader_(std::make_shared<tmx::MapLoader>(mapFolder)),
    console_("MapContainer") {}

bool MapContainer::loadMap(const std::string filename)
{
    bool result = tmxMapLoader_->Load(filename);
    console_.info << "Map loaded";
    return result;
}

sf::Drawable& MapContainer::getSfmlMap() const
{
    return *tmxMapLoader_;
}

}
