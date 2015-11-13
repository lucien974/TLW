#include "Game.h"

// Fait : Animation
// à Faire : ???

int main (int argc, char** argv)
{
    XInitThreads(); // Initialization of multi-threading client

    Game *game;
    game = new Game();

    game->update();

    delete game;

    return 0;
}
