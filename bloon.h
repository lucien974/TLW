#ifndef BLOON_H_INCLUDED
#define BLOON_H_INCLUDED

#include <deque>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include "entity.h"
#include "Textureloader.h"

class Bloon : public Entity
{
public:
    Bloon(sf::Image carte_v , int type , Textureloader* textload);
    virtual ~Bloon();
    void Init(int type , Textureloader* textload);
    void update();
    void Findway(int x, int y , int postab);
    bool Exit();
    int Getspeed();
    int Getincrementation();
    int Touch(int ball_pos_x , int ball_pos_y , int damages , Textureloader* textload);
    int Getmoney();
    void Setspeed(int speed);
    int Getdamages();

private:
    int m_speed , m_vie , m_earn , m_position_x , m_position_y , m_way;
    sf::Image m_carte_v;
    sf::Color m_color;
    bool m_enter , m_exit , m_hunt , m_boucle , m_direction[8] , m_find , m_first , m_touch , m_kill;
    sf::Sound m_sound;
};

#endif // BLOON_H_INCLUDED
