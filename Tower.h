#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include <deque>
#include <sstream>

#include "Entity.h"
#include "Textureloader.h"

class Tower : public Entity
{
      public:
            Tower(int type, Textureloader* textload);
            Tower(int type, Textureloader* textload, sf::Vector2f position);
            virtual ~Tower();
            void update();
            void iceMove(int r);
            void drawBullet(sf::RenderWindow* screen);
            int fire(sf::Vector2f bloon);
            void destroyBullet();
            sf::Vector2f getBullet(int a);
            int getNumberBullet();
            int sell();
            int getCost();
            void upgradeLeft(Textureloader* textload);
            void upgradeRight(Textureloader* textload);
            void initialize(Textureloader* textload);
            int getEffect() const;
            int getNbBall() const;
            std::string getPrice() const;
            std::string getLeftUpgrade() const;
            std::string getRightUpgrade() const;
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
};

#endif // TOWER_H_INCLUDED
