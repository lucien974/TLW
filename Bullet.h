#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "bloon.h"

class Bullet
{
    public:
        Bullet(float angle , int posx , int posy);
        void Move(sf::RenderWindow* ecran);
    private:
        sf::RectangleShape m_bullet;
        float m_angle;
};

#endif // BULLET_H_INCLUDED