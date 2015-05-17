#ifndef MULTITOUR_H_INCLUDED
#define MULTITOUR_H_INCLUDED

#include "Tower.h"
#include <sstream>

class Multitower
{
    public:
        Multitower(sf::Image carte_v , Textureloader* textload);
        ~Multitower();
        int Panel(bool sup , sf::RenderWindow* screen , int money , int lives , Textureloader* textload);
        bool Settower(sf::RenderWindow* screen , Textureloader* textload);
        int Getsize();
        bool Getstatus();
        Tower* Gettower(int b);
        int Getrange(int n);
    private:
        sf::Image m_carte;
        sf::Sprite m_panel;
        int m_type , m_select , m_sel;
        std::deque<sf::Sprite*> m_choice;
        std::deque<int> m_cost;
        sf::Font m_police;
        sf::Text m_sprite_money , m_lives;
        std::deque<sf::Text*> m_sprite_cost;
        sf::Event m_event;
        sf::Texture m_texture;
        sf::Color m_color;
        sf::CircleShape m_rayon;
        std::deque<Tower*> m_tower;
        bool m_set , m_button_pressed , m_suppression;
};


#endif // MULTITOUR_H_INCLUDED
