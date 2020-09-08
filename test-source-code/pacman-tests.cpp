#include "../game-source-code/game.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


TEST_CASE("test down movement")
{
    auto testPlayer = Player(1, 1);
    auto y = testPlayer.getY();
    testPlayer.moveDown();
    CHECK(y +1 == testPlayer.getY());
}

TEST_CASE("test right movement")
{
    auto testPlayer = Player(40, 40);
    auto x = testPlayer.getX();
    testPlayer.moveRight();
    CHECK(x +1 == testPlayer.getX());
}


TEST_CASE("test left movement")
{
    auto testPlayer = Player(40, 40);
    testPlayer.setPosition(10, 10);
    auto x = testPlayer.getX();
    testPlayer.moveLeft();
    CHECK(x - 1 == testPlayer.getX());
}

TEST_CASE("test up movement")
{
    auto testPlayer = Player(40, 40);
    testPlayer.setPosition(10, 10);
    auto y = testPlayer.getY();
    testPlayer.moveUp();
    CHECK(y - 1 == testPlayer.getY());
}