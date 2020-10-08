#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "state.h"
#include "MazeHandler.h"

class GameState : public State
{
    public:
        GameState(shared_ptr<sf::RenderWindow> window);
        virtual ~GameState();
        // This will run the state
        virtual void run();
        // loads assets
        virtual void loadAssets();
        // Gets the logic for the entities
        virtual void update();
        // Check whether the player is dead
        bool playerState();
        //Check whether all the fruits are eaten
        bool fruitsEaten();



    protected:

    private:
        shared_ptr<sf::RenderWindow> window_;
        shared_ptr<MazeHandler> mazeHandler_;
};

#endif // GAMESTATE_H
