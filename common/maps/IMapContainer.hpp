#ifndef IMAP_CONTAINER_HPP_
#define IMAP_CONTAINER_HPP_

#include <memory>

namespace sf
{
class Texture;
}

namespace maps
{

class IMapContainer
{
public:
    virtual bool loadMap(const std::string filename) = 0;
    virtual const sf::Texture& getSfmlMap() const = 0;
};
using MapContainerPtr = std::shared_ptr<IMapContainer>;

}

#endif  // IMAP_CONTAINER_HPP_