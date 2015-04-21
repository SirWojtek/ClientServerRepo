
#include "ModelPainter.hpp"

#include "client/src/model/IObjectsFacade.hpp"

#include "common/maps/IMapContainer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
class Texture;
}

namespace view
{

const sf::Color ModelPainter::playerColor = sf::Color(100, 250, 50);
const sf::Vector2f ModelPainter::viewportSize = sf::Vector2f(400, 300);

ModelPainter::ModelPainter(model::ObjectsFacadePtr modelFacade) :
    modelFacade_(modelFacade)
    {
        view_.setSize(viewportSize);
    }

void ModelPainter::paint(sf::RenderWindow& window)
{
    model::ObjectPtr playerObj = modelFacade_->getPlayerObject();
    maps::IMapContainer& currentMap = modelFacade_->getCurrentMap();

    printMap(window, currentMap);
    printPlayer(window, playerObj);
    setCamera(window, playerObj);
    updateViewportArea(currentMap, playerObj);
}

void ModelPainter::printMap(sf::RenderWindow& window, maps::IMapContainer& currentMap)
{
    sf::Sprite mapSprite(currentMap.getSfmlMap());
    window.draw(mapSprite);
}

void ModelPainter::printPlayer(sf::RenderWindow& window, const model::ObjectPtr& playerObj)
{
    sf::RectangleShape player(sf::Vector2f(playerObj->size, playerObj->size));

    player.setPosition(playerObj->position.x, playerObj->position.y);
    player.setFillColor(playerColor);

    window.draw(player);
}

void ModelPainter::setCamera(sf::RenderWindow& window, const model::ObjectPtr& playerObj)
{
    view_.setCenter(sf::Vector2f(playerObj->position.x, playerObj->position.y));
    window.setView(view_);
}

void ModelPainter::updateViewportArea(maps::IMapContainer& map,
    const model::ObjectPtr& playerObj)
{
    sf::FloatRect viewportArea;

    viewportArea.left = playerObj->position.x - (viewportSize.x / 2);
    viewportArea.top = playerObj->position.y - (viewportSize.y / 2);
    viewportArea.width = viewportSize.x;
    viewportArea.height = viewportSize.y;

    map.updateViewport(viewportArea);
}

}
