#include "MazeHandler.h"

MazeHandler::MazeHandler(shared_ptr<sf::RenderWindow> window) : window_{window}, isPlayerDead{false}, isFruitFinished{false}
{
    init("resources/maze.txt");
}

MazeHandler::~MazeHandler()
{
    //dtor
}

void MazeHandler::init(string level)
{
    maze_ = make_shared<Maze>(level);
    playerHandler_ = make_shared<PlayerHandler>(maze_);
    enemyHandler_ = make_shared<EnemyHandler>(maze_);
}

void MazeHandler::run()
{
    auto [state, fruit] = playerHandler_->run();
    isPlayerDead = state;
    isFruitFinished = fruit;
    isPlayerDead = isPlayerDead | enemyHandler_->run();
    render();
}

void MazeHandler::render()
{
    playerHandler_->render(window_);
}

shared_ptr<PlayerHandler> MazeHandler::getPlayerHandler()
{
    return playerHandler_;
}

shared_ptr<EnemyHandler> MazeHandler::getEnemyHandler()
{
    return enemyHandler_;
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
