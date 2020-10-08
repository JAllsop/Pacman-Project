#include "EnemyHandler.h"

EnemyHandler::EnemyHandler(shared_ptr<Maze> maze)
{
    srand(time(0));
    enemies_ = maze->getEnemies();
    player_ = maze->getPlayer();
    walls_ = maze->getWalls();
    doors_ = maze->getDoors();
    enemySpeed1 = sf::milliseconds(1000);
    enemySpeed2 = sf::milliseconds(400);
}

EnemyHandler::~EnemyHandler()
{
    //dtor
}

void EnemyHandler::run()
{
    if(enemyClock1.getElapsedTime() >= enemySpeed1)
    {
        update(0);
        enemyClock1.restart();
    }
    if(enemyClock2.getElapsedTime() >= enemySpeed2)
    {
        update(1);
        enemyClock2.restart();
    }
}

void EnemyHandler::update(int enemyNum) //move to EnemyHandler
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

bool EnemyHandler::enemyMoveDown(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveDown();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        hasMoved = false;
        (*i)->moveUp();
    }
    return hasMoved;
}

bool EnemyHandler::enemyMoveUp(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveUp();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        hasMoved = false;
        (*i)->moveDown();
    }
    return hasMoved;
}

bool EnemyHandler::enemyMoveRight(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveRight();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        hasMoved = false;
        (*i)->moveLeft();
    }
    return hasMoved;
}

bool EnemyHandler::enemyMoveLeft(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveLeft();
    auto hasMoved = true;
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        hasMoved = false;
        (*i)->moveRight();
    }
    return hasMoved;
}

shared_ptr<Entity> EnemyHandler::enemyCollision(shared_ptr<Enemy> enemy)
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

