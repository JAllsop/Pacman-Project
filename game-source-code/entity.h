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
#include <vector>
#include <iterator>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <ctime>

#define blockSize 40

using namespace std;

class Entity
{
public:
    Entity(float width, float height, sf::Color color);
    virtual ~Entity();
    //set stuff
    void setPosition(float xPos, float yPos);
    void setColor(sf::Color color);

    //Get positions
    float getX();
    float getY();
    shared_ptr<sf::RectangleShape> getEntity();

    float setInitialX(float x);
    float setInitialY(float y);

    float getInitialX();
    float getInitialY();

protected:
    shared_ptr<sf::RectangleShape> entity_;

    float initialX;
    float initialY;

    float height_;
    float width_;

private:
};

#endif // ENTITY_H
