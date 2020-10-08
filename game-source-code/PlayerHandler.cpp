#include "PlayerHandler.h"

PlayerHandler::PlayerHandler(shared_ptr<Maze> maze) : keys{0}, powerPellets{0}, isPlayerDead{false}, isFruitFinished{false}, fruits{0}
{
    enemies_ = maze->getEnemies();
    player_ = maze->getPlayer();
    walls_ = maze->getWalls();
    keys_ = maze->getKeys();
    fruits_ = maze->getFruits();
    maxFruits = maze->getMaxFruits();

    powerPellets_ = maze->getPowerPellets();
    doors_ = maze->getDoors();

    score_ = make_unique<Score>();
    score_->update(0);

    powerPelletTime = sf::milliseconds(4000);
    playerSpeed = sf::milliseconds(150);
}
PlayerHandler::~PlayerHandler()
{
    //dtor
}

tuple<bool, bool> PlayerHandler::run()
{
    if(playerClock.getElapsedTime() >= playerSpeed)
    {
        update();
        playerClock.restart();
    }
    if(powerPellets > 0)
    {
        if(powerPelletClock.getElapsedTime() >= powerPelletTime){
            powerPellets--;
            if(powerPellets == 0)
            {
                for(auto i = enemies_.begin(); i != enemies_.end(); ++i)
                {
                    (*i)->setColor(sf::Color::Red);
                }
            }
            powerPelletClock.restart();
        }
    }
    return {isPlayerDead, isFruitFinished};
}



void PlayerHandler::update()
{
    if(powerPellets > 0)
    {
        if(powerPelletClock.getElapsedTime() >= powerPelletTime){
            powerPellets--;
            powerPelletClock.restart();
        }
    }
    else
    {
        powerPelletClock.restart();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        moveDown();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        moveUp();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        moveLeft();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        moveRight();
    }
}

void PlayerHandler::moveDown()
{
    player_->moveDown();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveUp();}
}

void PlayerHandler::moveUp()
{
    player_->moveUp();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveDown();}
}

void PlayerHandler::moveLeft()
{
    player_->moveLeft();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveRight();}
}

void PlayerHandler::moveRight()
{
    player_->moveRight();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveLeft();}
}

bool PlayerHandler::resolveCollision()
{
    auto reverseMovement = false;
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
            score_->update(fruits);
            if(fruits == maxFruits)
                {
                    isFruitFinished = true;
                }
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

            powerPellets++;

            for(auto i = enemies_.begin(); i != enemies_.end(); ++i)
            {
                (*i)->setColor(sf::Color::Magenta);
            }
        }
        else if(typeid(*collideEntity) == typeid(Enemy))
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

shared_ptr<Entity> PlayerHandler::playerCollision()
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
    for(auto testEntity = enemies_.begin(); testEntity != enemies_.end(); ++testEntity)
    {
        if(player_->getEntity()->getGlobalBounds().intersects((*testEntity)->getEntity()->getGlobalBounds()))
            {
                return (*testEntity);
            }
    }
    return player_;
}

void PlayerHandler::render(shared_ptr<sf::RenderWindow> window)
{
    window->clear();
    //walls
    for(auto i = walls_.begin(); i != walls_.end(); ++i)
    {
        window->draw(*((*i)->getEntity()));
    }
    //fruits
    for(auto i = fruits_.begin(); i != fruits_.end(); ++i)
    {
        window->draw(*((*i)->getEntity()));
    }
    //keys
    for(auto i = keys_.begin(); i != keys_.end(); ++i)
    {
        window->draw(*((*i)->getEntity()));
    }
    //doors
    for(auto i = doors_.begin(); i != doors_.end(); ++i)
    {
        window->draw(*((*i)->getEntity()));
    }
    //power pellets
    for(auto i = powerPellets_.begin(); i != powerPellets_.end(); ++i)
    {
        window->draw(*((*i)->getEntity()));
    }
    //Enemies
    for(auto i = enemies_.begin(); i != enemies_.end(); ++i)
    {
        window->draw(*((*i)->getEntity()));
    }
    //Player
    window->draw(*(player_->getEntity()));
    score_->render(window);

    window->display();
}
