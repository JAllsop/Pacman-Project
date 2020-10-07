#include "MazeHandler.h"

MazeHandler::MazeHandler(shared_ptr<sf::RenderWindow> window) : window_{window}, random{0}, keys{0}, fruits{0}, powerPellets{0}
{
    // Objects
    maze_ = make_shared<Maze>(window);

    enemies_ = maze_->getEnemies();
    player_ = maze_->getPlayer();
    walls_ = maze_->getWalls();
    keys_ = maze_->getKeys();
    fruits_ = maze_->getFruits();
    powerPellets_ = maze_->getPowerPellets();
    doors_ = maze_->getDoors();

    // Time var
    enemySpeed = sf::milliseconds(200);
    playerSpeed = sf::milliseconds(100);
    powerPelletTime = sf::milliseconds(5000);

    // Directions, not used yet
    isPlayerDead = false;
    isAllFruitsEaten = false;

    srand(time(0));
}

MazeHandler::~MazeHandler()
{
    //dtor
}

void MazeHandler::run()
{
    if(enemyClock.getElapsedTime() >= enemySpeed)
    {
        updateAI();
        //enemyHandler_->run();
        enemyClock.restart();
    }/*
    if(playerClock.getElapsedTime() >= playerSpeed)
    {
        updatePlayer();
        //playerHandler_->run();
        playerClock.restart();
    }
    if(powerPellet > 0)
    {
        if(PowerPelletClock.getElapsedTime() >= PowerPelletTime){
            powerPellets = 0;
            PowerPelletClock.restart();
        }
    }else{PowerPelletClock.restart();}

    if(fruits == maze_->getMaxFruits())
    {
        isPlayerDead = true;
    }*/
    render();
}

void MazeHandler::updateAI() //move to EnemyHandler
{
    //enumerate direction?
    auto hasMoved = false;
    //auto enemies = maze_->getEnemies();
    for (auto i = enemies_.begin(); i != enemies_.end(); ++i)
    {
        while(hasMoved == false)
        {
            random = (rand()%4)+1;
            switch(random)
            {//better seperation (especially for testing) if indivual function for each movement
            case 1 : //Up
                {
                    (*i)->moveUp();
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
                            (*i)->moveDown();
                        }
                    }
                }
                break;
            case 2 :  //Down
                {
                    (*i)->moveDown();
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
                            (*i)->moveUp();
                        }
                    }
                }
                break;
            case 3 : //Left
                {
                    (*i)->moveLeft();
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
                            (*i)->moveRight();
                        }
                    }
                }
                break;
            case 4 : //Right
                {
                    (*i)->moveRight();
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
                }
                break;
            }
        }
    }
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

//cannot pass superclass vector of pointers to base class class vector of pointers
/*
shared_ptr<Entity> MazeHandler::collision(shared_ptr<Entity> movingEntity, vector<shared_ptr<Entity>) //move to PlayerHandley (& Player Handler??)
{
    auto testEntities = maze_->getWalls();
    for(auto testEntity = testEntities.begin(); testEntity != testEntities.end(); ++testEntity)
    {
        if(movingEntity->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return *testEntity;
            }
    }
    return movingEntity;
}
*/

shared_ptr<Entity> MazeHandler::playerCollision(shared_ptr<Player> player) //move to PlayerHandler
{
    auto testWalls = maze_->getWalls();
    for(auto testEntity = testWalls.begin(); testEntity != testWalls.end(); ++testEntity)
    {
        if(player->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }

    auto testFruits = maze_->getFruits();
    for(auto testEntity = testFruits.begin(); testEntity != testFruits.end(); ++testEntity)
    {
        if(player->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    auto testKeys = maze_->getKeys();
    for(auto testEntity = testKeys.begin(); testEntity != testKeys.end(); ++testEntity)
    {
        if(player->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    auto testDoors = maze_->getDoors();
    for(auto testEntity = testDoors.begin(); testEntity != testDoors.end(); ++testEntity)
    {
        if(player->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    auto testPowerPellets = maze_->getPowerPellets();
    for(auto testEntity = testPowerPellets.begin(); testEntity != testPowerPellets.end(); ++testEntity)
    {
        if(player->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    return player;
    //cannot pass superclass vector of pointers to base class class vector of pointers
    /*
    auto collideEntity = collision(player, maze->getWalls());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_->getFruit());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_->getKeys());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_->getDoors());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}

    collideEntity = collision(player, maze_->getPowerPellets());
    if(typeid(collideEntity) != typeid(Player)){return collideEntity;}
    */
}
//move to PlayerHandler
bool MazeHandler::resolveCollision(shared_ptr<Player> player)//player required for future developemnt e.g. multiplayer
{
    bool reverseMovement = false; //change initiliasation
    auto collideEntity = playerCollision(player);
    if(typeid(collideEntity) != typeid(player))
    {
        if(typeid(collideEntity) == typeid(Wall))
        {
            reverseMovement = true;
        }
        else if(typeid(collideEntity) == typeid(Fruit))
        {
            auto it = find(maze_->getFruits().begin(), maze_->getFruits().end(), collideEntity);
            auto index = maze_->getFruits().begin() + distance(maze_->getFruits().begin(), it);
            maze_->getFruits().erase(index);

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
            auto index = maze_->getPowerPellets().begin() + distance(maze_->getPowerPellets().begin(), it);
            maze_->getPowerPellets().erase(index);

            powerPellets++;
        }
        else if(typeid(collideEntity) == typeid(Enemy))
        {
            if(powerPellets > 0)
            {
                collideEntity->setPosition(collideEntity->getInitialX(),collideEntity->getInitialY());
            }
            else
            {
                isPlayerDead = true;
            }
        }
    }
    return reverseMovement;
}
//move to PlayerHandler
void MazeHandler::playerMoveDown()
{
    auto player = maze_->getPlayer();
    player->moveDown();
    auto reverseMovement = resolveCollision(player);
    if(reverseMovement){player->moveUp();}
}
//move to PlayerHandler
void MazeHandler::playerMoveUp()
{
    auto player = maze_->getPlayer();
    player->moveUp();
    auto reverseMovement = resolveCollision(player);
    if(reverseMovement){player->moveDown();}
}
//move to PlayerHandler
void MazeHandler::playerMoveLeft()
{
    auto player = maze_->getPlayer();
    player->moveLeft();
    auto reverseMovement = resolveCollision(player);
    if(reverseMovement){player->moveRight();}
}
//move to PlayerHandler
void MazeHandler::playerMoveRight()
{
    auto player = maze_->getPlayer();
    player->moveRight();
    auto reverseMovement = resolveCollision(player);
    if(reverseMovement){player->moveLeft();}
}
//move to PlayerHandler
void MazeHandler::updatePlayer()
{
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
    //walls
    for(auto i = walls_.begin(); i != walls_.end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //fruits
    for(auto i = fruits_.begin(); i != fruits_.end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //keys
    for(auto i = keys_.begin(); i != keys_.end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //doors
    for(auto i = doors_.begin(); i != doors_.end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //Enemies
    for(auto i = enemies_.begin(); i != enemies_.end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //Player
    window_->draw(*(maze_->getPlayer()->getEntity()));

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
