#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include "enemy.h"
#include "maze.h"

class EnemyHandler
{
    public:
        EnemyHandler(shared_ptr<Maze> maze);
        virtual ~EnemyHandler();
        void update();

    protected:

    private:

};

#endif // ENEMYHANDLER_H
