#include "MazeHandler.h"

MazeHandler::MazeHandler(shared_ptr<sf::RenderWindow> window) : window_{window}
{
    // Objects
    maze_ = make_shared<Maze>(window);
    mChar_ = maze_->getCharMaze();
    m_= maze_-> getMaze();
    //auto test = maze_->getPlayer();
    //cout << test->getY() << "\n";
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
    isAllFruitsEaten = false;
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
        //playerHandler_->run();
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
        isPlayerDead = true;
    }
    render();
}
/*
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
*/
void MazeHandler::updateAI()
{
    //enumerate direction?
    auto hasMoved = false;
    srand(time(0));
    auto enemies = maze_->getEnemies();
    if(random == 0)
    {
        random = (rand()%4)+1;
    }
    /*for(int i = 0; i < MAX_MAZE_X; i++)
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
    }*/
    for (auto i = enemies.begin(); i != enemies.end(); ++i)
    {
        while(hasMoved == false)
        {   //lambda function? - lots of repeating code, or playerCollision method
            switch(random)
            {//better seperation (especially for testing) if indivual function for each movement
            case '1' : //Up
                {
                    *i->moveUp();
                    hasMoved = true;
                    auto test = enemyCollision(*i);
                    if(test != *i)
                    {
                        if(typeid(*test) == typeid(Player))
                        {
                            //super pellet check
                        }
                        else //hitting wall
                        {
                            hasMoved = false;
                            random = (rand()%4)+1;
                            *i->moveDown();
                        }
                    }
                }
                break;
            case '2' :  //Down
                {
                    *i->moveDown();
                    hasMoved = true;
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
                            random = (rand()%4)+1;
                            *i->moveUp();
                        }
                    }
                }
                break;
            case '3' : //Left
                {
                    *i->moveLeft();
                    hasMoved = true;
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
                            random = (rand()%4)+1;
                            *i->moveRight();
                        }
                    }
                }
                break;
            case '4' : //Right
                {
                    *i->moveRight();
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
                            random = (rand()%4)+1;
                            *i->moveLeft();
                        }
                    }
                }
                break;
            }
        }
    }
}

shared_ptr<Entity> MazeHandler::enemyCollision(shared_ptr<Enemy> enemy)
{
    auto testEntities = maze_->getWalls();
    auto player = maze_->getPlayer();
    if (enemy->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
    {
        return player;
    }
    for(auto testEntity = testEntities.begin(); testEntity != testEntities.end(); ++testEntities)
    {
        if(enemy->getSprite().getGlobalBounds().intersects(*testEntity->getSprite().getGlobalBounds()))
            {
                return *testEntity;
            }
    }
    return enemy;
}

shared_ptr<Entity> MazeHandler::collision(shared_ptr<Entity> movingEntity, vector<shared_ptr<Entity>> testEntities)
{
    for(auto testEntity = testEntities.begin(); testEntity != testEntities.end(); ++testEntities)
    {
        if(movingEntity->getSprite().getGlobalBounds().intersects(*testEntity->getSprite().getGlobalBounds()))
            {
                return *testEntity;
            }
    }
    return movingEntity;
}

shared_ptr<Entity> MazeHandler::playerCollision(shared_ptr<Player> Player)
{
    collideEntity = collision(player, maze_getWall());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_getFruit());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_getKey());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_getDoor());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_getPowerPellets());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}
}

bool MazeHandler::resolveCollision(shared_ptr<Player> player)
{
    bool reverseMovement;
    auto collideEntity = playerCollision();
    if(typeid(collideEntity) != typeid(player))
    {
        if(typeid(collideEntity) == typeid(Wall))
        {
            reverseMovement = true;
        }
        else if(typeid(collideEntity) == typeid(Fruit))
        {
            auto it = find(maze_->getFruit().begin(), maze_->getFruit().end(), collideEntity);
            auto index = maze_->getFruit().begin() + distance(maze_->getFruit().begin(), it);
            maze_->getFruit().erase(index);

            fruits++;
        }
        else if(typeid(collideEntity) == typeid(Key))
        {
            auto it = find(maze_->getKeys().begin(), maze_->getKeys().end(), collideEntity);
            auto index = maze_->getKeys().begin() + distance(maze_->getKeys().begin(), it);
            maze_->getKeys().erase(index);

            keys++;
        }
        else if(typeid(collideEntity) == typeid(Door))
        {
            if(keys > 0)
            {
                auto it = find(maze_->getDoors().begin(), maze_->getDoors().end(), collideEntity);
                auto index = maze_->getDoors().begin() + distance(maze_->getDoors().begin(), it);
                maze_->getDoors().erase(index);

                keys--;
            }
            else
            {
                reverseMovement = true;
            }
        }
        else if(typeid(collideEntity) == typeid(PowerPellet))
        {
            auto it = find(maze_->getPowerPellets().begin(), maze_->getPowerPellets().end(), collideEntity);
            auto index = maze_->getKeys().begin() + distance(maze_->getPowerPellets().begin(), it);
            maze_->getPowerPellets().erase(index);

            powerPellets++;
        }
        else if(typeid(collideEntity) == typeid(Enemy))
        {
            if(powerPellet > 0)
            {
                collideEntity->setPosition(ePosX,ePosY);
            }
            else
            {
                isPlayerDead = true;
            }
        }
    }
    return reverseMovement;
}

void MazeHandler::playerMoveDown()
{
    auto player = maze_->getPlayer();
    player->moveDown();
    auto reverseMovement = resolveCollision(shared_ptr<Player> player);
    if(reverseMovement){player->moveUp();}
}

void MazeHandler::playerMoveUp()
{
    auto player = maze_->getPlayer();
    player->moveUp();
    auto reverseMovement = resolveCollision(shared_ptr<Player> player);
    if(reverseMovement){player->moveDown();}
}

void MazeHandler::playerMoveLeft()
{
    auto player = maze_->getPlayer();
    player->moveLeft();
    auto reverseMovement = resolveCollision(shared_ptr<Player> player);
    if(reverseMovement){player->moveRight();}
}

void MazeHandler::playerMoveRight()
{
    auto player = maze_->getPlayer();
    player->moveRight();
    auto reverseMovement = resolveCollision(shared_ptr<Player> player);
    if(reverseMovement){player->moveLeft();}
}

void MazeHandler::updatePlayer()
{

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
    */
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerMoveDown();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerMoveUp();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerMoveLeft();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerMoveRight();
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

vector<vector<shared_ptr<Entity>>> MazeHandler::getEntities()
{
    return m_;
}

vector<vector<char>> MazeHandler::getCharMaze()
{
    return mChar_;
}

shared_ptr<Maze> MazeHandler::getMaze()
{
    return maze_;
}

int MazeHandler::getEnemyInitialX()
{
    return eEntityX;
}
int MazeHandler::getEnemyInitialY()
{
    return eEntityY;
}
