#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "state.h"

class MenuState : public State
{
public:
    MenuState(shared_ptr<sf::RenderWindow> window);
    virtual ~MenuState();
    virtual void run();
    virtual void loadAssets();
    virtual void update();

protected:

private:
    shared_ptr<sf::RenderWindow> window_;
    sf::Font font;
    vector<sf::Text> texts_;
};

#endif // MENUSTATE_H
