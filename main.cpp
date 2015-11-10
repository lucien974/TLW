#include "Game.h"

/// Fait : class Game
/// à Faire : Animation du main_menu

int main ( int argc, char** argv )
{
    XInitThreads(); /// Initialization of multi-threading client

    Game *game;
    game = new Game();

    game->update();

    delete game;

    return 0;
}
