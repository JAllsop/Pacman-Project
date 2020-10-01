#include "StaticEntity.h"

StaticEntity::StaticEntity(float width, float height, sf::Color color) : Entity(width, height, color)
{
    //ctor
}

StaticEntity::~StaticEntity()
{
    //dtor
}

void StaticEntity::moveUp()
{
    entity_->move(0,0);
}
void StaticEntity::moveDown()
{
    entity_->move(0,0);
}
void StaticEntity::moveLeft()
{
    entity_->move(0,0);
}
void StaticEntity::moveRight()
{
    entity_->move(0,0);
}
