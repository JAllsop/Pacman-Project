#include "../game-source-code/game.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define l 40.0f

TEST_CASE("Player Basic Movement")
{
    auto testPlayer = Player(blockSize, blockSize, sf::Color::Blue);
    testPlayer.setPosition(500, 500);

    auto y = testPlayer.getY();
    testPlayer.moveDown();
    CHECK(y + blockSize == testPlayer.getY());

    y = testPlayer.getY();
    testPlayer.moveUp();
    CHECK(y - blockSize == testPlayer.getY());

    auto x = testPlayer.getX();
    testPlayer.moveRight();
    CHECK(x + blockSize == testPlayer.getX());

    x = testPlayer.getX();
    testPlayer.moveLeft();
    CHECK(x - blockSize == testPlayer.getX());
}

TEST_CASE("Enemy Basic Movement")
{
    auto testEnemy = Enemy(blockSize, blockSize, sf::Color::Blue);
    testEnemy.setPosition(500, 500);

    auto y = testEnemy.getY();
    testEnemy.moveDown();
    CHECK(y + blockSize == testEnemy.getY());

    y = testEnemy.getY();
    testEnemy.moveUp();
    CHECK(y - blockSize == testEnemy.getY());

    auto x = testEnemy.getX();
    testEnemy.moveRight();
    CHECK(x + blockSize == testEnemy.getX());

    x = testEnemy.getX();
    testEnemy.moveLeft();
    CHECK(x - blockSize == testEnemy.getX());
}

/*requires more seperation of logic in order to simulate collision testing correctly
TEST_CASE("Maze Test")
{
    std::shared_ptr<sf::RenderWindow> window;
    window = make_shared<sf::RenderWindow>(sf::VideoMode(1600, 900), "test");
    auto testInstance = MazeHandler(window);
    testInstance->getMaze();
}
*/

//ensures console doesn't close upon test completion when running .exe
int main(int argc, char** argv) {
    doctest::Context context;
    int res = context.run();
    if(context.shouldExit())
        return res;

    system("pause");
}

