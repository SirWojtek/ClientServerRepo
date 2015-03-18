#ifndef MAP_CONTAINER_HPP_
#define MAP_CONTAINER_HPP_

#include "IMapContainer.hpp"

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "common/utilities/Console.hpp"

namespace sf
{
class Texture;
};

namespace tmx
{
class MapLoader;
class MapObject;
}

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
        const sf::FloatRect& spriteArea) const;

private:
    void loadMapRenderTexture();

    std::shared_ptr<tmx::MapLoader> tmxMapLoader_;
    sf::RenderTexture mapTexture_;
    Console console_;
};

}

#endif  // MAP_CONTAINER_HPP_
