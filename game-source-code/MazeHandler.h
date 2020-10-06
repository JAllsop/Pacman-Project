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
    void draw();

    shared_ptr<Entity> collision(shared_ptr<Entity> movingEntity, const string type);
    shared_ptr<Entity> playerCollision(shared_ptr<Player> player);
    shared_ptr<Entity> enemyCollision(shared_ptr<Enemy> enemy);
    bool resolveCollision(shared_ptr<Player> Player);

    void playerMoveDown();
    void playerMoveUp();
    void playerMoveRight();
    void playerMoveLeft();

    shared_ptr<Maze> getMaze();


    //void setUpPlayer();
    //void setUpEnemy();
    //vector<vector<shared_ptr<Entity>>> getEntities();
    //vector<vector<char>> getCharMaze();
    //int getEnemyInitialX();
    //int getEnemyInitialY();

protected:

private:

    shared_ptr<Maze> maze_;
    /*
    //Containers
    vector<vector<shared_ptr<Entity>>> m_;
    vector<vector<char>> mChar_;
    //Handlers
    shared_ptr<PlayerHandler> playerHandler_;
    shared_ptr<EnemyHandler> enemyHandler_;
    /*
    //Window
    //Keeps track of char vector
    //int playerX;
    //int playerY;
    //int enemyX;
    //int enemyY;
    // Starting Co-ord of Moving Entities
    int eEntityX;
    int eEntityY;
    int pEntityX;
    int pEntityY;
    float ePosX;
    float ePosY;
    */
    // Random rumber gen
    int random;
    //Direction indicators
    bool isPlayerDead;
    bool isAllFruitsEaten;
    //counters
    int keys;
    int fruits;
    int powerPellet;
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

    shared_ptr<sf::RenderWindow> window_;
};

#endif // MAZEHANDLER_H
