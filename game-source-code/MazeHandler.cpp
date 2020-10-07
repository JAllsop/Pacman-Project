#include "MazeHandler.h"

MazeHandler::MazeHandler(shared_ptr<sf::RenderWindow> window) : window_{window}, random{0}, keys{0}, fruits{0}, powerPellets{0}
{
    // Objects
    maze_ = make_shared<Maze>(window_);
    playerHandler_ = make_shared<PlayerHandler>(window_, maze_);

    loadLevel();

    // Time var
    enemySpeed1 = sf::milliseconds(400);
    enemySpeed2 = sf::milliseconds(400);
    playerSpeed = sf::milliseconds(350);
    powerPelletTime = sf::milliseconds(8000);

    // Directions, not used yet
    isPlayerDead = false;
    isAllFruitsEaten = false;

    srand(time(0));
}

MazeHandler::~MazeHandler()
{
    //dtor
}
//just needed for handlers???
void MazeHandler::loadLevel()
{
    enemies_ = maze_->getEnemies();
    player_ = maze_->getPlayer();
    walls_ = maze_->getWalls();
    keys_ = maze_->getKeys();
    fruits_ = maze_->getFruits();
    powerPellets_ = maze_->getPowerPellets();
    doors_ = maze_->getDoors();
}

void MazeHandler::run()
{
    if(enemyClock1.getElapsedTime() >= enemySpeed1)
    {
        updateAI(0);
        //enemyHandler_->run();
        enemyClock1.restart();
    }
    if(enemyClock2.getElapsedTime() >= enemySpeed2)
    {
        updateAI(1);
        //enemyHandler_->run();
        enemyClock2.restart();
    }
    if(playerClock.getElapsedTime() >= playerSpeed)
    {
        //updatePlayer();
        playerHandler_->update();
        playerClock.restart();
    }
    if(powerPellets > 0)
    {
        if(powerPelletClock.getElapsedTime() >= powerPelletTime){
            powerPellets--;
            powerPelletClock.restart();
        }
    }else{powerPelletClock.restart();}

    if(fruits == maze_->getMaxFruits())
    {
        isPlayerDead = true;
    }
    render();
}

bool MazeHandler::enemyMoveDown(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveDown();
    auto hasMoved = true;
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
    return hasMoved;
}

bool MazeHandler::enemyMoveUp(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveUp();
    auto hasMoved = true;
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
            (*i)->moveDown();
        }
    }
    return hasMoved;
}

bool MazeHandler::enemyMoveRight(vector<shared_ptr<Enemy>>::iterator i)
{
(*i)->moveRight();
    auto hasMoved = true;
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
    return hasMoved;
}

bool MazeHandler::enemyMoveLeft(vector<shared_ptr<Enemy>>::iterator i)
{
    (*i)->moveLeft();
    auto hasMoved = true;
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
    return hasMoved;
}

void MazeHandler::updateAI(int enemyNum) //move to EnemyHandler
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

shared_ptr<Entity> MazeHandler::playerCollision() //move to PlayerHandler
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

//move to PlayerHandler
bool MazeHandler::resolveCollision()
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
                isPlayerDead = true;
            }
        }
    }
    return reverseMovement;
}
//move to PlayerHandler
void MazeHandler::playerMoveDown()
{
    player_->moveDown();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveUp();}
}
//move to PlayerHandler
void MazeHandler::playerMoveUp()
{
    player_->moveUp();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveDown();}
}
//move to PlayerHandler
void MazeHandler::playerMoveLeft()
{
    player_->moveLeft();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveRight();}
}
//move to PlayerHandler
void MazeHandler::playerMoveRight()
{
    player_->moveRight();
    auto reverseMovement = resolveCollision();
    if(reverseMovement){player_->moveLeft();}
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
    window_->draw(*(maze_->getPlayer()->getEntity()));

    window_->display();
}

shared_ptr<Maze> MazeHandler::getMaze()
{
    return maze_;
}

bool MazeHandler::getPlayerState()
{
    return isPlayerDead;
}

bool MazeHandler::allFruitsEaten()
{
    return isAllFruitsEaten;
}
