#include "Game.h"
#include <X11/Xlib.h>

// Fait : Animation
// A Faire : Priorité des chemins de ballons

int main ()
{
    XInitThreads(); // Initialization of multi-threading client
    srand(time(nullptr));

    Game *game;
    game = new Game();

    game->update();

    delete game;

    return 0;
}
