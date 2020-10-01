#ifndef FRUIT_H
#define FRUIT_H

#include "StaticEntity.h"

class Fruit : public StaticEntity
{
    public:
        Fruit(float width, float height, sf::Color color);
        virtual ~Fruit();

    protected:

    private:
};

#endif // FRUIT_H
