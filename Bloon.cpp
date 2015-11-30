#include "Bloon.h"

Bloon::Bloon(int type, Textureloader* textload, sf::Vector2f start_pos) :
Entity(),
m_speed(0),
m_health(type),
m_earn(0),
m_way(0),
m_effect_status(0),
m_effect_limit(0),
m_status(m_effect::none),
m_life_lost(0),
m_color(0, 0, 0),
m_exit(false),
m_find(false),
m_touch(false),
m_earn_money(false),
m_carte("")
{
    for (int m(0); m < 8; m++)
    {
        m_direction[m] = true;
    }
    initialize(textload);
    setPosition(start_pos);
    m_time_update.restart();
}

Bloon::~Bloon()
{
}

void Bloon::initialize(Textureloader* textload)
{
    std::string ndefich = "";
    int bloon_type = m_health;
    spriteStatus(false, SHIELD);

    if (m_health > 9 && m_health < 100)
    {
        bloon_type /= 10;
    }
    else if (m_health > 100 && m_health < 200)
    {
        bloon_type -= 90;
        bloon_type /= 10;
        if (bloon_type > 9)
        {
            bloon_type = 9;
        }
    }
    switch (bloon_type)
    {
        case 1:
            ndefich = "bloon_1.png";
            m_speed = 5;
            m_earn = 1;
            break;
        case 2:
            ndefich = "bloon_2.png";
            m_speed = 6;
            m_earn = 2;
            break;
        case 3:
            ndefich = "bloon_3.png";
            m_speed = 7;
            m_earn = 3;
            break;
        case 4:
            ndefich = "bloon_4.png";
            m_speed = 8;
            m_earn = 4;
            break;
        case 5:
            ndefich = "bloon_5.png";
            m_speed = 15;
            m_earn = 5;
            break;
        case 6:
            ndefich = "bloon_6.png";
            m_speed = 15;
            m_earn = 6;
            break;
        case 7:
            ndefich = "bloon_7.png";
            m_speed = 8;
            m_earn = 7;
            break;
        case 8:
            ndefich = "bloon_8.png";
            m_speed = 8;
            m_earn = 8;
            break;
        case 9:
            ndefich = "bloon_9.png";
            m_speed = 5;
            m_earn = 9;
            break;
        case 100:
            ndefich = "bloon_10.png";
            m_speed = 30;
            m_earn = 100;
            break;
        case 200:
            ndefich = "bloon_11.png";
            m_speed = 30;
            m_earn = 100;
            break;
        default:
            break;
    }

    if (bloon_type < 10 || bloon_type == 100 || bloon_type == 200)
    {
        setTexture(textload->getTexture(ndefich), BLOON);
    }

    if (m_health > 9 && m_health < 100)
    {
        m_earn = 15;
        setTexture(textload->getTexture("bloon_shield_1.png"), SHIELD);
        spriteStatus(true, SHIELD);
    }
    else if (m_health > 100 && m_health < 200)
    {
        m_earn = 15;
        setTexture(textload->getTexture("bloon_shield_2.png"), SHIELD);
        spriteStatus(true, SHIELD);
    }
}

void Bloon::findWay(unsigned int x, unsigned int y, int postab, Textureloader* textload)
{
    // If the mao exist
    if (m_carte != "")
    {
        // If the coord exist
        if (x < textload->getMap(m_carte).getSize().x && y < textload->getMap(m_carte).getSize().y)
        {
            m_color = textload->getMap(m_carte).getPixel(x, y);
            // If the color isn't green
            if (m_color != sf::Color(0, 153, 0))
            {
                setPosition(sf::Vector2f(x, y));
                // All except the current boolean is set as false because the next position is found
                for (int v(0); v < 8; v++)
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
            // If the color is blue the bloon passed through the map so we can destroy the bloon
            if (m_color == sf::Color::Blue)
            {
                setPosition(sf::Vector2f(x, y));
                m_exit = true;
            }
        }
    }
}

int Bloon::getDamages()
{
    // If the bloon passed through the map and don't been hit : return the health
    if (m_exit == true && m_touch == false)
    {
        return m_health;
    }
    return 0;
}

bool Bloon::isTouch(sf::Vector2f pos_ball, int damages, Textureloader* textload, int effect, int ice_limit)
{
    if (damages >= 0)
    {
        // If the ball is in the bloon
        if ((pos_ball.x >= getPosition().x - 22 && pos_ball.x <= getPosition().x + 23) &&
            (pos_ball.y >= getPosition().y - 22 && pos_ball.y <= getPosition().y + 23))
        {
            if (m_health > 0)
            {
                switch (effect)
                {
                    case -1:
                        m_health -= damages;
                        m_touch = true;
                        initialize(textload);
                        spriteStatus(false, ALL);
                        m_life_lost = damages;
                        break;
                    case 0:
                        m_effect_status++;
                        if (m_effect_limit != ice_limit)
                            m_effect_limit = ice_limit;
                        if (m_effect_status == m_effect_limit)
                        {
                            m_life_lost = damages;
                            m_health -= damages;
                            m_touch = true;
                            initialize(textload);
                            m_clock.restart();
                            m_effect_status++;
                            m_status = m_effect::ice;
                            setTexture(textload->getTexture("ice_bloon.png"), ICE);
                            spriteStatus(true, ICE);
                            m_earn_money = true;
                        }
                        break;
                    default:
                        m_touch = false;
                        break;
                }
                if (m_touch && damages > 0)
                    return 1;
            }
            else
                m_exit = true;
        }
    }
    return 0;
}

int Bloon::getHealth()
{
    return m_health;
}

void Bloon::update(Textureloader* textload)
{
    if (m_clock.getElapsedTime().asMilliseconds() >= 1000 && m_effect_status > m_effect_limit && m_health > 0)
    {
        m_effect_status = 0;
        spriteStatus(false, ICE);
    }
    if ((m_effect_status < m_effect_limit || m_status == m_effect::none) && m_health > 0)
    {
        for (int n(0); n < m_speed; ++n)
        {
            m_way++;
            if (m_direction[0] == true && m_find == false)
                findWay(getPosition().x + 1, getPosition().y, 1, textload);

            if (m_direction[2] == true && m_find == false)
                findWay(getPosition().x, getPosition().y + 1, 3, textload);

            if (m_direction[1] == true && m_find == false)
                findWay(getPosition().x - 1, getPosition().y, 0, textload);

            if (m_direction[3] == true && m_find == false)
                findWay(getPosition().x, getPosition().y - 1, 2, textload);

            if (m_find == false)
            {
                if (m_direction[4] == true && m_find == false)
                    findWay(getPosition().x + 1, getPosition().y - 1, 6, textload);

                if (m_direction[5] == true && m_find == false)
                    findWay(getPosition().x + 1, getPosition().y + 1, 7, textload);

                if (m_direction[6] == true && m_find == false)
                    findWay(getPosition().x - 1, getPosition().y + 1, 4, textload);

                if (m_direction[7] == true && m_find == false)
                    findWay(getPosition().x - 1, getPosition().y - 1, 5, textload);
            }
            m_find = false;
        }
    }
    m_time_update.restart();
}

void Bloon::update()
{
}

bool Bloon::isWentOut()
{
    return m_exit;
}

int Bloon::getSpeed()
{
    return m_speed;
}

int Bloon::getMoney()
{
    if (m_touch)
    {
        m_touch = false;
        if (m_status == m_effect::none && m_life_lost > 0)
            return m_earn;
        if (m_status == m_effect::ice && m_life_lost > 0 && m_earn_money == true)
        {
            m_earn_money = false;
            return m_earn;
        }
    }
    return 0;
}

int Bloon::getAdvance()
{
    return m_way;
}

void Bloon::setSpeed(int speed)
{
    m_speed = speed;
}

void Bloon::setMap(std::string bloon_map)
{
    m_carte = bloon_map;
}
