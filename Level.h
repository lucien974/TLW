#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "Vague.h"
#include "Multitour.h"
#include "Bouton.h"

class Level
{
public:
    Level(sf::Image carte_v , Textureloader* textload);
    ~Level();
    void Launch(sf::RenderWindow *ecran , Textureloader* textload);
    void Event(sf::RenderWindow *ecran , Textureloader* textload);

private:
    std::deque<Vague*> m_level;
    std::deque<int> m_interlevel;
    FILE* m_fichier;
    int m_nbbloon , m_inter , m_type , m_play , m_pause , m_damages , m_money , m_play_save , m_inter_vague , m_tri , m_lives;
    long m_frontinter , m_seek , m_size;
    sf::Image m_carte_v;
    bool m_pass , m_passinter , m_end , m_done , m_one_time , m_bp , m_bool_pause , m_first_pass , m_win , m_sup , m_delete;
    sf::Event m_event;
    sf::Sprite m_sprite , m_tower_bar , m_bouton , m_loose;
    sf::Text m_sprite_money;
    Bouton *m_text_pause , *m_text_loose , *m_restart , *m_text_win , *m_text_exit , *m_resume;
    Multitower* m_tower;
    sf::RectangleShape m_shape_pause;
    sf::Font m_police;
};

#endif // LEVEL_H_INCLUDED
