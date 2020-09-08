#include "game.h"

int main()
{
    auto game = make_unique<Game>(1600,900);
    game->run();
    return 0;
}
