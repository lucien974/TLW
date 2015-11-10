#ifndef BLOON_H_INCLUDED
#define BLOON_H_INCLUDED

#include "Entity.h"
#include "Textureloader.h"

class Bloon : public Entity
{
public:
    Bloon(int type , Textureloader* textload , sf::Vector2f start_pos);
    virtual ~Bloon();
    void initialize(Textureloader* textload); /// Initialization of all variables of bloon
    void update(Textureloader* textload);
    void update();
    void findWay(int x, int y , int postab , Textureloader* textload); /// Research of the next position of the bloon
    bool isWentOut();
    int getSpeed();
    int getAdvance();
    int isTouch(sf::Vector2f pos_ball , int damages , Textureloader* textload , int effect , int ice_limit); /// Manage the collision between bullets and bloon
    int getMoney(); /// Return money when hit
    void setSpeed(int speed);
    int getDamages(); /// Return Damages when pass through the map
    int getHealth();
    void setMap(string bloon_map);

private:
    int m_speed , m_vie , m_earn , m_way , m_ice , m_ice_limit , m_status , m_life_lost;
    sf::Color m_color;
    bool m_exit , m_direction[8] , m_find , m_first , m_touch , m_earn_money;
    string m_carte;
    sf::Clock m_clock;
    enum m_shield{none = 0 , ice = 0 , burn = 1 , glue = 2 , reverse = 3};
};

#endif // BLOON_H_INCLUDED
