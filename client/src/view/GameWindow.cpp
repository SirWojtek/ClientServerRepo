
#include "GameWindow.hpp"
#include "IModelPainter.hpp"

#include <thread>
#include <memory>
#include <atomic>

#include <SFML/Graphics/RenderWindow.hpp>

#include "EventListener.hpp"

namespace view
{

GameWindow::GameWindow(ModelPainterPtr modelPainter) :
    modelPainter_(modelPainter),
    exit_(false),
    console_("GameWindow") {}


void GameWindow::startWindowThread()
{
    windowThread_.reset(new std::thread(&GameWindow::windowMain, this));
    console_.info << "Window thread started";
}

void GameWindow::tearDown()
{
    if (windowThread_ && windowThread_->joinable())
    {
        exit_.store(true);
        windowThread_->join();
        console_.info << "Window thread joined";
    }
}

void GameWindow::windowMain()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    console_.info << "Window creation OK";

    while (!exit_)
    {
        pumpEvents(window);
        display(window);
    }
}

void GameWindow::pumpEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            console_.debug << "Received close event";
            exit_.store(true);
        }

        EventListener::receiveEvent(event);
    }
}

void GameWindow::display(sf::RenderWindow& window)
{
    window.clear();

    modelPainter_->paint(window);

    window.display();
}

}