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

    void updatePlayer();
    void updateAI();
    bool getPlayerState();
    bool allFruitsEaten();

    void render();// This is part of the display PS: change later

    //shared_ptr<Entity> collision(shared_ptr<Entity> movingEntity, vector<shared_ptr<Entity>> testEntities);
    //cannot pass superclass vector of pointers to base class class vector of pointers
    shared_ptr<Entity> playerCollision(shared_ptr<Player> player);
    shared_ptr<Entity> enemyCollision(shared_ptr<Enemy> enemy);
    bool resolveCollision(shared_ptr<Player> Player);

    void playerMoveDown();
    void playerMoveUp();
    void playerMoveRight();
    void playerMoveLeft();

    shared_ptr<Maze> getMaze();

protected:

private:
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
    sf::Time milli1;
    sf::Time milli2;
    sf::Time milli3;
    sf::Clock clock1;
    sf::Clock clock2;
    sf::Clock clock3;
    sf::Time elapsed1;
    sf::Time elapsed2;
    sf::Time elapsed3;


};

#endif // MAZEHANDLER_H
