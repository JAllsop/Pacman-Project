#include "MazeHandler.h"

MazeHandler::MazeHandler(shared_ptr<sf::RenderWindow> window) : window_{window}, isPlayerDead{false}, isFruitFinished{false}
{
    // Objects
    maze_ = make_shared<Maze>();
    playerHandler_ = make_shared<PlayerHandler>(maze_);
    enemyHandler_ = make_shared<EnemyHandler>(maze_);
}

MazeHandler::~MazeHandler()
{
    //dtor
}

void MazeHandler::run()
{
    if(isPlayerDead == false)
    {
        enemyHandler_->run();
        auto [state, fruit] = playerHandler_->run();
        isPlayerDead = state;
        isFruitFinished = fruit;
    }
    render();
}

void MazeHandler::render()
{
    playerHandler_->render(window_);
}

shared_ptr<Maze> MazeHandler::getMaze()
{
    return maze_;
}

bool MazeHandler::getPlayerState()
{
    return isPlayerDead;
}

bool MazeHandler::allFruitsEaten()
{
    return isFruitFinished;
}
