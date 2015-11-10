#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "Wave.h"
#include "TowerManager.h"
#include "Button.h"
#include "Menu.h"

class Level
{
public:
    Level(Textureloader* textload , sf::RenderWindow *screen);
    ~Level();
    void update(sf::RenderWindow *ecran , Textureloader* textload);
    void event(sf::RenderWindow *ecran , Textureloader* textload);
    void physicsMotor();
    void buttonAnimation();
    void load();
    void initialize();

private:

    deque<Wave*> m_bloons;
    TowerManager *m_towers;
    int m_money , m_lives , m_play_save , m_status;
    char m_clic , m_animation;
    bool m_done , m_delete;
    ifstream m_file;
    sf::Event m_event;
    sf::Sprite m_map , m_button_play , m_interface;
    Menu *m_pause , *m_win , *m_loose;
    Button *m_text_life;
    sf::Music m_music;

    thread *m_thread;
    sf::RenderWindow *m_screen;
    Textureloader *m_textload;
    mutex m_mutex;

    enum game_status{normal = 0 , paused = 1 , win = 2 , loose = 3 , wait = 4 , play_animation = 5};
};

#endif // LEVEL_H_INCLUDED
