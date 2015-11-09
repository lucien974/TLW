#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Level.h"

class Game
{
    public:
        Game();
        void update();
    private:
        Level *m_level;
        Menu *m_start;
        Textureloader *m_textload;
        RenderWindow m_screen;
        Sprite m_background;
};

#endif // GAME_INCLUDED
