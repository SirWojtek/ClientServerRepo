#ifndef MAP_CONTAINER_HPP_
#define MAP_CONTAINER_HPP_

#include "IMapContainer.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>

#include "common/utilities/Console.hpp"


namespace tmx
{
class MapLoader;
}

namespace maps
{

class MapContainer : public IMapContainer
{
public:
    MapContainer(std::string mapFolder);

    virtual bool loadMap(const std::string filename);
    virtual sf::Drawable& getSfmlMap() const;

private:
    std::shared_ptr<tmx::MapLoader> tmxMapLoader_;
    Console console_;
};

}

#endif  // MAP_CONTAINER_HPP_