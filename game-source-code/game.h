#ifndef GAME_H
#define GAME_H

#include "state.h"
#include "MenuState.h"
#include "GameState.h"

#define MAX_NUM_STATES 3
#define MIN_NUM_STATES 1
class Game
{
public:
    Game();
    virtual ~Game();
    // Game loop
    void run();

private:

    // Initialise window
    void initWindow();
    // Manages events
    void updateEvents();
    // Managaes states
    void updateStates();
    // Runs a state
    void runState();
    // Initialise states
    void initState();

    // Window variables
    std::shared_ptr<sf::RenderWindow> window_;
    sf::Event event_;
    int gameWidth_;
    int gameHeight_;

    // State variables
    bool isMenuState_;
    bool isGameState_;
    bool isEndState_;

    // Objects
    shared_ptr<State> menuState_;
    shared_ptr<State> gameState_;
    stack<shared_ptr<State>> stateContainer_;

};

#endif // GAME_H
