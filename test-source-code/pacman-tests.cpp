#include "../game-source-code/game.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("Player Basic Movement:")
{
    auto testPlayer = Player(blockSize, blockSize, sf::Color::Blue);
    testPlayer.setPosition(500, 500);
    auto y{0};
    auto x{0};

    SUBCASE("Position Allocation")
    {
        CHECK(testPlayer.getY() == 500);
        CHECK(testPlayer.getX() == 500);
    }
    SUBCASE("Move Down")
    {
        y = testPlayer.getY();
        testPlayer.moveDown();
        CHECK(testPlayer.getY() == y + blockSize);
    }
    SUBCASE("Move Up")
    {
        y = testPlayer.getY();
        testPlayer.moveUp();
        CHECK(testPlayer.getY() == y - blockSize);
    }
    SUBCASE("Move Right")
    {
        x = testPlayer.getX();
        testPlayer.moveRight();
        CHECK(testPlayer.getX() == x + blockSize);
    }
    SUBCASE("Move Left")
    {
        x = testPlayer.getX();
        testPlayer.moveLeft();
        CHECK(testPlayer.getX() == x - blockSize);
    }
}

TEST_CASE("Enemy Basic Movement")
{
    auto testEnemy = Enemy(blockSize, blockSize, sf::Color::Blue);
    testEnemy.setPosition(500, 500);
    auto y{0};
    auto x{0};

    SUBCASE("Position Allocation")
    {
        CHECK(testEnemy.getY() == 500);
        CHECK(testEnemy.getX() == 500);
    }
    SUBCASE("-Move Down")
    {
        y = testEnemy.getY();
        testEnemy.moveDown();
        CHECK(testEnemy.getY() == y + blockSize);
    }
    SUBCASE("-Move Up")
    {
        y = testEnemy.getY();
        testEnemy.moveUp();
        CHECK(testEnemy.getY() == y - blockSize);
    }
    SUBCASE("-Move Right")
    {
        x = testEnemy.getX();
        testEnemy.moveRight();
        CHECK(testEnemy.getX() == x + blockSize);
    }
    SUBCASE("-Move Left")
    {
        x = testEnemy.getX();
        testEnemy.moveLeft();
        CHECK(testEnemy.getX() == x - blockSize);
    }
}

TEST_CASE("Entity Interactions")
{
    auto window = make_shared<sf::RenderWindow>(sf::VideoMode(1600, 900), "Unit Test");
    auto testInstance = MazeHandler(window);
    testInstance.init("resources/maze_test.txt");
    auto playerHandler = testInstance.getPlayerHandler();
    auto enemyHandler = testInstance.getEnemyHandler();
    //testInstance.run();

    SUBCASE("Player Traversal:")
    {
        auto y{0};
        auto x{0};
        SUBCASE("-Standard Movement")
        {
            SUBCASE("--Move Down")
            {
                y = testInstance.getMaze()->getPlayer()->getY();
                playerHandler->moveDown();
                CHECK(testInstance.getMaze()->getPlayer()->getY() == y + blockSize);
            }
            SUBCASE("--Move Up")
            {
                y = testInstance.getMaze()->getPlayer()->getY();
                playerHandler->moveUp();
                CHECK(testInstance.getMaze()->getPlayer()->getY() == y - blockSize);
            }
            SUBCASE("--Move Right")
            {
                x = testInstance.getMaze()->getPlayer()->getX();
                playerHandler->moveRight();
                CHECK(testInstance.getMaze()->getPlayer()->getX() == x + blockSize);
            }
            SUBCASE("--Move Left")
            {
                x = testInstance.getMaze()->getPlayer()->getX();
                playerHandler->moveLeft();
                CHECK(testInstance.getMaze()->getPlayer()->getX() == x - blockSize);
            }
        }
        SUBCASE("-Collisions")
        {
            SUBCASE("--Wall")
            {
                x = testInstance.getMaze()->getPlayer()->getX();
                playerHandler->moveRight();
                playerHandler->moveRight();
                CHECK(testInstance.getMaze()->getPlayer()->getX() == x + blockSize);
            }
        }
    }
    //system("pause");
}

//ensures console doesn't close upon test completion when running .exe
int main(int argc, char** argv) {
    doctest::Context context;
    int res = context.run();
    if(context.shouldExit())
        return res;

    system("pause");
}

