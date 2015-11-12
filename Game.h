#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Level.h"
#include "Particle.h"

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
        Particle *m_mouse;
        bool m_menu;
        char m_clic;
};

#endif // GAME_INCLUDED
