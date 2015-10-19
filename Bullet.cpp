#include "Bullet.h"

Bullet::Bullet(float angle, int posx, int posy)
{
    m_bullet.setRotation(angle);
    m_bullet.setSize(sf::Vector2f(5, 2));
    m_bullet.setFillColor(sf::Color::Black);
    m_bullet.setPosition(posx, posy);
    m_angle = angle;
}



void Bullet::move(sf::RenderWindow* ecran)
{
    ecran->draw(m_bullet);
    m_bullet.move(sin(m_angle), cos(m_angle));
}

