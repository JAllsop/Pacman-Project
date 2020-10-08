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
    Maze();
    virtual ~Maze();

    // Functions
    void init();
    void read();

    //getters
    int getMaxFruits();
    shared_ptr<Player> getPlayer();
    vector<shared_ptr<Enemy>> getEnemies();
    vector<shared_ptr<Key>> getKeys();
    vector<shared_ptr<Door>> getDoors();
    vector<shared_ptr<Wall>> getWalls();
    vector<shared_ptr<Fruit>> getFruits();
    vector<shared_ptr<PowerPellet>> getPowerPellets();

    void setLevel(string level_);
protected:

private:
    void update();
    void setUp();
    void loadAssets();
    void loadEntity(const char entity_m, const int x, const int y);
    // Variables

    shared_ptr<Player> player_;
    vector<shared_ptr<Enemy>> enemies_;

    vector<shared_ptr<Key>> keys_;
    vector<shared_ptr<Fruit>> fruits_;
    vector<shared_ptr<Door>> doors_;
    vector<shared_ptr<Wall>> walls_;
    vector<shared_ptr<PowerPellet>> powerPellets_;

    int maxFruits;
    string level_;
};

#endif // MAZE_H
