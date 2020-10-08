#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include "player.h"
#include "maze.h"

class PlayerHandler
{
    public:
        PlayerHandler(shared_ptr<Maze> maze);
        virtual ~PlayerHandler();
        bool run();
        bool update();
        void render(shared_ptr<sf::RenderWindow> window);

        //movement
        void playerMoveDown();
        void playerMoveUp();
        void playerMoveRight();
        void playerMoveLeft();

    private:
        shared_ptr<Entity> playerCollision();
        bool resolveCollision();

        shared_ptr<sf::RenderWindow> window_;

        vector<shared_ptr<Wall>> walls_;
        vector<shared_ptr<Key>> keys_;
        vector<shared_ptr<Door>> doors_;
        vector<shared_ptr<PowerPellet>> powerPellets_;
        vector<shared_ptr<Fruit>> fruits_;
        vector<shared_ptr<Enemy>> enemies_;
        shared_ptr<Player> player_;

        sf::Clock playerClock;
        sf::Time playerSpeed;

        sf::Time powerPelletTime;
        sf::Clock powerPelletClock;

        bool isPlayerDead;
        int keys;
        int fruits;
        int maxFruits_;
        int powerPellets;
};

#endif // PLAYERHANDLER_H
