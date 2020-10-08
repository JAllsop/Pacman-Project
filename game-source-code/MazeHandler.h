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

    void render();// This is part of the display (move to presentation layer)

    //enemy movement with Collision (move to handler)
    bool enemyMoveDown(vector<shared_ptr<Enemy>>::iterator i);
    bool enemyMoveUp(vector<shared_ptr<Enemy>>::iterator i);
    bool enemyMoveRight(vector<shared_ptr<Enemy>>::iterator i);
    bool enemyMoveLeft(vector<shared_ptr<Enemy>>::iterator i);

    //player movement with Collision (move to handler)
    void playerMoveDown();
    void playerMoveUp();
    void playerMoveRight();
    void playerMoveLeft();

    shared_ptr<Maze> getMaze();

protected:

private:
    //player collision check (move to handler)
    shared_ptr<Entity> playerCollision();
    bool resolveCollision();

    //enemy collision check (move to handler)
    shared_ptr<Entity> enemyCollision(shared_ptr<Enemy> enemy);

    shared_ptr<sf::RenderWindow> window_;

    shared_ptr<Maze> maze_;

    //handlers
    shared_ptr<PlayerHandler> playerHandler_;
    shared_ptr<EnemyHandler> enemyHandler_;
    /*
    //just needed for handlers???
    vector<shared_ptr<Wall>> walls_;
    vector<shared_ptr<Key>> keys_;
    vector<shared_ptr<Door>> doors_;
    vector<shared_ptr<PowerPellet>> powerPellets_;
    vector<shared_ptr<Fruit>> fruits_;
    vector<shared_ptr<Enemy>> enemies_;
    shared_ptr<Player> player_;
    */
    // Random rumber gen
    int random;

    //Direction indicators
    bool isPlayerDead;
    bool isAllFruitsEaten;

    //counters
    //int keys;
    //int fruits;
    //int powerPellets;

    //SfML
    sf::Time enemySpeed1;
    sf::Time enemySpeed2;

    sf::Clock enemyClock1;
    sf::Clock enemyClock2;
};

#endif // MAZEHANDLER_H
