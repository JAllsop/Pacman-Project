#include "MovableEntity.h"

MovableEntity::MovableEntity(float width, float height , sf::Color color): Entity(width, height, color)
{
    //ctor
}

MovableEntity::~MovableEntity()
{
    //dtor
}

void MovableEntity::moveUp()
{
    entity_->move(0,-height_);
}

void MovableEntity::moveDown()
{
    entity_->move(0,height_);
}

void MovableEntity::moveLeft()
{
    entity_->move(-width_,0);
}

void MovableEntity::moveRight()
{
    entity_->move(width_,0);
}
