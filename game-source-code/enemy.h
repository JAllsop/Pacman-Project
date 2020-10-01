#ifndef ENEMY_H
#define ENEMY_H

#include "MovableEntity.h"

class Enemy : public MovableEntity
{
public:
    Enemy(float width, float height, sf::Color color);
    virtual ~Enemy();

protected:

private:
};

#endif // ENEMY_H
