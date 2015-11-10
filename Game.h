#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Level.h"

class Game
{
    public:
        Game();
        ~Game();
        void update();
    private:
        Level *m_level;
        Menu *m_start;
        Textureloader *m_textload;
        sf::RenderWindow *m_screen;
        sf::Sprite m_background;
        bool m_menu;
        //Thread *m_thread;
};

#endif // GAME_INCLUDED
