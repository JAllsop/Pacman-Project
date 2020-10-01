#ifndef POWERPELLET_H
#define POWERPELLET_H

#include "StaticEntity.h"

class PowerPellet : public StaticEntity
{
    public:
        PowerPellet(float width, float height , sf::Color color);
        virtual ~PowerPellet();

    protected:

    private:
};

#endif // POWERPELLET_H
