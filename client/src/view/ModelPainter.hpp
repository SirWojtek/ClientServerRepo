#ifndef MODEL_PAINTER_HPP_
#define MODEL_PAINTER_HPP_

#include "IModelPainter.hpp"

#include "client/src/model/IObjectsFacade.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>


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
    void printMap(sf::RenderWindow& window, const maps::MapContainerPtr& currentMap);
    void printPlayer(sf::RenderWindow& window, const model::ObjectPtr& playerObj);
    void setCamera(sf::RenderWindow& window, const model::ObjectPtr& playerObj);
    void updateViewportArea(maps::MapContainerPtr& map, const model::ObjectPtr& playerObj);

    model::ObjectsFacadePtr modelFacade_;
    sf::View view_;

    static const sf::Color playerColor;
    static const sf::Vector2f viewportSize;
};

}

#endif  // MODEL_PAINTER_HPP_
