#ifndef PLAYER_H
#define PLAYER_H

#include "MovableEntity.h"

class Player : public MovableEntity
{
    public:
        Player(float width, float height ,sf::Color color);
        virtual ~Player();
        int getLives();
    protected:

    private:
        int lives;
};

#endif // PLAYER_H
