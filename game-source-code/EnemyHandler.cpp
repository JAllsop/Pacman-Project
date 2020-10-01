#include "EnemyHandler.h"

EnemyHandler::EnemyHandler(vector<vector<shared_ptr<Entity>>> mazeE, vector<vector<char>>& mazeC,bool& isPlayerD, int& pP, int pX, int pY) : m_{mazeE},
mChar_{mazeC},
isPlayerDead{isPlayerD},
powerPellet{pP},
playerX{pX},
playerY{pY}
{
    setup();
    //ctor
}

EnemyHandler::~EnemyHandler()
{
    //dtor
}

void EnemyHandler::run()
{
    update();
}

void EnemyHandler::setup()
{
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(mChar_[i][j] == 'e')
            {
                enemyX = i;
                enemyY = j;
                eEntityX = i;
                eEntityY = j;
            }
        }
    }
    // Stores starting screen position of the enemy
    ePosX = m_[enemyX][enemyY]->getX();
    ePosY = m_[enemyX][enemyY]->getY();
}

bool EnemyHandler::isEdable()
{
    if(powerPellet > 0)
    {
        return true;
    }

    return false;
}

void EnemyHandler::reset()
{
    m_[eEntityX][eEntityY]->setPosition(ePosX,ePosY);
    enemyX = eEntityX;
    enemyY = eEntityY;
}

void EnemyHandler::checkPlayerCollision()
{
    if(enemyX == playerX && enemyY == playerY)
    {
        if(isEdable() == true)
        {
            reset();
        }
        else
        {
            isPlayerDead = true;
        }
    }
}

void EnemyHandler::changeColorState()
{
    if(isEdable() == true)
    {
        m_[eEntityX][eEntityY]->setColor(sf::Color::Red);
    }
    else
    {
        m_[eEntityX][eEntityY]->setColor(sf::Color::White);
    }
}

void EnemyHandler::up(bool& hasMoved)
{
    m_[eEntityX][eEntityY]->moveUp();
    enemyX--;
    hasMoved = true;
    checkPlayerCollision();
}

void EnemyHandler::down(bool& hasMoved)
{
    m_[eEntityX][eEntityY]->moveDown();
    enemyX++;
    hasMoved = true;
    checkPlayerCollision();
}

void EnemyHandler::left(bool& hasMoved)
{
    m_[eEntityX][eEntityY]->moveLeft();
    enemyY--;
    hasMoved = true;
    checkPlayerCollision();
}

void EnemyHandler::right(bool& hasMoved)
{
    m_[eEntityX][eEntityY]->moveRight();
    enemyY++;
    hasMoved = true;
    checkPlayerCollision();
}

void EnemyHandler::update()
{
    bool hasMoved = false;
    srand(time(0));
    if(random == 0)// if at the start of the game
    {
        random = (rand()%4)+1;
    }
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(random == 1) // Up
            {
                if((mChar_[enemyX-1][enemyY] != 'w' && mChar_[enemyX-1][enemyY] != 'd'))
                {
                    up(hasMoved);
                    break;
                }
            }
            else if(random == 2) // down
            {
                if((mChar_[enemyX+1][enemyY] != 'w' && mChar_[enemyX+1][enemyY] != 'd'))
                {
                    down(hasMoved);
                    break;
                }
            }
            else if(random == 3 ) // left
            {
                if((mChar_[enemyX][enemyY-1] != 'w' && mChar_[enemyX][enemyY-1] != 'd'))
                {
                    left(hasMoved);
                    break;
                }
            }
            else if(random == 4) // right
            {
                if((mChar_[enemyX][enemyY+1] != 'w' && mChar_[enemyX][enemyY+1] != 'd'))
                {
                    right(hasMoved);
                    break;
                }
            }
            changeColorState();
            if (hasMoved == false)
            {
                random = (rand()%4)+1;
            }
        }
        if(hasMoved == true)
        {
            break;
        }
    }
}
