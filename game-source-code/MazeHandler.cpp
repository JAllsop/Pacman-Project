#include "MazeHandler.h"

MazeHandler::MazeHandler(shared_ptr<sf::RenderWindow> window) : window_{window}
{
    // Objects
    maze_ = make_shared<Maze>(window);
    mChar_ = maze_->getCharMaze();
    m_= maze_-> getMaze();
    // Time var
    milli1 = sf::milliseconds(110);
    milli2 = sf::milliseconds(100);
    milli3 = sf::milliseconds(5000);
    //Var init
    random = 0;
    // Counters
    keys = 0;
    fruits = 0;
    powerPellet = 0;
    // Directions, not used yet
    isPlayerDead = false;
    isAllFruitsEaten=false;
    //Gets positional info from mazes
    setUpPlayer();
    setUpEnemy();
    //enemyHandler_ = make_shared<EnemyHandler>(m_,mChar_,isPlayerDead,powerPellet,playerX,playerY);
    //ctor
}

MazeHandler::~MazeHandler()
{
    //dtor
}

void MazeHandler::run()
{
    elapsed1 = clock1.getElapsedTime();
    elapsed2 = clock2.getElapsedTime();
    elapsed3 = clock3.getElapsedTime();
    if(elapsed1 >= milli1)
    {
        updateAI();
        //enemyHandler_->run();
        clock1.restart();
    }
    if(elapsed2 >= milli2)
    {
        updatePlayer();
        clock2.restart();
    }
    if(powerPellet > 0)
    {
        if(elapsed3 >= milli3){
            powerPellet = 0;
            clock3.restart();
        }
    }else{clock3.restart();}

    if(fruits == maze_->getMaxFruits())
    {
        isPlayerDead=true;
    }

    render();
}

void MazeHandler::setUpPlayer()
{
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(mChar_[i][j] == 'p')
            {
                playerX = i;
                playerY = j;
                pEntityX = i;
                pEntityY = j;
            }
        }
    }
}

void MazeHandler::setUpEnemy()
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
    // stores screen position
    ePosX = m_[enemyX][enemyY]->getX();
    ePosY = m_[enemyX][enemyY]->getY();
}

void MazeHandler::updateAI()
{
    bool hasMoved = false;
    srand(time(0));
    if(random == 0)
    {
        random = (rand()%4)+1;
    }
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(random == 1) // Up
            {
                if(mChar_[enemyX-1][enemyY] == '.' || mChar_[enemyX-1][enemyY] != 'w' && mChar_[enemyX-1][enemyY] != 'd')
                {
                    m_[eEntityX][eEntityY]->moveUp();
                    enemyX--;
                    hasMoved = true;
                    if(enemyX == playerX && enemyY == playerY)
                    {
                        if(powerPellet > 0)
                        {
                            m_[eEntityX][eEntityY]->setPosition(ePosX,ePosY);
                            enemyX = eEntityX;
                            enemyY = eEntityY;
                        }
                        else
                        {
                            isPlayerDead = true;
                        }
                    }
                    //break;
                }
            }
            else if(random == 2) // down
            {
                if(mChar_[enemyX+1][enemyY] == '.' || mChar_[enemyX+1][enemyY] != 'w' && mChar_[enemyX+1][enemyY] != 'd')
                {
                    m_[eEntityX][eEntityY]->moveDown();
                    enemyX++;
                    hasMoved = true;
                    if(enemyX == playerX && enemyY == playerY)
                    {
                        if(powerPellet > 0)
                        {
                            m_[eEntityX][eEntityY]->setPosition(ePosX,ePosY);
                            enemyX = eEntityX;
                            enemyY = eEntityY;
                        }
                        else
                        {
                            isPlayerDead = true;
                        }
                    }
                    //break;
                }
            }
            else if(random == 3 ) // left
            {
                if(mChar_[enemyX][enemyY-1] == '.' || mChar_[enemyX][enemyY-1] != 'w' && mChar_[enemyX][enemyY-1] != 'd')
                {
                    m_[eEntityX][eEntityY]->moveLeft();
                    enemyY--;
                    hasMoved = true;
                    if(enemyX == playerX && enemyY == playerY)
                    {
                       if(powerPellet > 0)
                        {
                            m_[eEntityX][eEntityY]->setPosition(ePosX,ePosY);
                            enemyX = eEntityX;
                            enemyY = eEntityY;
                        }
                        else
                        {
                            isPlayerDead = true;
                        }
                    }
                    //break;
                }
            }
            else if(random == 4) // right
            {
                if(mChar_[enemyX][enemyY+1] == '.' || mChar_[enemyX][enemyY+1] != 'w' && mChar_[enemyX][enemyY+1] != 'd')
                {
                    m_[eEntityX][eEntityY]->moveRight();
                    enemyY++;
                    hasMoved = true;
                    if(enemyX == playerX && enemyY == playerY)
                    {
                        if(powerPellet > 0)
                        {
                            m_[eEntityX][eEntityY]->setPosition(ePosX,ePosY);
                            enemyX = eEntityX;
                            enemyY = eEntityY;
                        }
                        else
                        {
                            isPlayerDead = true;
                        }
                    }
                    //break;
                }
            }
            if(powerPellet == 0)
            {
               //set color
               m_[eEntityX][eEntityY]->setColor(sf::Color::Red);
            }
            else
            {
                m_[eEntityX][eEntityY]->setColor(sf::Color::White);
            }
            if (hasMoved == false)
            {
                random = (rand()%4)+1;
            }
            else{break;}
        }
        if(hasMoved == true)
        {
            break;
        }
    }
}

void MazeHandler::updatePlayer()
{
    bool hasMoved = false;
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            //elapsed = clock.getElapsedTime();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if(mChar_[playerX+1][playerY] != 'w')
                {
                    if(mChar_[playerX+1][playerY] == 'f')
                    {
                        m_[pEntityX][pEntityY]->moveDown();
                        // Keep track on the array
                        playerX++;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the fruit

                        fruits++; // increments fruits
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX+1][playerY] == 'k')
                    {
                        // DEACTIVATES A DOOR
                        m_[pEntityX][pEntityY]->moveDown();
                        // Keep track on the array
                        playerX++;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key

                        keys++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX+1][playerY] == 'u') // Powerpellet
                    {
                        // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                        m_[pEntityX][pEntityY]->moveDown();
                        // Keep track on the array
                        playerX++;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key
                        powerPellet++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX+1][playerY] == 'd')
                    {
                        if(keys > 0) // if we have a key use it to open a door
                        {
                            // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                            m_[pEntityX][pEntityY]->moveDown();
                            // Keep track on the array
                            playerX++;
                            auto path = make_shared<Path>(40,40,sf::Color::Black);
                            auto pathChar = '.';
                            mChar_[playerX][playerY] = pathChar;
                            m_[playerX][playerY] = path; // smart pointer deletes the key
                            keys--;
                            hasMoved = true;
                            break;
                        }
                    }
                    else
                    {
                        // Move the object down
                        m_[pEntityX][pEntityY]->moveDown();
                        // Keep track on the array
                        playerX++;
                        hasMoved = true;
                        break;
                    }
                }
                //clock.restart();
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // up
            {
                if(mChar_[playerX-1][playerY] != 'w')
                {
                    if(mChar_[playerX-1][playerY] == 'f')
                    {
                        // Move the object down
                        m_[pEntityX][pEntityY]->moveUp();
                        // Keep track on the array
                        playerX--;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the fruit
                        fruits++; // increments fruits
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX-1][playerY] == 'k')
                    {
                        // DEACTIVATES A DOOR
                        m_[pEntityX][pEntityY]->moveUp();
                        // Keep track on the array
                        playerX--;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key
                        keys++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX-1][playerY] == 'u') // Powerpellet
                    {
                        // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                        m_[pEntityX][pEntityY]->moveUp();
                        // Keep track on the array
                        playerX--;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key
                        powerPellet++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX-1][playerY] == 'd')
                    {
                        if(keys > 0) // if we have a key use it to open a door
                        {
                            // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                            m_[pEntityX][pEntityY]->moveUp();
                            // Keep track on the array
                            playerX--;
                            auto path = make_shared<Path>(40,40,sf::Color::Black);
                            auto pathChar = '.';
                            mChar_[playerX][playerY] = pathChar;
                            m_[playerX][playerY] = path; // smart pointer deletes the key
                            keys--;
                            hasMoved = true;
                            break;
                        }
                    }
                    else
                    {
                        // Move the object down
                        m_[pEntityX][pEntityY]->moveUp();
                        // Keep track on the array
                        playerX--;
                        hasMoved = true;
                        break;
                    }
                    //clock.restart();
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                if(mChar_[playerX][playerY+1] != 'w')
                {
                    if(mChar_[playerX][playerY+1] == 'f')
                    {
                        // Move the object down
                        m_[pEntityX][pEntityY]->moveRight();
                        // Keep track on the array
                        playerY++;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the fruit
                        fruits++; // increments fruits
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX][playerY+1] == 'k')
                    {
                        // DEACTIVATES A DOOR
                        m_[pEntityX][pEntityY]->moveRight();
                        // Keep track on the array
                        playerY++;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key
                        keys++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX][playerY+1] == 'u') // Powerpellet
                    {
                        // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                        m_[pEntityX][pEntityY]->moveRight();
                        // Keep track on the array
                        playerY++;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key
                        powerPellet++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX][playerY+1] == 'd')
                    {
                        if(keys > 0) // if we have a key use it to open a door
                        {
                            // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                            m_[pEntityX][pEntityY]->moveRight();
                            // Keep track on the array
                            playerY++;
                            auto path = make_shared<Path>(40,40,sf::Color::Black);
                            auto pathChar = '.';
                            mChar_[playerX][playerY] = pathChar;
                            m_[playerX][playerY] = path; // smart pointer deletes the key
                            keys--;
                            hasMoved = true;
                            break;
                        }
                    }
                    else
                    {
                        // Move the object down
                        m_[pEntityX][pEntityY]->moveRight();
                        // Keep track on the array
                        playerY++;
                        hasMoved = true;
                        break;
                    }
                    //clock.restart();
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                if(mChar_[playerX][playerY-1] != 'w')
                {
                    if(mChar_[playerX][playerY-1] == 'f')
                    {
                        // Move the object down
                        m_[pEntityX][pEntityY]->moveLeft();
                        // Keep track on the array
                        playerY--;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the fruit
                        fruits++; // increments fruits
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX][playerY-1] == 'k')
                    {
                        // DEACTIVATES A DOOR
                        m_[pEntityX][pEntityY]->moveLeft();
                        // Keep track on the array
                        playerY--;
                        auto path = make_shared<Path>(40,40,sf::Color::Transparent);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key
                        keys++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX][playerY-1] == 'u') // Powerpellet
                    {
                        // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                        m_[pEntityX][pEntityY]->moveLeft();
                        // Keep track on the array
                        playerY--;
                        auto path = make_shared<Path>(40,40,sf::Color::Black);
                        auto pathChar = '.';
                        mChar_[playerX][playerY] = pathChar;
                        m_[playerX][playerY] = path; // smart pointer deletes the key
                        powerPellet++;
                        hasMoved = true;
                        break;
                    }
                    else if(mChar_[playerX][playerY-1] == 'd')
                    {
                        if(keys > 0) // if we have a key use it to open a door
                        {
                            // CANT MOVE THROUGH DOORS UNLESS THEY ARE TURNED OFF
                            m_[pEntityX][pEntityY]->moveLeft();
                            // Keep track on the array
                            playerY--;
                            auto path = make_shared<Path>(40,40,sf::Color::Transparent);
                            auto pathChar = '.';
                            mChar_[playerX][playerY] = pathChar;
                            m_[playerX][playerY] = path; // smart pointer deletes the key
                            keys--;
                            hasMoved = true;
                            break;
                        }
                    }
                    else
                    {
                        // Move the object down
                        m_[pEntityX][pEntityY]->moveLeft();
                        // Keep track on the array
                        playerY--;
                        hasMoved = true;
                        break;
                    }
                    //clock.restart();
                }
                //clock.restart();
            }
        }
        if(hasMoved == true)
        {
            break;
        }
    }
}

void MazeHandler::render()
{
    window_->clear();
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(typeid(Wall) == typeid(*m_[i][j]))
                window_->draw(*(m_[i][j]->getEntity()));
            if(typeid(Fruit) == typeid(*m_[i][j]))
                window_->draw(*(m_[i][j]->getEntity()));
            if(typeid(Key) == typeid(*m_[i][j]))
                window_->draw(*(m_[i][j]->getEntity()));
            if(typeid(Door) == typeid(*m_[i][j]))
                window_->draw(*(m_[i][j]->getEntity()));
            if(typeid(PowerPellet) == typeid(*m_[i][j]))
                window_->draw(*(m_[i][j]->getEntity()));
        }
    }
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(typeid(Player) == typeid(*m_[i][j]))
                window_->draw(*(m_[i][j]->getEntity()));
            if(typeid(Enemy) == typeid(*m_[i][j]))
                window_->draw(*(m_[i][j]->getEntity()));
        }
    }

    window_->display();
}

bool MazeHandler::getPlayerState()
{
    return isPlayerDead;
}

bool MazeHandler::allFruitsEaten()
{
    return isAllFruitsEaten;
}
