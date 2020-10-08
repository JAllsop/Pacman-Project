#ifndef WINSTATE_H
#define WINSTATE_H

#include "state.h"

class WinState : public State
{
    public:
        WinState(shared_ptr<sf::RenderWindow> window);
        virtual ~WinState();
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

#endif // WINSTATE_H
