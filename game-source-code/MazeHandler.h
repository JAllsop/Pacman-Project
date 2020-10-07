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

    void loadLevel(); //changing level possible

    void updatePlayer();
    void updateAI(int enemyNum);

    bool getPlayerState();
    bool allFruitsEaten();

    void render();// This is part of the display PS: change later

    //enemy movement with Collision
    void enemyMoveDown();
    void enemyMoveUp();
    void enemyMoveRight();
    void enemyMoveLeft();

    //player movement with Collision
    void playerMoveDown();
    void playerMoveUp();
    void playerMoveRight();
    void playerMoveLeft();

    shared_ptr<Maze> getMaze();

protected:

private:
    //player collision check
    shared_ptr<Entity> playerCollision();
    bool resolveCollision();
    //enemy collision check
    shared_ptr<Entity> enemyCollision(shared_ptr<Enemy> enemy);

    shared_ptr<sf::RenderWindow> window_;

    shared_ptr<Maze> maze_;

    vector<shared_ptr<Wall>> walls_;
    vector<shared_ptr<Key>> keys_;
    vector<shared_ptr<Door>> doors_;
    vector<shared_ptr<PowerPellet>> powerPellets_;
    vector<shared_ptr<Fruit>> fruits_;
    vector<shared_ptr<Enemy>> enemies_;
    shared_ptr<Player> player_;

    // Random rumber gen
    int random;

    //Direction indicators
    bool isPlayerDead;
    bool isAllFruitsEaten;

    //counters
    int keys;
    int fruits;
    int powerPellets;

    //SfML
    sf::Time enemySpeed1;
    sf::Time enemySpeed2;
    sf::Time playerSpeed;
    sf::Time powerPelletTime;
    sf::Clock enemyClock1;
    sf::Clock enemyClock2;
    sf::Clock playerClock;
    sf::Clock powerPelletClock;

};

#endif // MAZEHANDLER_H
