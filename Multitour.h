#ifndef MULTITOUR_H_INCLUDED
#define MULTITOUR_H_INCLUDED

#include "Tower.h"
#include "Bouton.h"

class Multitower
{
    public:
        Multitower(Textureloader* textload);
        ~Multitower();
        int update(sf::Image carte , sf::RenderWindow* screen , Textureloader* textload , int money , bool sup , bool click , bool clic_up);
        int getSize();
        Tower* getTower(int b);
        sf::CircleShape getRange(int n);
        bool getStatus();
    private:
        std::deque<Tower*> m_tower , m_selection;
        std::deque<Bouton> m_cost_sprite;
        int m_select , m_tower_selected;
        sf::Sprite m_up[2];
        Bouton m_up_price[2] , m_money;
};


#endif // MULTITOUR_H_INCLUDED
