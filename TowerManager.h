#ifndef TOWER_MANAGER_H_INCLUDED
#define TOWER_MANAGER_H_INCLUDED

#include <deque>

#include "Tower.h"
#include "Button.h"

class TowerManager
{
    public:
        TowerManager(Textureloader* textload);
        ~TowerManager();
        int update(sf::Image carte, sf::RenderWindow* screen, Textureloader* textload, int money, bool sup, bool clic_up);
        int getSize();
        bool getStatus();
        sf::Vector2f getPosition(int num);
        float getRange(int n);
        void rotateTowards(int n, sf::Vector2f bloon);
        int shoot(int n, sf::Vector2f bloon);
        int getEffect(int n);
        int getNbBall(int n);

    private:
        std::deque<Tower*> m_tower, m_selection;
        std::deque<Button> m_cost_sprite;
        int m_select, m_tower_selected;
        sf::Sprite m_up[2];
        Button *m_up_price[2], *m_money;
};

#endif // TOWER_MANAGER_H_INCLUDED
