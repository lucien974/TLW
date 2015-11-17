#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include <string>
#include <deque>

#include "Entity.h"
#include "Textureloader.h"
#include "Include.h"

class Tower : public Entity
{
    public:
        Tower(int type, Textureloader* textload);
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
        void upgradeLeft(Textureloader* textload);
        void upgradeRight(Textureloader* textload);
        void init(Textureloader* textload);
        int getEffect();
        int getNbBall();
        void iceMove(int r);
        std::string getPrice();
        std::string getLeftUpgrade();
        std::string getRightUpgrade();
        int getUpPrice(Textureloader* textload);

    private:
        sf::Sprite m_tower;
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
        enum m_effect{none = -1, ice = 0, burn = 1, glue = 2, reverse = 3};
};

#endif // TOWER_H_INCLUDED
