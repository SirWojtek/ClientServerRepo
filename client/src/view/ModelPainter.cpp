
#include "ModelPainter.hpp"

#include "client/src/model/IObjectsFacade.hpp"

#include "common/maps/IMapContainer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace view
{

const unsigned ModelPainter::playerSize = 25;
const sf::Color ModelPainter::playerColor = sf::Color(100, 250, 50);

ModelPainter::ModelPainter(model::ObjectsFacadePtr modelFacade) :
    modelFacade_(modelFacade) {}

void ModelPainter::paint(sf::RenderWindow& window)
{
    printMap(window);
    printPlayer(window);
}

void ModelPainter::printMap(sf::RenderWindow& window) const
{
    maps::MapContainerPtr currentMap = modelFacade_->getCurrentMap();
    sf::Drawable& sfmlMap = currentMap->getSfmlMap();

    window.draw(sfmlMap);
}

void ModelPainter::printPlayer(sf::RenderWindow& window)
{
    sf::RectangleShape player(sf::Vector2f(playerSize, playerSize));
    model::ObjectPtr playerObj = modelFacade_->getPlayerObject();

    player.setPosition(playerObj->position.x, playerObj->position.y);
    player.setFillColor(playerColor);

    window.draw(player);
}

}
