#include "MovableEntity.h"

MovableEntity::MovableEntity(float width, float height): Entity(width, height)
{
    //ctor
}

MovableEntity::~MovableEntity()
{
    //dtor
}

void MovableEntity::moveUp()
{
    entity_->move(0,-1);
}

void MovableEntity::moveDown()
{
    entity_->move(0,1);
}

void MovableEntity::moveLeft()
{
    entity_->move(-1,0);
}

void MovableEntity::moveRight()
{
    entity_->move(1,0);
}
