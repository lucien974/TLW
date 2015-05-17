#include "Tower.h"

Tower::Tower(int type , Textureloader* textload , int cost) : Entity()
{
    m_firerate = 0.0;
    switch(type)
    {
        case 1:
            setTexture(textload->Gettexture("tower_1.png"));
            m_firerate = 1000.0;
            m_portee = 100;
            break;
        case 2:
            setTexture(textload->Gettexture("tower_2.png"));
            m_firerate = 666.0;
            m_portee = 125;
        default:
            break;
    }
    m_clock.restart();
    m_shoot = true;
    setOrigin(40 , 60);
    m_range.setFillColor(sf::Color(0,0,255,128));
    m_range.setRadius(100.0);
    m_range.setOrigin(m_range.getGlobalBounds().width / 2 , m_range.getGlobalBounds().height / 2);
    m_range.setPosition(getPosition().x - 40 , getPosition().y - 60);
    m_cost = cost;
}

Tower::~Tower()
{
}

int Tower::Getrange()
{
    return m_portee;
}

void Tower::update()
{
}

void Tower::Range(sf::RenderWindow* screen)
{
    m_range.setPosition(getPosition().x , getPosition().y);
    screen->draw(m_range);
}

int Tower::Fire()
{
    m_time = m_clock.getElapsedTime();
    m_tir = m_time.asMilliseconds();
    if(m_tir >= m_firerate)
    {
        m_clock.restart();
        return 1;
    }
    return 0;
}

int Tower::Sell()
{
    m_cost *= 0.75;
    return m_cost;
}
