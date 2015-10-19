#ifndef BLOON_H_INCLUDED
#define BLOON_H_INCLUDED

#include "Entity.h"
#include "Textureloader.h"

class Bloon : public Entity
{
    public:
        Bloon(int type, Textureloader* textload, std::string carte);
        virtual ~Bloon();
        void initialize(Textureloader* textload);
        void update(Textureloader* textload);
        void update();
        void findway(unsigned int x, unsigned int y, int postab, Textureloader* textload);
        int touch(sf::Vector2f pos_ball, int damages, Textureloader* textload, int effect, int ice_limit);
        bool exit() const;
        int getSpeed() const;
        void setSpeed(int speed);
        int getIncrementation() const;
        int getMoney();
        int getDamages() const;
        int getHealth() const;

    private:
        int m_speed, m_vie, m_earn, m_way, m_ice, m_ice_limit, m_status, m_life_lost;
        sf::Color m_color;
        bool m_exit, m_direction[8], m_find, m_first, m_touch, m_earn_money;
        std::string m_carte;
        sf::Clock m_clock;
        enum m_shield {none = 0, ice = 0, burn = 1, glue = 2, reverse = 3};
};

#endif // BLOON_H_INCLUDED
