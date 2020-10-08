#ifndef MAZEHANDLER_H
#define MAZEHANDLER_H

#include "maze.h"
#include "PlayerHandler.h"
#include "EnemyHandler.h"

class MazeHandler
{
public:
    MazeHandler(shared_ptr<sf::RenderWindow> window);
    virtual ~MazeHandler();
    void run();
    void render();

    void updatePlayer();
    void updateAI(int enemyNum);

    bool getPlayerState();
    bool allFruitsEaten();
    shared_ptr<Maze> getMaze();

protected:

private:
    shared_ptr<sf::RenderWindow> window_;

    shared_ptr<Maze> maze_;

    //handlers
    shared_ptr<PlayerHandler> playerHandler_;
    shared_ptr<EnemyHandler> enemyHandler_;

    int random;

    bool isPlayerDead;
    bool isFruitFinished;

    sf::Time enemySpeed1;
    sf::Time enemySpeed2;

    sf::Clock enemyClock1;
    sf::Clock enemyClock2;
};

#endif // MAZEHANDLER_H
