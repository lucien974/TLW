#ifndef BLOON_H_INCLUDED
#define BLOON_H_INCLUDED

#include <string>

#include <SFML/System.hpp>

#include "Entity.h"
#include "Textureloader.h"
#include "Include.h"

class Bloon : public Entity
{
    public:
        Bloon(int type, Textureloader* textload, sf::Vector2f start_pos);
        virtual ~Bloon();
        void initialize(Textureloader* textload); // Initialization of all variables of bloon
        void update(Textureloader* textload); // move the bloon
        void update();
        void findWay(int x, int y, Textureloader* textload); // Research of the next position of the bloon
        bool isWentOut(); // If the bloon pass through th map
        int getSpeed(); // Get bloon speed
        int getAdvance(); // Return the number pixels crossed
        bool isTouch(sf::Vector2f pos_ball, int damages, Textureloader* textload, int effect, int ice_limit); // Manage the collision between bullets and bloon
        int getMoney(); // Return money when hit
        void setSpeed(int speed);
        int getDamages(); // Return Damages when pass through the map
        int getHealth(); // Return health of bloon
        void setMap(std::string bloon_map); // Change the map name

    private:
        int m_speed, m_health, m_earn, m_way, m_effect_status, m_effect_limit, m_status, m_life_lost;
        sf::Color m_color;
        bool m_exit, m_find, m_touch, m_earn_money;
        unsigned char m_direction;
        std::string m_carte;
        sf::Clock m_clock, m_time_update;

        enum m_shield{none = 0, ice = 0, burn = 1, glue = 2, reverse = 3};
};

#endif // BLOON_H_INCLUDED
