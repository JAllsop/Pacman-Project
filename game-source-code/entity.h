#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Entity
{
    public:
        Entity(float width, float height);
        virtual ~Entity();
        virtual void setPosition(float xPos, float yPos);
        virtual float getX();
        virtual float getY();
        virtual float getTop();
        virtual float getBottom();
        virtual float getLeft();
        virtual float getRight();
        virtual shared_ptr<sf::RectangleShape> getEntity();

    protected:
        shared_ptr<sf::RectangleShape> entity_;
        float height_;
        float width_;
    private:
};

#endif // ENTITY_H
