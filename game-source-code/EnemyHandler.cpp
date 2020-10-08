#include "EnemyHandler.h"

EnemyHandler::EnemyHandler(shared_ptr<Maze> maze)
{
    //ctor
}

EnemyHandler::~EnemyHandler()
{
    //dtor
}

void MazeHandler::update(int enemyNum) //move to EnemyHandler
{
    auto hasMoved = false;
    auto i = enemies_.begin() + enemyNum;
    while(hasMoved == false)
    {
        random = (rand()%4)+1;
        switch(random)
        {//better seperation (especially for testing) if indivual function for each movement
        case 1 : //Down
            {
                hasMoved = enemyMoveDown(i);
            }
            break;
        case 2 :  //Up
            {
                hasMoved = enemyMoveUp(i);
            }
            break;
        case 3 : //Left
            {
                hasMoved = enemyMoveLeft(i);
            }
            break;
        case 4 : //Right
            {
                hasMoved = enemyMoveRight(i);
            }
            break;
        }
    }
}

bool MazeHandler::enemyMoveDown(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveDown();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(test) == typeid(Player))
        {
            //super pellet check
        }
        else //hitting wall
        {
            hasMoved = false;
            (*i)->moveUp();
        }
    }
    return hasMoved;
}

bool MazeHandler::enemyMoveUp(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveUp();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(test) == typeid(Player))
        {
            //super pellet check
        }
        else //hitting wall
        {
            hasMoved = false;
            (*i)->moveDown();
        }
    }
    return hasMoved;
}

bool MazeHandler::enemyMoveRight(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveRight();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(test) == typeid(Player))
        {
            //super pellet check
        }
        else //hitting wall
        {
            hasMoved = false;
            (*i)->moveLeft();
        }
    }
    return hasMoved;
}

bool MazeHandler::enemyMoveLeft(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveLeft();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(test) == typeid(Player))
        {
            //super pellet check
        }
        else //hitting wall
        {
            hasMoved = false;
            (*i)->moveRight();
        }
    }
    return hasMoved;
}

shared_ptr<Entity> MazeHandler::enemyCollision(shared_ptr<Enemy> enemy) //move to EnemyHandler
{
    if (enemy->getEntity()->getGlobalBounds().intersects(player_->getEntity()->getGlobalBounds()))
    {
        return player_;
    }
    for(auto testEntity = walls_.begin(); testEntity != walls_.end(); ++testEntity)
    {
        if(enemy->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return *testEntity;
            }
    }
    for(auto testEntity = doors_.begin(); testEntity != doors_.end(); ++testEntity)
    {
        if(enemy->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return *testEntity;
            }
    }
    return enemy;
}

