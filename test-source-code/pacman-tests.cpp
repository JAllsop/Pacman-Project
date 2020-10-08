#include "../game-source-code/game.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("Player Basic Movement")
{
    auto testPlayer = Player(blockSize, blockSize, sf::Color::Blue);
    testPlayer.setPosition(500, 500);

    SUBCASE("Move Down")
    {
        auto y = testPlayer.getY();
        testPlayer.moveDown();
        CHECK(y + blockSize == testPlayer.getY());
    }
    SUBCASE("Move Up")
    {
        auto y = testPlayer.getY();
        testPlayer.moveUp();
        CHECK(y - blockSize == testPlayer.getY());
    }
    SUBCASE("Move Right")
    {
        auto x = testPlayer.getX();
        testPlayer.moveRight();
        CHECK(x + blockSize == testPlayer.getX());
    }
    SUBCASE("Move Left")
    {
        auto x = testPlayer.getX();
        testPlayer.moveLeft();
        CHECK(x - blockSize == testPlayer.getX());
    }
}

TEST_CASE("Enemy Basic Movement")
{
    auto testEnemy = Enemy(blockSize, blockSize, sf::Color::Blue);
    testEnemy.setPosition(500, 500);

    SUBCASE("Move Down")
    {
        auto y = testEnemy.getY();
        testEnemy.moveDown();
        CHECK(y + blockSize == testEnemy.getY());
    }
    SUBCASE("Move Up")
    {
        auto y = testEnemy.getY();
        testEnemy.moveUp();
        CHECK(y - blockSize == testEnemy.getY());
    }
    SUBCASE("Move Right")
    {
        auto x = testEnemy.getX();
        testEnemy.moveRight();
        CHECK(x + blockSize == testEnemy.getX());
    }
    SUBCASE("Move Left")
    {
        auto x = testEnemy.getX();
        testEnemy.moveLeft();
        CHECK(x - blockSize == testEnemy.getX());
    }
}

TEST_CASE("Logic Layer Test")
{

    auto window = make_shared<sf::RenderWindow>(sf::VideoMode(600, 800, 32), "Unit Test");
    auto testInstance = MazeHandler(window);
    testInstance.init("resources/maze_test");
    testInstance.run();
}

//ensures console doesn't close upon test completion when running .exe
int main(int argc, char** argv) {
    doctest::Context context;
    int res = context.run();
    if(context.shouldExit())
        return res;

    system("pause");
}

