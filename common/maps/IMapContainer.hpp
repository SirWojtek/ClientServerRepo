#ifndef IMAP_CONTAINER_HPP_
#define IMAP_CONTAINER_HPP_

#include <memory>

#include <SFML/Graphics/Drawable.hpp>

namespace maps
{

class IMapContainer
{
public:
    virtual bool loadMap(const std::string filename) = 0;
    virtual sf::Drawable& getSfmlMap() const = 0;
};
using MapContainerPtr = std::shared_ptr<IMapContainer>;

}

#endif  // IMAP_CONTAINER_HPP_