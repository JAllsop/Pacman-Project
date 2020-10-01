#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "enemy.h"

class Controller
{
public:
    Controller();
    virtual ~Controller();
    void control(shared_ptr<Entity> player);
    void controlAI(shared_ptr<Enemy> enemy);
protected:

private:
};

#endif // CONTROLLER_H
