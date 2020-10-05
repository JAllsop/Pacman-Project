#include "maze.h"

Maze::Maze(shared_ptr<sf::RenderWindow> window) : window_{window}
{
    startXPos = 50;// control maze top left location X
    startYPos = 50;// control maze top left location Y

    // all entities have the same dimension, this makes it easier to work with
    entityWidth_ = 40.0;
    entityHeight_ = 40.0;
    maxFruits = 0;
    // Make sure containers are empty
    char_.clear();
    maze_.clear();

    init();
}

Maze::~Maze()
{
    //dtor
}

vector<vector<shared_ptr<Entity>>> Maze::getMaze()
{
    return maze_;
}

vector<vector<char>> Maze:: getCharMaze()
{
    return char_;
}

int Maze::getMaxFruits()
{
    return maxFruits;
}

void Maze::init()
{
    read();
    setUp();
    update();
}

void Maze::read()
{
    // we need to check if this fails
    auto temp = ' ';
    ifstream mazeFile;
    mazeFile.open(level_);
    while(!mazeFile.eof())
    {
        for(auto i = 0; i < MAX_MAZE_X; ++i)
        {
            char_.push_back(vector<char>());
            for(auto j = 0; j < MAX_MAZE_Y; ++j)
            {
                mazeFile >> temp;
                char_[i].push_back(temp);
            }
        }
    }
    mazeFile.close();
}

void Maze::setUp()
{
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        maze_.push_back(vector<shared_ptr<Entity>>());
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(char_[i][j] == 'w')
            {
                auto wall_ = make_shared<Wall>(entityWidth_,entityHeight_,sf::Color::Blue);
                walls_.push_back(wall_);
                maze_[i].push_back(wall_);
            }
            else if(char_[i][j] == 'p')
            {
                player_= make_shared<Player>(entityWidth_,entityHeight_,sf::Color::Green);
                maze_[i].push_back(player_);
            }
            else if(char_[i][j] == 'e')
            {
                enemy_= make_shared<Enemy>(entityWidth_,entityHeight_,sf::Color::Red);
                maze_[i].push_back(enemy_);
            }
            else if(char_[i][j] == '.')
            {
                auto path_ = make_shared<Path>(entityWidth_,entityHeight_,sf::Color::Transparent);
                maze_[i].push_back(path_);
            }
            else if(char_[i][j] == 'k')
            {
                auto key_ = make_shared<Key>(entityWidth_,entityHeight_,sf::Color::Yellow);
                maze_[i].push_back(key_);
            }
            else if(char_[i][j] == 'd')
            {
                auto door_ = make_shared<Door>(entityWidth_,entityHeight_,sf::Color(53,19,0));
                maze_[i].push_back(door_);
            }
            else if(char_[i][j] == 'f')
            {
                auto fruit_ = make_shared<Fruit>(entityWidth_,entityHeight_,sf::Color(166,61,0));
                maze_[i].push_back(fruit_);
                maxFruits++;
            }
            else if(char_[i][j] == 'u')
            {
                auto powerPellet_ = make_shared<PowerPellet>(entityWidth_,entityHeight_,sf::Color::White);
                maze_[i].push_back(powerPellet_);
            }
        }
    }
}

void Maze::update()// Screen related this is suppose to be on the display part
{
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if (i == 0 && j == 0)
            {
                maze_[i][j]->setPosition(startXPos,startYPos);
            }
            auto x = maze_[i][j]->getX();
            auto y = maze_[i][j]->getY();
            if(j<MAX_MAZE_Y-1)
            {
                maze_[i][j+1]->setPosition(x+entityWidth_,y);
            }
            if(j==MAX_MAZE_Y-1)
            {
                maze_[i][j]->setPosition(x,y);
            }
        }
        auto x = maze_[i][8]->getX();
        auto y = maze_[i][8]->getY();
        if(i<MAX_MAZE_X-1)
        {
            maze_[i+1][0]->setPosition(x-((8)*entityWidth_), y + entityHeight_);
        }
        if(i==MAX_MAZE_X-1)
        {
            maze_[i][0]->setPosition(x-((8)*entityWidth_), y);
        }
    }
}

void Maze::loadAssets()
{
}

void Maze::setLevel(string level)
{
    level = level_;
}
