
#include "ModelPainter.hpp"

#include "client/src/model/IObjectsFacade.hpp"

#include "common/maps/IMapContainer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

namespace view
{

const unsigned ModelPainter::playerSize = 25;
const sf::Color ModelPainter::playerColor = sf::Color(100, 250, 50);
const sf::Vector2f ModelPainter::viewportSize = sf::Vector2f(800, 600);

ModelPainter::ModelPainter(model::ObjectsFacadePtr modelFacade) :
    modelFacade_(modelFacade)
    {
        view_.setSize(viewportSize);
    }

void ModelPainter::paint(sf::RenderWindow& window)
{
    model::ObjectPtr playerObj = modelFacade_->getPlayerObject();

    printMap(window);
    printPlayer(window, playerObj);
    setCamera(window, playerObj);
}

void ModelPainter::printMap(sf::RenderWindow& window) const
{
    maps::MapContainerPtr currentMap = modelFacade_->getCurrentMap();
    sf::Drawable& sfmlMap = currentMap->getSfmlMap();

    window.draw(sfmlMap);
}

void ModelPainter::printPlayer(sf::RenderWindow& window, const model::ObjectPtr& playerObj)
{
    sf::RectangleShape player(sf::Vector2f(playerSize, playerSize));

    player.setPosition(playerObj->position.x, playerObj->position.y);
    player.setFillColor(playerColor);

    window.draw(player);
}

void ModelPainter::setCamera(sf::RenderWindow& window, const model::ObjectPtr& playerObj)
{
    view_.setCenter(sf::Vector2f(playerObj->position.x, playerObj->position.y));
    window.setView(view_);
}

}
