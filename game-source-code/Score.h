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
        Score();
        virtual ~Score();
        void update(int fruits);
        void render(shared_ptr<sf::RenderWindow> window);
        void loadAssets();
    protected:

    private:
        sf::Text score_;
        sf::Font font_;

};

#endif // SCORE_H
