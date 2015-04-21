#ifndef MAP_CONTAINER_HPP_
#define MAP_CONTAINER_HPP_

#include "IMapContainer.hpp"

#include <memory>
#include <string>
#include <vector>
#include <mutex>

#include <tmx/MapLoader.h>
#include <SFML/Graphics/RenderTexture.hpp>

#include "common/utilities/Console.hpp"

namespace sf
{
class Texture;
};

namespace maps
{

class MapContainer : public IMapContainer
{
public:
    MapContainer(std::string mapFolder);

    virtual bool loadMap(const std::string filename);
    virtual const sf::Texture& getSfmlMap() const;
    virtual void updateViewport(const sf::FloatRect& area);
    virtual std::vector<tmx::MapObject*> getCollisionObjects(
        const sf::FloatRect& spriteArea);

private:
    void loadMapRenderTexture();

    tmx::MapLoader tmxMapLoader_;
    std::mutex loaderMutex_;
    sf::RenderTexture mapTexture_;
    Console console_;
};

}

#endif  // MAP_CONTAINER_HPP_
