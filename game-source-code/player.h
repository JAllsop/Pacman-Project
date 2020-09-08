#ifndef PLAYER_H
#define PLAYER_H

#include "MovableEntity.h"

class Player : public MovableEntity
{
    public:
        Player(float width, float height);
        virtual ~Player();

    protected:

    private:
};

#endif // PLAYER_H
