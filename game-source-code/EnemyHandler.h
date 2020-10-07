#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include "enemy.h"
#include "maze.h"

class EnemyHandler
{
    public:
        EnemyHandler(vector<vector<shared_ptr<Entity>>> mazeE, vector<vector<char>>& mazeC,bool& isPlayerD, int& pP, int pX, int pY);
        virtual ~EnemyHandler();
        void run();
        void update();

    protected:

    private:
    //Functions
       void setup();
    void up(bool& hasMoved);
    void down(bool& hasMoved);
    void left(bool& hasMoved);
    void right(bool& hasMoved);
    bool isEdable();
    void checkPlayerCollision();
    void reset();
    void changeColorState();
    //Containers
    vector<vector<shared_ptr<Entity>>> m_;
    vector<vector<char>> mChar_;
    //Add some private functions
    int playerX;
    int playerY;
    int enemyX;
    int enemyY;
    // Keep track of enetities
    int eEntityX;
    int eEntityY;
    float ePosX;
    float ePosY;
    // Random rumber gen
    int random;

    int powerPellet;
    bool isPlayerDead;
};

#endif // ENEMYHANDLER_H
