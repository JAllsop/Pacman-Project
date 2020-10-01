#include "MenuState.h"

MenuState::MenuState(shared_ptr<sf::RenderWindow> window) : State(), window_{window}
{
    cout << "create menuState" << endl;
    loadAssets();
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    text4.setFont(font);
    text5.setFont(font);
    text1.setString("Press Enter to play");
    text2.setString("Use WASD move up,left,down,right respectively");
    text3.setString("Color-Code: Red-Ghost, White-PowerPellet, Orange-fruit, Yellow-Key, Brown-Door, Blue-Wall");
    text4.setString("Note: If a key is taken, you need to be at the door to open it");
    text5.setString("Note: If a PowerPellet is eaten the ghost turns whites");
    text1.setPosition(sf::Vector2f(0,0));
    text2.setPosition(sf::Vector2f(0,0+100));
    text3.setPosition(sf::Vector2f(0,0+200));
    text4.setPosition(sf::Vector2f(0,0+300));
    text5.setPosition(sf::Vector2f(0,0+400));
    texts_.push_back(text1);
    texts_.push_back(text2);
    texts_.push_back(text3);
    texts_.push_back(text4);
    texts_.push_back(text5);
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
    window_->draw(texts_.at(2));
    window_->draw(texts_.at(3));
    window_->draw(texts_.at(4));
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

bool MenuState::isStateEnd()
{
    //blah blah
}
