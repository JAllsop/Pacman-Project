#include "MazeHandler.h"

MazeHandler::MazeHandler(shared_ptr<sf::RenderWindow> window) : window_{window}, random{0}, keys{0}, fruits{0}, powerPellets{0}
{
    // Objects
    maze_ = make_shared<Maze>(window);
    enemies_ = maze_->getEnemies();
    player_ = maze_->getPlayer();
    //auto drawEntity = player_->getEntity();
    //cout << player_->getX() << "\n";
    walls_ = maze_->getWalls();
    keys_ = maze_->getKeys();
    fruits_ = maze_->getFruits();
    powerPellets_ = maze_->getPowerPellets();
    doors_ = maze_->getDoors();
    //maze_->init();
    // Time var
    milli1 = sf::milliseconds(110);
    milli2 = sf::milliseconds(100);
    milli3 = sf::milliseconds(5000);
    // Directions, not used yet
    isPlayerDead = false;
    isAllFruitsEaten = false;
    //window_->clear();
    //window_->display();

    //window_->draw(drawEntity);
    //window_->display();
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
    if(powerPellets > 0)
    {
        if(elapsed3 >= milli3){
            powerPellets = 0;
            clock3.restart();
        }
    }else{clock3.restart();}

    if(fruits == maze_->getMaxFruits())
    {
        isPlayerDead = true;
    }
    render();
}

void MazeHandler::updateAI() //move to EnemyHandler
{
    //enumerate direction?
    auto hasMoved = false;
    srand(time(0));
    auto enemies = maze_->getEnemies();
    if(random == 0)
    {
        random = (rand()%4)+1;
    }
    for (auto i = enemies.begin(); i != enemies.end(); ++i)
    {
        while(hasMoved == false)
        {
            switch(random)
            {//better seperation (especially for testing) if indivual function for each movement
            case '1' : //Up
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
                            random = (rand()%4)+1;
                            (*i)->moveDown();
                        }
                    }
                }
                break;
            case '2' :  //Down
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
                            random = (rand()%4)+1;
                            (*i)->moveUp();
                        }
                    }
                }
                break;
            case '3' : //Left
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
                            random = (rand()%4)+1;
                            (*i)->moveRight();
                        }
                    }
                }
                break;
            case '4' : //Right
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
                            random = (rand()%4)+1;
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
    auto testEntities = maze_->getWalls();
    auto player = maze_->getPlayer();
    if (enemy->getEntity()->getGlobalBounds().intersects(player->getEntity()->getGlobalBounds()))
    {
        return player;
    }
    for(auto testEntity = testEntities.begin(); testEntity != testEntities.end(); ++testEntity)
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
    window_->display();
    //walls
    for(auto i = walls_.begin(); i != walls_.end(); ++i)
    {
        auto drawEntity = (*i)->getEntity();
        window_->draw(*drawEntity);
    }
    //keys
    for(auto i = maze_->getKeys().begin(); i != maze_->getKeys().end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //doors
    for(auto i = maze_->getDoors().begin(); i != maze_->getDoors().end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //Enemies
    for(auto i = maze_->getEnemies().begin(); i != maze_->getEnemies().end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
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
