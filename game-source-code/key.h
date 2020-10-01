#ifndef KEY_H
#define KEY_H

#include "StaticEntity.h"

class Key : public StaticEntity
{
    public:
        Key(float width, float height, sf::Color color);
        virtual ~Key();

    protected:

    private:
};

#endif // KEY_H
