#include "Score.h"

Score::Score(shared_ptr<sf::RenderWindow> window) : window_{window}
{
    loadAssets();
    score_.setFont(font_);
    //ctor
}

Score::~Score()
{
    //dtor
}

void Score::update(int fruits)
{
    stringstream ss;
    ss<<fruits;
    score_.setString(ss.str().c_str());
    score_.setPosition(sf::Vector2f(1000,0));
}

void Score::render()
{
    window_->draw(score_);
}

void Score::loadAssets()
{
    if(!font_.loadFromFile("resources/sansation.ttf"))
    {
        //throw something
        system("pause");
    }
}
