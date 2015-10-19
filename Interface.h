#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Vague.h"
#include "Tower.h"
#include "Bouton.h"

class Interface
{
public:
    Interface(Textureloader* textload);
    ~Interface();
    void Update(sf::RenderWindow* screen , Textureloader* textload);
    bool Boucle(sf::RenderWindow* screen , Textureloader* textload);

private:
    sf::Texture m_texture , m_fond_texture;
    Bouton *m_bouton_play , *m_bouton_exit , *m_name;
    sf::Sprite m_fusion , m_fond;
    int tpspred , tpssuiv , m_explo , m_alea;
    int m_pos_x , m_posplayx , m_posexitx , m_posnamex , m_pos_left_x , m_pos_right_x;
    int m_pos_y , m_posplayy , m_posexity , m_posnamey , m_pos_left_y , m_pos_right_y;
    sf::Event m_event;
    bool m_anim_1 , m_anim_2 , m_anim_3 , m_anim_4 , m_exit;
    Vague *m_black , *m_white;
    bool m_anim_5 , m_pass , m_end , m_click;
    sf::RectangleShape m_left , m_right;
    sf::CircleShape m_explosion;
    sf::Font m_police;
    sf::View m_view;
    sf::Sound m_sound_xplo;
    Tower *m_tower , *m_inter , *m_tower_2;
};

#endif // MENU_H_INCLUDED
