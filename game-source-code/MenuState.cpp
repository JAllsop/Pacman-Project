#include "MenuState.h"

MenuState::MenuState(shared_ptr<sf::RenderWindow> window) : State(), window_{window}
{
    cout << "create menuState" << endl;
    loadAssets();
    sf::Text text1;
    sf::Text text2;
    text1.setFont(font);
    text2.setFont(font);
    text1.setString("Press Enter to play");
    text2.setString("Use WASD move up,left,down,right respectively");
    text1.setPosition(sf::Vector2f(1600/2 - 100,900/2-100));
    text2.setPosition(sf::Vector2f(1600/2 - 300,900/2));
    texts_.push_back(text1);
    texts_.push_back(text2);
    //ctor
}

MenuState::~MenuState()
{
    //dtor
}

void MenuState::run()
{
    window_->clear();
    window_->draw(texts_.at(0));
    window_->draw(texts_.at(1));
    window_->display();
}

void MenuState::loadAssets()
{
    if(!font.loadFromFile("resources/sansation.ttf"))
    {
        //throw something
        system("pause");
    }
}

void MenuState::update()
{

}
