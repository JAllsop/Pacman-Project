#include "GameState.h"

GameState::GameState(shared_ptr<sf::RenderWindow> window) : State(), window_{window}
{
    //construct handlers
    mazeHandler_ = make_shared<MazeHandler> (window);
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
    mazeHandler_->run();
    //boardhandler->run();
    //playerHandler_->run();
    //enemyHandler->run();
    //fruitHandler->run();
    //keyHandler->run();

}

bool GameState::isStateEnd()
{
    if (mazeHandler_->getPlayerState() == true)
    {
        return true;
    }
    return false;
}
