#include "PlayerHandler.h"

PlayerHandler::PlayerHandler(shared_ptr<sf::RenderWindow> window, shared_ptr<Entity> player) : window_{window}, player_{player}
{
    controller_ = make_shared<Controller>();
    //ctor
}

PlayerHandler::~PlayerHandler()
{
    //dtor
}

void PlayerHandler::run()
{
    update();
}

void PlayerHandler::update()
{
    controller_->control(player_);
}
