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

    float getInitialX();
    float getInitialY();

    // The entity boundaries
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();

    /*
    // Entity dimensions
    virtual float getWidth();
    virtual float getHeight();
    virtual shared_ptr<sf::RectangleShape> getEntity();
    */
    /* Entity movements
    virtual void moveUp()= 0;
    virtual void moveDown()= 0;
    virtual void moveLeft()= 0;
    virtual void moveRight()= 0;
    */
    // bools
    //bool isAlive();

protected:
    shared_ptr<sf::RectangleShape> entity_;
    float height_;
    float width_;
    float initialX;
    float initialY;

private:
    //float isAlive_;
};

#endif // ENTITY_H
