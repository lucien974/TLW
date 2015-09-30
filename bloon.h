#ifndef BLOON_H_INCLUDED
#define BLOON_H_INCLUDED

#include "entity.h"
#include "Textureloader.h"

class Bloon : public Entity
{
public:
    Bloon(int type , Textureloader* textload , std::string carte);
    virtual ~Bloon();
    void Init(Textureloader* textload);
    void Update(Textureloader* textload);
    void update();
    void Findway(int x, int y , int postab , Textureloader* textload);
    bool Exit();
    int Getspeed();
    int Getincrementation();
    int Touch(sf::Vector2f pos_ball , int damages , Textureloader* textload , int effect , int ice_limit);
    int Getmoney();
    void Setspeed(int speed);
    int Getdamages();
    int getHealth();

private:
    int m_speed , m_vie , m_earn , m_way , m_ice , m_ice_limit , m_status , m_life_lost;
    sf::Color m_color;
    bool m_exit , m_direction[8] , m_find , m_first , m_touch , m_earn_money;
    std::string m_carte;
    sf::Clock m_clock;
    enum m_effect{none = -1 , ice = 0 , burn = 1 , glue = 2 , reverse = 3};
};

#endif // BLOON_H_INCLUDED
