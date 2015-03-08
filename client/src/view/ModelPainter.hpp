#ifndef MODEL_PAINTER_HPP_
#define MODEL_PAINTER_HPP_

#include "IModelPainter.hpp"

#include "client/src/model/IObjectsFacade.hpp"



namespace sf
{
class RenderWindow;
class Color;
}

namespace view
{

class ModelPainter : public IModelPainter
{
public:
    ModelPainter(model::ObjectsFacadePtr modelFacade);

    virtual void paint(sf::RenderWindow& window);

private:
    void printPlayer(sf::RenderWindow& window);

    model::ObjectsFacadePtr modelFacade_;

    static const unsigned playerSize;
    static const sf::Color playerColor;
};

}

#endif  // MODEL_PAINTER_HPP_
