#ifndef WALL_H
#define WALL_H

#include "StaticEntity.h"

class Wall : public StaticEntity
{
    public:
        Wall(float width, float height , sf::Color color);
        virtual ~Wall();

    protected:

    private:
};

#endif // WALL_H
