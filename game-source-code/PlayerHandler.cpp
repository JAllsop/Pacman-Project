#include "PlayerHandler.h"

PlayerHandler::PlayerHandler(shared_ptr<sf::RenderWindow> window) : window_{window}
{
    player_ = make_shared<Player>(40,40);
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
    render();
}

void PlayerHandler::update()
{
    controller_->control(player_);
}

void PlayerHandler::render()
{
    window_->clear();
    window_->draw(*(player_->getEntity()));
    window_->display();
}
