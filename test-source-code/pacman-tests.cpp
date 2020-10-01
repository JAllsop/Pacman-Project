#include "../game-source-code/game.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define l 40.0f

TEST_CASE("Player Basic Movement")
{
    auto testPlayer = Player(l, l, sf::Color::Blue);
    testPlayer.setPosition(500, 500);

    auto y = testPlayer.getY();
    testPlayer.moveDown();
    CHECK(y + l == testPlayer.getY());

    y = testPlayer.getY();
    testPlayer.moveUp();
    CHECK(y - l == testPlayer.getY());

    auto x = testPlayer.getX();
    testPlayer.moveRight();
    CHECK(x + l == testPlayer.getX());

    x = testPlayer.getX();
    testPlayer.moveLeft();
    CHECK(x - l == testPlayer.getX());
}
//inheritance structure needs to be implemented correctly
TEST_CASE("Enemy Basic Movement")
{
    auto testEnemy = Enemy(l, l, sf::Color::Blue);
    testPlayer.setPosition(500, 500);

    auto y = testEnemy.getY();
    testPlayer.moveDown();
    CHECK(y + l == testPlayer.getY());

    y = testEnemy.getY();
    testPlayer.moveUp();
    CHECK(y - l == testPlayer.getY());

    auto x = testEnemy.getX();
    testPlayer.moveRight();
    CHECK(x + l == testPlayer.getX());

    x = testEnemy.getX();
    testPlayer.moveLeft();
    CHECK(x - l == testPlayer.getX());
}

TEST_CASE("maze test")
{
    std::shared_ptr<sf::RenderWindow> window;
    window = make_shared<sf::RenderWindow>(sf::VideoMode(1600, 900), "test");
    auto testInstance = MazeHandler(window);
    testInstance->get
}

int main(int argc, char** argv) {

    doctest::Context context;

    int res = context.run();

    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;
    system("pause");
}

