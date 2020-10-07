#include "entity.h"

Entity::Entity(float width, float height, sf::Color color) : height_{height}, width_{width}
{
    //initialX = getX();
    //initialY = getY();
    //isAlive_ = true;
    entity_ = make_shared<sf::RectangleShape>(sf::Vector2f(width_,height_));
    entity_->setFillColor(color);
    entity_->setPosition(0,0);
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::setPosition(float xPos, float yPos)
{
    entity_->setPosition(xPos,yPos);
}

void Entity::setColor(sf::Color color)
{
    entity_->setFillColor(color);
}

float Entity::getX()
{
    return entity_->getPosition().x;
}

float Entity::getY()
{
    return entity_->getPosition().y;
}

float Entity::getTop()
{
    return getY();
}

float Entity::getBottom()
{
    return (getY() + height_);
}

float Entity::getLeft()
{
    return getX();
}

float Entity::getRight()
{
    return (getX() + width_);
}
/*
float Entity::getWidth()
{
    return width_;
}

float Entity::getHeight()
{
    return height_;
}
*/
shared_ptr<sf::RectangleShape> Entity::getEntity()
{
    return entity_;
}

float Entity::getInitialX()
{
    return initialX;
}

float Entity::getInitialY()
{
    return initialY;
}

/*
bool Entity::isAlive()
{
    return isAlive_;
}
*/
