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
        bool touch(sf::Vector2f pos_ball, int damages, Textureloader* textload, int effect, int ice_limit);
        bool isWentOut() const;
        int getSpeed() const;
        void setSpeed(int speed);
        int getIncrementation() const;
        int getMoney();
        int getDamages() const;
        int getHealth() const;

    private:
        int m_speed, m_life, m_life_lost, m_earn, m_way, m_ice, m_ice_limit, m_status;
        sf::Color m_color;
        bool m_went_out, m_direction[8], m_find, m_first, m_touch, m_earn_money;
        std::string m_carte;
        sf::Clock m_clock;
};

#endif // BLOON_H_INCLUDED
