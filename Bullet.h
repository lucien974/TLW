#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Bloon.h"

class Bullet
{
    public:
        Bullet(float angle, int posx, int posy);
        void move(sf::RenderWindow* ecran);

    private:
        sf::RectangleShape m_bullet;
        float m_angle;
};

#endif // BULLET_H_INCLUDED
