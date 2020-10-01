#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "state.h"

class EndState : public State
{
public:
    EndState(shared_ptr<sf::RenderWindow> window);
    virtual ~EndState();
    virtual void run();
    virtual void loadAssets();
    virtual void update();
    virtual bool isStateEnd();

protected:

private:
    shared_ptr<sf::RenderWindow> window_;
    sf::Font font;
    vector<sf::Text> texts_;
};

#endif // ENDSTATE_H
