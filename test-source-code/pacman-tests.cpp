#include "../game-source-code/game.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("test down movement")
{
    auto testPlayer = Player(40, 40);
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
