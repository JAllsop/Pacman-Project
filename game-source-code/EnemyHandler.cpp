#include "EnemyHandler.h"

EnemyHandler::EnemyHandler(shared_ptr<Maze> maze): isPlayerDead{false}
{
    srand(time(0));
    enemies_ = maze->getEnemies();
    player_ = maze->getPlayer();
    walls_ = maze->getWalls();
    doors_ = maze->getDoors();
    enemySpeed = sf::milliseconds(450);
}

EnemyHandler::~EnemyHandler()
{
    //dtor
}

bool EnemyHandler::run()
{
    if(enemyClock1.getElapsedTime() >= enemySpeed)
    {
        update(0);
        enemyClock1.restart();
    }
    if(enemyClock2.getElapsedTime() >= enemySpeed)
    {
        update(1);
        enemyClock2.restart();
    }
    if(enemyClock3.getElapsedTime() >= enemySpeed)
    {
        update(2);
        enemyClock3.restart();
    }
    return isPlayerDead;
}

void EnemyHandler::update(int enemyNum)
{
    auto hasMoved = false;
    vector<int> obstacle;
    random = (rand()%4)+1;
    while(hasMoved == false)
    {
        //accounts for moving in the same direction if a static entity is there
        if (std::find(obstacle.begin(), obstacle.end(), random) != obstacle.end())
        {
             random = (rand()%4)+1;
        }
        switch(random)
        {
        case 1 : //Down
            {
                obstacle.push_back(random);
                hasMoved = moveDown(enemyNum);
            }
            break;
        case 2 :  //Up
            {
                obstacle.push_back(random);
                hasMoved = moveUp(enemyNum);
            }
            break;
        case 3 : //Left
            {
                obstacle.push_back(random);
                hasMoved = moveLeft(enemyNum);
            }
            break;
        case 4 : //Right
            {
                obstacle.push_back(random);
                hasMoved = moveRight(enemyNum);
            }
            break;
        }
    }
    obstacle.clear();
}

bool EnemyHandler::moveDown(int enemyNum)
{
    auto i = enemies_.begin() + enemyNum;
    (*i)->moveDown();
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(*test) == typeid(Player))
        {
            if((*i)->getEntity()->getFillColor() == sf::Color::Magenta)//powerPellet Mode
            {
                (*i)->moveUp();
                return true;
            }
            isPlayerDead = true;
            return true;
        }
        (*i)->moveUp();
        return false;
    }
    return true;
}

bool EnemyHandler::moveUp(int enemyNum)
{
    auto i = enemies_.begin() + enemyNum;
    (*i)->moveUp();
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(*test) == typeid(Player))
        {
            if((*i)->getEntity()->getFillColor() == sf::Color::Magenta)//powerPellet Mode
            {
                (*i)->moveDown();
                return true;
            }
            isPlayerDead = true;
            return true;
        }
        (*i)->moveDown();
        return false;
    }
    return true;
}

bool EnemyHandler::moveRight(int enemyNum)
{
    auto i = enemies_.begin() + enemyNum;
    (*i)->moveRight();
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(*test) == typeid(Player))
        {
            if((*i)->getEntity()->getFillColor() == sf::Color::Magenta)//powerPellet Mode
            {
                (*i)->moveLeft();
                return true;
            }
            isPlayerDead = true;
            return true;
        }
        (*i)->moveLeft();
        return false;
    }
    return true;
}

bool EnemyHandler::moveLeft(int enemyNum)
{
    auto i = enemies_.begin() + enemyNum;
    (*i)->moveLeft();
    auto test = enemyCollision(*i);
    if(test != *i)
    {
        if(typeid(*test) == typeid(Player))
        {
            if((*i)->getEntity()->getFillColor() == sf::Color::Magenta)//powerPellet Mode
            {
                (*i)->moveRight();
                return true;
            }
            isPlayerDead = true;
            return true;
        }
        (*i)->moveRight();
        return false;
    }
    return true;
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

