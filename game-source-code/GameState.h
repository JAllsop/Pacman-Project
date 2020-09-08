#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "state.h"
//#include "PlayerHandler.h"

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
protected:

private:
    shared_ptr<sf::RenderWindow> window_;
    //shared_ptr<PlayerHandler> playerHandler_; // this will handle the player
};

#endif // GAMESTATE_H
