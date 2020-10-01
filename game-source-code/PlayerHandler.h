#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include "player.h"
#include "controller.h"
#include "maze.h"

class PlayerHandler
{
    public:
        PlayerHandler(shared_ptr<sf::RenderWindow> window, shared_ptr<Entity> player);
        virtual ~PlayerHandler();
        void run();
        void update();

    private:
        shared_ptr<Entity> player_;
        shared_ptr<sf::RenderWindow> window_;
        shared_ptr<Controller> controller_;
        shared_ptr<Maze> maze_;
};

#endif // PLAYERHANDLER_H
