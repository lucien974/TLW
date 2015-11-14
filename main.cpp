#include "Game.h"

// Fait : Animation
// � Faire : ???

int main ()
{
    XInitThreads(); // Initialization of multi-threading client

    Game *game;
    game = new Game();

    game->update();

    delete game;

    return 0;
}
