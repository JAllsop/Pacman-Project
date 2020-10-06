#include "maze.h"

Maze::Maze(shared_ptr<sf::RenderWindow> window) : window_{window}, level_{"resources/maze.txt"}
{
    //startXPos = 50;// control maze top left location X
    //startYPos = 50;// control maze top left location Y

    // all entities have the same dimension, this makes it easier to work with
    //entityWidth_ = 40.0;
    //entityHeight_ = 40.0;
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

void Maze::init()
{
    read();
    setUp();
    update();
}

void Maze::read()
{
    /*
    // we need to check if this fails
    auto temp = ' ';
    ifstream mazeFile(level_);
    //mazeFile.open(level_);
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
    */
    //error check needed
    ifstream fileReader(level_);
    fileReader.open(level_);
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
            auto enemy_= make_shared<Enemy>(blockSize,blockSize,sf::Color::Red);
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

/*
void Maze::setUp()
{
    for(int i = 0; i < MAX_MAZE_X; i++)
    {
        maze_.push_back(vector<shared_ptr<Entity>>());
        for(int j = 0; j < MAX_MAZE_Y; j++)
        {
            if(char_[i][j] == 'w')
            {
                auto wall_ = make_shared<Wall>(blockSize,blockSize,sf::Color::Blue);
                maze_[i].push_back(wall_);
            }
            else if(char_[i][j] == 'p')
            {
                player_= make_shared<Player>(blockSize,blockSize,sf::Color::Green);
                maze_[i].push_back(player_);
            }
            else if(char_[i][j] == 'e')
            {
                enemy_= make_shared<Enemy>(blockSize,blockSize,sf::Color::Red);
                maze_[i].push_back(enemy_);
            }
            else if(char_[i][j] == '.')
            {
                auto path_ = make_shared<Path>(blockSize,blockSize,sf::Color::Transparent);
                maze_[i].push_back(path_);
            }
            else if(char_[i][j] == 'k')
            {
                auto key_ = make_shared<Key>(blockSize,blockSize,sf::Color::Yellow);
                maze_[i].push_back(key_);
            }
            else if(char_[i][j] == 'd')
            {
                auto door_ = make_shared<Door>(blockSize,blockSize,sf::Color(53,19,0));
                maze_[i].push_back(door_);
            }
            else if(char_[i][j] == 'f')
            {
                auto fruit_ = make_shared<Fruit>(blockSize,blockSize,sf::Color(166,61,0));
                maze_[i].push_back(fruit_);
                maxFruits++;
            }
            else if(char_[i][j] == 'u')
            {
                auto powerPellet_ = make_shared<PowerPellet>(blockSize,blockSize,sf::Color::White);
                maze_[i].push_back(powerPellet_);
            }
        }
    }
}
*/
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
/*
vector<vector<shared_ptr<Entity>>> Maze::getMaze()
{
    return maze_;
}

vector<vector<char>> Maze:: getCharMaze()
{
    return char_;
}
*/
int Maze::getMaxFruits()
{
    return maxFruits;
}

/*
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
                maze_[i][j+1]->setPosition(x+blockSize,y);
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
            maze_[i+1][0]->setPosition(x-((8)*blockSize), y + blockSize);
        }
        if(i==MAX_MAZE_X-1)
        {
            maze_[i][0]->setPosition(x-((8)*blockSize), y);
        }
    }
}

void Maze::loadAssets()
{
}
*/
void Maze::setLevel(string level)
{
    level = level_;
}
