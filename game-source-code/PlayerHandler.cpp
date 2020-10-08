#include "PlayerHandler.h"

PlayerHandler::PlayerHandler(shared_ptr<sf::RenderWindow> window, shared_ptr<Maze> maze) : window_{window}, keys{0}, fruits{0}, powerPellets{0}
{
    //maze_ = maze;
    enemies_ = maze->getEnemies();
    player_ = maze->getPlayer();
    walls_ = maze->getWalls();
    keys_ = maze->getKeys();
    fruits_ = maze->getFruits();
    powerPellets_ = maze->getPowerPellets();
    doors_ = maze->getDoors();
    maxFruits_ = maze->getMaxFruits();
    powerPelletTime = sf::milliseconds(8000);
}
PlayerHandler::~PlayerHandler()
{
    //dtor
}

bool PlayerHandler::update()
{
    if(powerPellets > 0)
    {
        if(powerPelletClock.getElapsedTime() >= powerPelletTime){
            powerPellets--;
            powerPelletClock.restart();
        }
    }
    else{powerPelletClock.restart();}
    playerMoveDown();
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
    if(fruits == maxFruits_)
    {
        return true;
    }
    return false;
}

void PlayerHandler::playerMoveDown()
{
    player_->moveDown();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveUp();}
}

void PlayerHandler::playerMoveUp()
{
    player_->moveUp();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveDown();}
}

void PlayerHandler::playerMoveLeft()
{
    player_->moveLeft();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveRight();}
}

void PlayerHandler::playerMoveRight()
{
    player_->moveRight();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveLeft();}
}

bool PlayerHandler::resolveCollision()
{
    auto reverseMovement = false; //change initiliasation
    auto collideEntity = playerCollision();
    if(typeid(collideEntity) != typeid(Player))
    {
        if(typeid(*collideEntity) == typeid(Wall))
        {
            reverseMovement = true;
        }
        else if(typeid(*collideEntity) == typeid(Fruit))
        {
            auto it = find(fruits_.begin(), fruits_.end(), collideEntity);
            auto index = fruits_.begin() + distance(fruits_.begin(), it);
            fruits_.erase(index);

            fruits++;
        }
        else if(typeid(*collideEntity) == typeid(Key))
        {
            auto it = find(keys_.begin(), keys_.end(), collideEntity);
            auto index = keys_.begin() + distance(keys_.begin(), it);
            keys_.erase(index);

            keys++;
        }
        else if(typeid(*collideEntity) == typeid(Door))
        {
            if(keys > 0)
            {
                auto it = find(doors_.begin(), doors_.end(), collideEntity);
                auto index = doors_.begin() + distance(doors_.begin(), it);
                doors_.erase(index);

                keys--;
            }
            else
            {
                reverseMovement = true;
            }
        }
        else if(typeid(*collideEntity) == typeid(PowerPellet))
        {
            auto it = find(powerPellets_.begin(), powerPellets_.end(), collideEntity);
            auto index = powerPellets_.begin() + distance(powerPellets_.begin(), it);
            powerPellets_.erase(index);
            //change ghost colour
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
                //isPlayerDead = true;
            }
        }
    }
    return reverseMovement;
}

shared_ptr<Entity> PlayerHandler::playerCollision() //move to PlayerHandler
{
    for(auto testEntity = walls_.begin(); testEntity != walls_.end(); ++testEntity)
    {
        if(player_->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    for(auto testEntity = fruits_.begin(); testEntity != fruits_.end(); ++testEntity)
    {
        if(player_->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    for(auto testEntity = keys_.begin(); testEntity != keys_.end(); ++testEntity)
    {
        if(player_->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    for(auto testEntity = doors_.begin(); testEntity != doors_.end(); ++testEntity)
    {
        if(player_->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    for(auto testEntity = powerPellets_.begin(); testEntity != powerPellets_.end(); ++testEntity)
    {
        if(player_->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    return player_;
}

void PlayerHandler::render()
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
    //power pellets
    for(auto i = powerPellets_.begin(); i != powerPellets_.end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //Enemies
    for(auto i = enemies_.begin(); i != enemies_.end(); ++i)
    {
        window_->draw(*((*i)->getEntity()));
    }
    //Player
    window_->draw(*(player_->getEntity()));

    window_->display();
}
