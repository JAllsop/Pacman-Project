#ifndef LOSESTATE_H
#define LOSESTATE_H

#include "state.h"

class LoseState : public State
{
    public:
        LoseState(shared_ptr<sf::RenderWindow> window);
        virtual ~LoseState();
        // This will run the state
        virtual void run();
        // loads assets
        virtual void loadAssets();
        // Gets the logic for the entities
        virtual void update();

    protected:

    private:
    shared_ptr<sf::RenderWindow> window_;
    sf::Font font;
    vector<sf::Text> texts_;
};

#endif // LOSESTATE_H
