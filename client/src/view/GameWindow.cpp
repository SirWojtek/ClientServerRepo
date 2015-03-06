
#include "GameWindow.hpp"

#include <thread>
#include <memory>
#include <atomic>

#include <SFML/Window.hpp>

#include "EventListener.hpp"

namespace view
{

GameWindow::GameWindow() :
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
        console_.debug << "Window thread joined";
    }
}

void GameWindow::windowMain()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");

    while (!exit_)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                exit_.store(true);
            }

            EventListener::receiveEvent(event);
        }
    }
}

}