#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "entity.h"

class StaticEntity : public Entity
{
    public:
        StaticEntity(float width, float height , sf::Color color);
        virtual ~StaticEntity();

    protected:

    private:
};

#endif // STATICENTITY_H
