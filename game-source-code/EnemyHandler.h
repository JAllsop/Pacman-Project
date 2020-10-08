#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include "enemy.h"
#include "maze.h"

class EnemyHandler
{
    public:
        EnemyHandler(shared_ptr<Maze> maze);
        virtual ~EnemyHandler();
        void run();

        bool enemyMoveDown(vector<shared_ptr<Enemy>>::iterator i);
        bool enemyMoveUp(vector<shared_ptr<Enemy>>::iterator i);
        bool enemyMoveRight(vector<shared_ptr<Enemy>>::iterator i);
        bool enemyMoveLeft(vector<shared_ptr<Enemy>>::iterator i);

    protected:

    private:
        void update(int enemyNum);

        shared_ptr<Entity> enemyCollision(shared_ptr<Enemy> enemy);

        shared_ptr<Player> player_;
        vector<shared_ptr<Wall>> walls_;
        vector<shared_ptr<Door>> doors_;
        vector<shared_ptr<Enemy>> enemies_;

        sf::Time enemySpeed1;
        sf::Time enemySpeed2;

        sf::Clock enemyClock1;
        sf::Clock enemyClock2;

        int random;
};

#endif // ENEMYHANDLER_H
