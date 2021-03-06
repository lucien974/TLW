#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include <string>
#include <deque>
#include <sstream>
#include <stdexcept>

#include "Entity.h"
#include "Textureloader.h"
#include "Include.h"
#include "TowerEffect.h"

class Tower : public Entity
{
    public:
        Tower(int type, Textureloader* textload, sf::Vector2f position);
        int shoot(sf::Vector2f bloon);
        virtual ~Tower();
        void update();
        void drawBullet(sf::RenderWindow* screen);
        void destroyBullet();
        sf::Vector2f getBullet(int a);
        int getNumberBullet();
        int sell();
        int getCost();
        void initialize(Textureloader* textload);
        int getEffect();
        int getNbBall();
        int getType();
        int getUpgrade();
        std::string getUpgrade(int num);
        int getUpgradePrice(Textureloader *textload, int num);
        void upgrade (Textureloader* textload, int num);
        void getTowerPrice();

    private:
        sf::Clock m_clock;
        sf::CircleShape m_range;
        std::deque<sf::Vector2f> m_forward;
        std::deque<sf::RectangleShape> m_bullet;
        bool m_shoot, m_up_price, m_pass_canon[3];
        float m_tir, m_firerate, m_radian;
        int m_portee, m_cost, m_type, m_damages, m_turrets, m_nb_ball, m_type_effect, m_upgrade, m_canon;
        std::deque<sf::Vector2f> m_last_pos;
        std::deque<int> m_incrementation;
        sf::Color m_color;
        TowerEffect *m_effect_move;
};

#endif // TOWER_H_INCLUDED
