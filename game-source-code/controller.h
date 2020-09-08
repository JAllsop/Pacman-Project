#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

class Controller
{
public:
    Controller();
    virtual ~Controller();
    void control(shared_ptr<Player> player);
protected:

private:
};

#endif // CONTROLLER_H
