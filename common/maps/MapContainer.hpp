#ifndef MAP_CONTAINER_HPP_
#define MAP_CONTAINER_HPP_

#include "IMapContainer.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/RenderTexture.hpp>

#include "common/utilities/Console.hpp"


namespace tmx
{
class MapLoader;
class Texture;
}

namespace maps
{

class MapContainer : public IMapContainer
{
public:
    MapContainer(std::string mapFolder);

    virtual bool loadMap(const std::string filename);
    virtual const sf::Texture& getSfmlMap() const;

private:
    void loadMapRenderTexture();

    std::shared_ptr<tmx::MapLoader> tmxMapLoader_;
    sf::RenderTexture mapTexture_;
    Console console_;
};

}

#endif  // MAP_CONTAINER_HPP_