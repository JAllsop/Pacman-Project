#ifndef DOOR_H
#define DOOR_H

#include "StaticEntity.h"

class Door : public StaticEntity
{
    public:
        Door(float width, float height, sf::Color color);
        virtual ~Door();

    protected:

    private:
};

#endif // DOOR_H
