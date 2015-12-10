#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <string>
#include <cctype>
#include <fstream>
#include <thread>
#include <mutex>
#include <sstream>
#include <stdexcept>

#include "Wave.h"
#include "TowerManager.h"
#include "Button.h"
#include "Menu.h"

#define MONEY_UP 5000
#define LIFE_UP 5000

class Level
{
    public:
        Level(Textureloader* textload, sf::RenderWindow *screen, std::string file);
        ~Level();
        void update(sf::RenderWindow *ecran, Textureloader* textload);
        bool run(sf::RenderWindow *ecran, Textureloader* textload);
        bool isDone();
        void close();
        void physicsMotor();
        void buttonAnimation();
        void changeLevel(std::string file);
        void forceRunning(sf::RenderWindow *screen, Textureloader* textload);
        void load();
        void initialize();
        void destroy();
        void save();

    private:
        std::deque<Wave*> m_waves;
        TowerManager *m_towers;
        int m_money, m_status, m_last_status;
        unsigned int m_lives, m_play_save;
        char m_clic, m_animation;
        unsigned char m_shortcuts;
        bool m_done, m_delete, m_end;
        std::ifstream m_file;
        std::string m_file_name, m_cheat_code;
        sf::Event m_event;
        sf::Sprite m_map, m_button_play, m_interface, m_sprite_life;
        Menu *m_pause, *m_win, *m_loose;
        Button *m_text_life;
        sf::Music m_music;
        std::deque<sf::Sound> m_sound;
        std::thread *m_thread;
        sf::RenderWindow *m_screen;
        Textureloader *m_textload;
        std::mutex m_mutex;
        enum game_status{normal = 0, paused = 1, win = 2, loose = 3, wait = 4, play_animation = 5, end = 6};
};

#endif // LEVEL_H_INCLUDED
