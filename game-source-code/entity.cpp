#include "entity.h"

Entity::Entity(float width, float height) : width_{width}, height_{height}
{
    entity_ = make_shared<sf::RectangleShape>(sf::Vector2f(width_,height_));
    entity_->setFillColor(sf::Color::Green);
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

shared_ptr<sf::RectangleShape> Entity::getEntity()
{
    return entity_;
}
