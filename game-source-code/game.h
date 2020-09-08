#ifndef GAME_H
#define GAME_H

#include "state.h"

class Game
{
    public:
        Game(int gameWidth,int gameHeight);
        virtual ~Game();
        // Game loop
        void run();
        void update();
        void render();
        void updateEvents();
    protected:

    private:
        // Initialise window
        void initWindow();
        // Variables
        std::shared_ptr<sf::RenderWindow> window;
        sf::Event event;
        int gameWidth_;
        int gameHeight_;

};

#endif // GAME_H
