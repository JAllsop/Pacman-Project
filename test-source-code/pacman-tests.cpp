#include "../game-source-code/game.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("maze test")
{
    std::shared_ptr<sf::RenderWindow> window;
    window = make_shared<sf::RenderWindow>(sf::VideoMode(1600, 900), "test");
    auto testInstance = MazeHandler(window);

    window->setVerticalSyncEnabled(true);
}

TEST_CASE("test down movement")
{
    auto testPlayer = Player(40.0, 40.0, sf::Color::Green);
    auto y = testPlayer.getY();
    testPlayer.moveDown();
    CHECK(y +1 == testPlayer.getY());
}

/*
TEST_CASE("test right movement")
{
    auto testPlayer = MoveableEntity(40, 40);
    auto x = testPlayer.getX();
    testPlayer.moveRight();
    CHECK(x +1 == testPlayer.getX());
}


TEST_CASE("test left movement")
{
    auto testPlayer = MoveableEntity(40, 40);
    testPlayer.setPosition(10, 10);
    auto x = testPlayer.getX();
    testPlayer.moveLeft();
    CHECK(x - 1 == testPlayer.getX());
}

TEST_CASE("test up movement")
{
    auto testPlayer = MoveableEntity(40, 40);
    testPlayer.setPosition(10, 10);
    auto y = testPlayer.getY();
    testPlayer.moveUp();
    CHECK(y - 1 == testPlayer.getY());
}
*/


int main(int argc, char** argv) {

    doctest::Context context;

    int res = context.run();

    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;
    system("pause");
}

