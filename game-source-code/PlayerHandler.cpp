#include "PlayerHandler.h"

PlayerHandler::PlayerHandler(shared_ptr<sf::RenderWindow> window, shared_ptr<Maze> maze) : window_{window}, maze_{maze}
{
    enemies_ = maze_->getEnemies();
    player_ = maze_->getPlayer();
    walls_ = maze_->getWalls();
    keys_ = maze_->getKeys();
    fruits_ = maze_->getFruits();
    powerPellets_ = maze_->getPowerPellets();
    doors_ = maze_->getDoors();
}

PlayerHandler::~PlayerHandler()
{

}

void PlayerHandler::update()
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
    bool reverseMovement = false; //change initiliasation
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

            //fruits++; property of player todo
        }
        else if(typeid(*collideEntity) == typeid(Key))
        {
            auto it = find(keys_.begin(), keys_.end(), collideEntity);
            auto index = keys_.begin() + distance(keys_.begin(), it);
            keys_.erase(index);

            //keys++; property of player todo
        }
        else if(typeid(*collideEntity) == typeid(Door))
        {
            //if(keys > 0)
            //{
                auto it = find(doors_.begin(), doors_.end(), collideEntity);
                auto index = doors_.begin() + distance(doors_.begin(), it);
                doors_.erase(index);

                //keys--; property of player todo
            //}
            //else
            //{
                reverseMovement = true;
            //}
        }
        else if(typeid(*collideEntity) == typeid(PowerPellet))
        {
            auto it = find(powerPellets_.begin(), powerPellets_.end(), collideEntity);
            auto index = powerPellets_.begin() + distance(powerPellets_.begin(), it);
            powerPellets_.erase(index);
            //change ghost colour
            //powerPellets++; property of player todo
        }
        else if(typeid(collideEntity) == typeid(Enemy))
        {
            //if(powerPellets > 0)
            //{
                //collideEntity->setPosition(collideEntity->getInitialX(),collideEntity->getInitialY());
            //}
            //else
            //{
                //isPlayerDead = true;
            //}
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
