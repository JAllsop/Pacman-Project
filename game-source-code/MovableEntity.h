#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include "entity.h"

class MovableEntity : public Entity
{
    public:
        MovableEntity(float width, float height , sf::Color color);
        virtual ~MovableEntity();
        virtual void moveUp();
        virtual void moveDown();
        virtual void moveLeft();
        virtual void moveRight();
    protected:

    private:
};

#endif // MOVABLEENTITY_H
