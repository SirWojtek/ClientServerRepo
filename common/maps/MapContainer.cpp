
#include "MapContainer.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <tmx/MapLoader.h>

namespace maps
{

MapContainer::MapContainer(std::string mapFolder) :
    tmxMapLoader_(std::make_shared<tmx::MapLoader>(mapFolder)) {}

bool MapContainer::loadMap(const std::string filename)
{
    return tmxMapLoader_->Load(filename);
}

sf::Drawable& MapContainer::getSfmlMap() const
{
    return *tmxMapLoader_;
}

}
