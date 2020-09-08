#include "game.h"

int main()
{
    auto game = make_unique<Game>();
    game->run();
    return 0;
}
