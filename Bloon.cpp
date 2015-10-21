#include "Bloon.h"

Bloon::Bloon(int type, Textureloader* textload, std::string carte) :
Entity(),
m_speed(0),
m_life(type),
m_life_lost(0),
m_earn(0),
m_way(0),
m_ice(0),
m_ice_limit(0),
m_status(Effect::None),
m_went_out(false),
m_find(false),
m_touch(false),
m_earn_money(false),
m_carte(carte)
{
    for (int m(0); m < 8; ++m)
    {
        m_direction[m] = true;
    }
    initialize(textload);
    setPosition(textload->getRedPxl(carte));
}



Bloon::~Bloon()
{
}



// Initialization of the Bloon instance
void Bloon::initialize(Textureloader* textload)
{
    std::string ndefich = "";
    int bloonType = m_life;

    if (m_life > 9 && m_life < 100)
    {
        bloonType /= 10;
    }
    else if (m_life > 100 && m_life < 200)
    {
        bloonType -= 90;
        bloonType /= 10;
        if (bloonType > 9)
        {
            bloonType = 9;
        }
    }

    switch (bloonType)
    {
        case 1 :
            ndefich = "bloon_1.png";
            m_speed = 2;
            m_earn = 1;
            break;
        case 2 :
            ndefich = "bloon_2.png";
            m_speed = 2;
            m_earn = 2;
            break;
        case 3 :
            ndefich = "bloon_3.png";
            m_speed = 2;
            m_earn = 3;
            break;
        case 4 :
            ndefich = "bloon_4.png";
            m_speed = 2;
            m_earn = 4;
            break;
        case 5 :
            ndefich = "bloon_5.png";
            m_speed = 7;
            m_earn = 5;
            break;
        case 6 :
            ndefich = "bloon_6.png";
            m_speed = 7;
            m_earn = 6;
            break;
        case 7 :
            ndefich = "bloon_7.png";
            m_speed = 2;
            m_earn = 7;
            break;
        case 8 :
            ndefich = "bloon_8.png";
            m_speed = 2;
            m_earn = 8;
            break;
        case 9 :
            ndefich = "bloon_9.png";
            m_speed = 1;
            m_earn = 9;
            break;
        case 100 :
            ndefich = "bloon_10.png";
            m_speed = 21;
            m_earn = 100;
            break;
        case 200 :
            ndefich = "bloon_11.png";
            m_speed = 21;
            m_earn = 100;
            break;
        default :
            break;
    }

    if (m_life > 9 && m_life < 100)
    {
        m_earn = 15;
        setTexture(textload->getTexture("bloon_shield.png"), SHIELD);
        spriteStatus(true, SHIELD);
    }
    else if (m_life > 100 && m_life < 200)
    {
        m_earn = 15;
        setTexture(textload->getTexture("bloon_shield_1.png"), SHIELD);
        spriteStatus(true, SHIELD);
    }
    else
    {
        spriteStatus(false, SHIELD);
    }

    if (m_life < 10 || m_life == 100 || m_life == 200)
    {
        setTexture(textload->getTexture(ndefich), BLOON);
    }
}



// Recherche du chemin que doit suivre le ballon
void Bloon::update(Textureloader* textload)
{
    if (m_clock.getElapsedTime().asMilliseconds() >= 1000 && m_ice > m_ice_limit && m_life > 0)
    {
        m_ice = 0;
        spriteStatus(false, ICE);
    }
    if ((m_ice < m_ice_limit || m_status == Effect::None) && m_life > 0)
    {
        for (int n(0); n < m_speed; ++n)
        {
            m_way++;
            if (m_find == false)
            {
                if (m_direction[0] == true)
                    findway(getPosition().x + 1, getPosition().y, 1, textload);

                if (m_direction[2] == true)
                    findway(getPosition().x, getPosition().y + 1, 3, textload);

                if (m_direction[1] == true)
                    findway(getPosition().x - 1, getPosition().y, 0, textload);

                if (m_direction[3] == true)
                    findway(getPosition().x, getPosition().y - 1, 2, textload);

                if (m_direction[4] == true && m_find == false)
                    findway(getPosition().x + 1, getPosition().y - 1, 6, textload);

                if (m_direction[5] == true && m_find == false)
                    findway(getPosition().x + 1, getPosition().y + 1, 7, textload);

                if (m_direction[6] == true && m_find == false)
                    findway(getPosition().x - 1, getPosition().y + 1, 4, textload);

                if (m_direction[7] == true && m_find == false)
                    findway(getPosition().x - 1, getPosition().y - 1, 5, textload);
            }
            m_find = false;
        }
    }
}



void Bloon::update()
{
}



void Bloon::findway(unsigned int x, unsigned int y, int postab, Textureloader* textload)
{
    sf::Vector2u mapSize = textload->getMap(m_carte).getSize();
    if (x < mapSize.x && y < mapSize.y)
    {
        m_color = textload->getMap(m_carte).getPixel(x, y);
        if (m_color == sf::Color::White)
        {
            setPosition(sf::Vector2f(x, y));
            for (int v(0); v < 8; ++v)
            {
                if (v == postab)
                {
                    m_direction[postab] = false;
                }
                else
                {
                    m_direction[v] = true;
                }
            }
            m_find = true;
        }
        else if (m_color == sf::Color::Blue)
        {
            setPosition(sf::Vector2f(x, y));
            m_went_out = true;
        }
    }
}



bool Bloon::touch(sf::Vector2f pos_ball, int damages, Textureloader* textload, int effect, int ice_limit)
{
    if (damages >= 0)
    {
        if ((pos_ball.x >= getPosition().x - 22 && pos_ball.x <= getPosition().x + 23) &&
            (pos_ball.y >= getPosition().y - 22 && pos_ball.y <= getPosition().y + 23))
        {
            if (m_life > 0)
            {
                switch (effect)
                {
                    case -1 :
                        m_life -= damages;
                        m_touch = true;
                        initialize(textload);
                        spriteStatus(false, ALL);
                        m_life_lost = damages;
                        break;
                    case 0 :
                        m_ice++;
                        m_ice_limit = ice_limit;
                        if (m_ice == m_ice_limit)
                        {
                            m_life_lost = damages;
                            m_life -= damages;
                            m_touch = true;
                            initialize(textload);
                            m_clock.restart();
                            m_ice++;
                            m_status = Effect::Ice;
                            setTexture(textload->getTexture("ice_bloon.png"), ICE);
                            spriteStatus(true, ICE);
                            m_earn_money = true;
                        }
                        break;
                    default :
                        break;
                }

                if (m_touch)
                {
                    return true;
                }
            }
            else
            {
                m_went_out = true;
            }
        }
    }
    return false;
}



// Ordonne la destruction du ballon
bool Bloon::isWentOut() const
{
    return m_went_out;
}



int Bloon::getSpeed() const
{
    return m_speed;
}



void Bloon::setSpeed(int speed)
{
    m_speed = speed;
}



int Bloon::getIncrementation() const
{
    return m_way;
}



int Bloon::getMoney()
{
    if (m_touch)
    {
        m_touch = false;
        if (m_status == Effect::None && m_life_lost > 0)
            return m_earn;
        if (m_status == Effect::Ice && m_life_lost > 0 && m_earn_money == true)
        {
            m_earn_money = false;
            return m_earn;
        }
    }
    return 0;
}



int Bloon::getDamages() const
{
    if (isWentOut() && m_touch == false && m_life > 0)
    {
        return m_life;
    }
    return 0;
}



int Bloon::getHealth() const
{
    return m_life;
}
