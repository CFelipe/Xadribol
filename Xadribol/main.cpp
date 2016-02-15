#include "ResourcePath.hpp"
#include "PlayingState.h"

int main(int, char const**)
{
    Game game;
    game.pushState(new PlayingState(&game));
    game.gameLoop();
    return EXIT_SUCCESS;
}