#ifndef IMAP_CONTAINER_HPP_
#define IMAP_CONTAINER_HPP_

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics/Rect.hpp>

namespace sf
{
class Texture;
}

namespace tmx
{
class MapObject;
};

namespace maps
{

class IMapContainer
{
public:
    virtual bool loadMap(const std::string filename) = 0;
    virtual const sf::Texture& getSfmlMap() const = 0;
    virtual void updateViewport(const sf::FloatRect& area) = 0;
    virtual std::vector<tmx::MapObject*> getCollisionObjects(
        const sf::FloatRect& spriteArea) = 0;
};
using MapContainerPtr = std::unique_ptr<IMapContainer>;

}

#endif  // IMAP_CONTAINER_HPP_