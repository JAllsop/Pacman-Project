#include "LoseState.h"

LoseState::LoseState(shared_ptr<sf::RenderWindow> window) : State(), window_{window}
{
    loadAssets();
    sf::Text text1;
    sf::Text text2;
    text1.setFont(font);
    text2.setFont(font);
    text1.setString("GameOver");
    text2.setString("You Lose");
    text1.setPosition(sf::Vector2f(0 ,0));
    text2.setPosition(sf::Vector2f(0,50));
    texts_.push_back(text1);
    texts_.push_back(text2);
    //ctor
}

LoseState::~LoseState()
{
    //dtor
}

void LoseState::run()
{
    window_->clear();
    window_->draw(texts_.at(0));
    window_->draw(texts_.at(1));
    window_->display();
}

void LoseState::loadAssets()
{
    if(!font.loadFromFile("resources/sansation.ttf"))
    {
        //throw something
        system("pause");
    }
}

void LoseState::update()
{

}
