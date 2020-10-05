#ifndef MAZE_H
#define MAZE_H

#include "player.h"
#include "enemy.h"
#include "Wall.h"
#include "Path.h"
#include "key.h"
#include "Door.h"
#include "fruit.h"
#include "PowerPellet.h"

#define MAX_MAZE_X 15
#define MAX_MAZE_Y 19

class Maze
{
public:
    Maze(shared_ptr<sf::RenderWindow> window);
    virtual ~Maze();
    // Functions
    void init();
    void read();
    void setUp();
    void loadEntity(const char entity_m, const int x, const int y);
    void update();
    void loadAssets();
    //getters
    int getMaxFruits();
    // Returned
    vector<vector<shared_ptr<Entity>>> getMaze();
    vector<vector<char>> getCharMaze();
    void setLevel(string level_);

protected:

private:
    // Variables
    vector<vector<char>> char_;// holder for inputs
    vector<shared_ptr<Enemy>> enemies_;
    vector<shared_ptr<Key>> keys_;
    vector<shared_ptr<Fruit>> fruits_;
    vector<shared_ptr<Door>> doors_;
    vector<shared_ptr<Wall>> walls_;
    vector<shared_ptr<PowerPellet>> powerPellets_;
    float entityWidth_;
    float entityHeight_;
    float startXPos;
    float startYPos;
    shared_ptr<sf::RenderWindow> window_;
    // Entity variables
    vector<vector<shared_ptr<Entity>>> maze_;// actually returned by the maze
    // Movable entities
    shared_ptr<Player> player_;
    shared_ptr<Enemy> enemy_;
    // Static entities
    //shared_ptr<Wall> wall_;
    //shared_ptr<Path> path_;
    //shared_ptr<Key> key_;
    //shared_ptr<Fruit> fruit_;
    //shared_ptr<Door> door_;
    //shared_ptr<PowerPellet> powerPellet_;
    //Var
    int maxFruits;
    string level_;
};

#endif // MAZE_H
