#include "Score.h"

Score::Score()
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
    ss << fruits;
    string output = "Score: ";
    output.append(ss.str().c_str());
    score_.setString(output);
    score_.setPosition(sf::Vector2f(1000,0));
}

void Score::render(shared_ptr<sf::RenderWindow> window)
{
    window->draw(score_);
}

void Score::loadAssets()
{
    if(!font_.loadFromFile("resources/sansation.ttf"))
    {
        //throw something
        system("pause");
    }
}
