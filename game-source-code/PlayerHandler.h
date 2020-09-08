#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include "player.h"
//#include "controller.h"

class PlayerHandler
{
    public:
        PlayerHandler(shared_ptr<sf::RenderWindow> window);
        virtual ~PlayerHandler();
        void run();
        void update();
        void render();

    private:
        shared_ptr<Player> player_;
        shared_ptr<sf::RenderWindow> window_;
        //shared_ptr<Controller> controller_;
};

#endif // PLAYERHANDLER_H
