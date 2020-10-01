#ifndef PATH_H
#define PATH_H

#include "StaticEntity.h"

class Path : public StaticEntity
{
    public:
        Path(float width, float height , sf::Color color);
        virtual ~Path();

    protected:

    private:
};

#endif // PATH_H
