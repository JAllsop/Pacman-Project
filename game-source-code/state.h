#ifndef STATE_H
#define STATE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class State
{
public:
    State();
    virtual ~State();
    virtual void run() = 0;
    virtual void loadAssets() = 0;
    virtual void  update() = 0;
protected:

private:
};

#endif // STATE_H
