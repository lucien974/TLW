#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "Wave.h"
#include "Multitour.h"
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
    void load();

private:

    deque<Wave*> m_bloons;
    Multitower *m_towers;
    int m_money , m_life , m_play_save;
    char m_clic;
    bool m_done , m_delete , m_pause_avaible;
    ifstream m_file;
    Event m_event;
    Sprite m_map , m_button_play , m_interface;
    Text m_sprite_money;
    Menu *m_pause , *m_win , *m_loose;
    Button *m_text_life;
    Music m_music;

    Thread *m_thread;
    RenderWindow *m_screen;
    Textureloader *m_textload;
    Mutex m_mutex;
};

#endif // LEVEL_H_INCLUDED
