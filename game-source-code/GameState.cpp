#include "GameState.h"

GameState::GameState(shared_ptr<sf::RenderWindow> window) : State(), window_{window}
{
    playerHandler_ =  make_shared<PlayerHandler>(window_);
    //ctor
}

GameState::~GameState()
{
    //dtor
}

void GameState::run()
{
    update();
}

void GameState::loadAssets()
{
    // loads the player assets
}

void GameState::update()
{
    //boardhandler->run();
    playerHandler_->run();
    //enemyHandler->run();
    //fruitHandler->run();
    //keyHandler->run();

}
