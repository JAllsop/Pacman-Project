#include "controller.h"

Controller::Controller()
{
    //ctor
}

Controller::~Controller()
{
    //dtor
}

void Controller::control(shared_ptr<Entity> player)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if(player->getTop() > 0)
        {
            player->moveUp();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(player->getBottom() < 900)
        {
            player->moveDown();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if(player->getRight() < 1600)
        {
            player->moveRight();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(player->getLeft() > 0)
        {
            player->moveLeft();
        }
    }
}

void Controller::controlAI(shared_ptr<Enemy> enemy)
{

}
