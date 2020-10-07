#include "maze.h"

Maze::Maze(shared_ptr<sf::RenderWindow> window) : window_{window}, level_{"resources/maze.txt"}, maxFruits{0}
{

    // Make sure containers are empty

    init();
}

Maze::~Maze()
{
    //dtor
}

void Maze::init()
{
    read();
}

void Maze::read()
{
    //error check needed
    ifstream fileReader(level_);
    //fileReader.open(level_);
    while(fileReader)
    {
        auto line = ""s;
        auto lineNum{0};
        while (getline(fileReader, line))
        {
            for(auto i = 0; i != line.size(); ++i)
            {
                //cout << line.at(i);
                loadEntity(line.at(i), i, lineNum);
            }
            //cout << "\n";
            lineNum++;
        }
    }
    fileReader.close();
}

void Maze::loadEntity(const char entity_, const int x, const int y)
{
    switch(entity_)
    {//remove setPosition & Colour for alternate or standard object constructor
    case 'w' :
        {
            auto wall_ = make_shared<Wall>(blockSize,blockSize,sf::Color::Blue);
            wall_->setPosition(x*blockSize, y*blockSize);
            walls_.push_back(wall_);
        }
        break;
    case 'f' :
        {
            auto fruit_ = make_shared<Fruit>(blockSize,blockSize,sf::Color(166,61,0));
            fruit_->setPosition(x*blockSize, y*blockSize);
            fruits_.push_back(fruit_);
            maxFruits++;
        }
        break;
    case 'd' :
        {
            auto door_ = make_shared<Door>(blockSize,blockSize,sf::Color(53,19,0));
            door_->setPosition(x*blockSize, y*blockSize);
            doors_.push_back(door_);
        }
        break;
    case 'k' :
        {
            auto key_ = make_shared<Key>(blockSize,blockSize,sf::Color::Yellow);
            key_->setPosition(x*blockSize, y*blockSize);
            keys_.push_back(key_);
        }
        break;
    case 'u' :
        {
            auto powerPellet_ = make_shared<PowerPellet>(blockSize,blockSize,sf::Color::White);
            powerPellet_->setPosition(x*blockSize, y*blockSize);
            powerPellets_.push_back(powerPellet_);
        }
        break;
    case 'e' :
        {
            auto enemy_= make_shared<Enemy>(blockSize,blockSize, sf::Color::Red);
            enemy_->setPosition(x*blockSize, y*blockSize);
            enemies_.push_back(enemy_);
        }
        break;
    case 'p' :
        {
            player_= make_shared<Player>(blockSize,blockSize,sf::Color::Green);
            player_->setPosition(x*blockSize, y*blockSize);
        }
        break;
   }
}

shared_ptr<Player> Maze::getPlayer()
{
    return player_;
}

vector<shared_ptr<Enemy>> Maze::getEnemies()
{
    return enemies_;
}

vector<shared_ptr<Key>> Maze::getKeys()
{
    return keys_;
}

vector<shared_ptr<Door>> Maze::getDoors()
{
    return doors_;
}

vector<shared_ptr<Wall>> Maze::getWalls()
{
    return walls_;
}

vector<shared_ptr<Fruit>> Maze::getFruits()
{
    return fruits_;
}

vector<shared_ptr<PowerPellet>> Maze::getPowerPellets()
{
    return powerPellets_;
}

int Maze::getMaxFruits()
{
    return maxFruits;
}

void Maze::setLevel(string level)
{
    level = level_;
}
