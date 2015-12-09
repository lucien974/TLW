#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <string>

#include "Level.h"
#include "Particle.h"

//Number levels limit
#define NB_LEVELS 2

class Game
{
    public:
        Game();
        ~Game();
        void update();

    private:
        void animation();
        void run();
        void menu();
        void event();

        Level *m_level;
        Menu *m_start;
        Textureloader *m_textload;
        sf::RenderWindow *m_screen;
        sf::Sprite m_background;
        Particle *m_mouse;
        Wave *m_animation;
        std::fstream m_file;
        std::string m_level_name;
        unsigned int m_level_num, m_number_levels;
        bool m_menu, m_enable_animation;
        char m_clic;
};

#endif // GAME_INCLUDED
