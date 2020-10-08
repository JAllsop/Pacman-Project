#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <sstream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

using namespace std;

class Score
{
    public:
        Score(shared_ptr<sf::RenderWindow> window);
        virtual ~Score();
        void update(int fruits);
        void render();
        void loadAssets();
    protected:

    private:
        sf::Text score_;
        sf::Font font_;
        shared_ptr<sf::RenderWindow> window_;

};

#endif // SCORE_H
