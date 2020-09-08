#include "game.h"

Game::Game(int gameWidth, int gameHeight):gameWidth_{gameWidth}, gameHeight_{gameHeight}
{
    initWindow();
}

Game::~Game()
{
    //dtor
}

// Game loop
void Game::run()
{
    while(window->isOpen()){
        update();
        render();
    }
}

void Game::update()
{
    updateEvents();
}

void Game::render()
{
    window->clear();

    // Render stuff

    window->display();

}

void Game::updateEvents()
{
    while(window->pollEvent(event)) {
	   if(event.type == sf::Event::Closed)
       {
           window->close();
       }
	}
}
// Initialise window
void Game::initWindow()
{
    window = make_shared<sf::RenderWindow>(sf::VideoMode(gameWidth_, gameHeight_), "SFML Pacman");
    window->setVerticalSyncEnabled(true);
}
