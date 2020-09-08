#include "game.h"

Game::Game()
{

    gameWidth_ = 1600;
    gameHeight_ = 900;
    initWindow();

    isMenuState_ = true;
    isGameState_ = false;
    isEndState_ = false;

    menuState_ = make_shared<MenuState>(window_);
    gameState_ = make_shared<GameState>(window_);

    initState();
}

Game::~Game()
{
    //dtor
}

void Game::run()
{
    while(window_->isOpen())
    {
        updateEvents();
        updateStates();
        runState();
    }
}

void Game::updateEvents()
{
    while(window_->pollEvent(event_))
    {
        switch(event_.type)
        {
        case sf::Event::EventType::Closed:
            window_->close();
            break;
        case sf::Event::EventType::KeyPressed:
            if(sf::Keyboard::Enter == event_.key.code && isMenuState_ == true && isGameState_ == false && isEndState_ == false)
            {
                cout << "GameState" << endl;
                isMenuState_ = false;
                isGameState_ = true;
                isEndState_ = false;
            }
            break;
        }
    }
}

void Game::updateStates()
{
    // When we press backspace we want to go back to the menu state
    //if(stateContainer_.size() > MIN_NUM_STATES && isMenuState_ == true)
    //{
    //    stateContainer_.pop();
    //}
    if (!(stateContainer_.empty()) && isGameState_ == true)
    {
        stateContainer_.push(gameState_);
    }
    // Still need to add the end game state
}

void Game::runState()
{
    stateContainer_.top()->run();
}

void Game::initState()
{
    if (stateContainer_.empty() && isMenuState_ == true)
    {
        stateContainer_.push(menuState_);
    }
}

void Game::initWindow()
{
    window_ = make_shared<sf::RenderWindow>(sf::VideoMode(gameWidth_, gameHeight_), "SFML Pacman");
    window_->setVerticalSyncEnabled(true);
}

