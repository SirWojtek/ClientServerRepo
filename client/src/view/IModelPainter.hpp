#ifndef IMODEL_PAINTER_HPP_
#define IMODEL_PAINTER_HPP_

#include <memory>

namespace sf
{
class RenderWindow;
}

namespace view
{

class IModelPainter
{
public:
    virtual void paint(sf::RenderWindow& window) = 0;
};
using ModelPainterPtr = std::shared_ptr<IModelPainter>;

}

#endif  // IMODEL_PAINTER_HPP_
