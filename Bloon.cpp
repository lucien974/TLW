#include "Bloon.h"

Bloon::Bloon(int type , Textureloader* textload , sf::Vector2f start_pos) : Entity()
{
    m_earn_money = false;
    m_vie = type;
    m_speed = 0;
    m_find = false;
    m_touch = false;
    m_ice = 0;
    for( int m(0) ; m < 8 ; m++ )
    {
        m_direction[m] = true;
    }
    m_earn = 0;
    m_way = 0;
    initialize(textload);
    m_exit = false;
    setPosition(start_pos);
    m_status = m_effect::none;
}

Bloon::~Bloon()
{
}

////////////////////////////////////////
// INITIALISATION
////////////////////////////////////////

void Bloon::initialize(Textureloader* textload)
{
    std::string ndefich = "";
    int inter = m_vie;
    spriteStatus(false , SHIELD);

    if(inter > 9 && inter < 100)
        m_vie /= 10;
    if(inter > 100 && inter < 200)
    {
        m_vie -= 90;
        m_vie /= 10;
        if(m_vie > 9)
            m_vie = 9;
    }
    switch(m_vie)
    {
        case 1:
            ndefich = "bloon_1.png";
            m_speed = 2;
            m_earn = 1;
            break;
        case 2:
            ndefich = "bloon_2.png";
            m_speed = 2;
            m_earn = 2;
            break;
        case 3:
            ndefich = "bloon_3.png";
            m_speed = 2;
            m_earn = 3;
            break;
        case 4:
            ndefich = "bloon_4.png";
            m_speed = 2;
            m_earn = 4;
            break;
        case 5:
            ndefich = "bloon_5.png";
            m_speed = 7;
            m_earn = 5;
            break;
        case 6:
            ndefich = "bloon_6.png";
            m_speed = 7;
            m_earn = 6;
            break;
        case 7:
            ndefich = "bloon_7.png";
            m_speed = 2;
            m_earn = 7;
            break;
        case 8:
            ndefich = "bloon_8.png";
            m_speed = 2;
            m_earn = 8;
            break;
        case 9:
            ndefich = "bloon_9.png";
            m_speed = 1;
            m_earn = 9;
            break;
        case 100:
            ndefich = "bloon_10.png";
            m_speed = 21;
            m_earn = 100;
        case 200:
            ndefich = "bloon_11.png";
            m_speed = 21;
            m_earn = 100;
        default:
            break;
    }

    if(m_vie < 10 || m_vie == 100 || m_vie == 200)
        setTexture(textload->getTexture(ndefich) , BLOON);

    m_vie = inter;

    if(m_vie > 9 && m_vie < 100)
    {
        m_earn = 15;
        setTexture(textload->getTexture("bloon_shield.png") , SHIELD);
        spriteStatus(true , SHIELD);
    }
    if(m_vie > 100 && m_vie < 200)
    {
        m_earn = 15;
        setTexture(textload->getTexture("bloon_shield_1.png") , SHIELD);
        spriteStatus(true , SHIELD);
    }
}

void Bloon::findWay(int x, int y , int postab , Textureloader* textload)
{
    if(m_carte != "")
    {
        if((unsigned int)x < textload->getMap(m_carte).getSize().x && (unsigned int)y < textload->getMap(m_carte).getSize().y)
        {
            m_color = textload->getMap(m_carte).getPixel(x,y);
            if( m_color != sf::Color(0,153,0))
            {
                setPosition(sf::Vector2f(x,y));
                for( int v(0) ; v < 8 ; v++ )
                {
                    if( v == postab )
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
            if( m_color == sf::Color::Blue)
            {
                setPosition(sf::Vector2f(x,y));
                m_exit = true;
            }
        }
    }
}

int Bloon::getDamages()
{
    if(m_exit == true && m_touch == false && m_vie > 0)
    {
        return m_vie;
    }
    return 0;
}

int Bloon::isTouch(sf::Vector2f pos_ball , int damages , Textureloader* textload , int effect , int ice_limit)
{
    if(damages >= 0)
    {
        if( (pos_ball.x >= getPosition().x - 22 && pos_ball.x <= getPosition().x + 23) &&
            (pos_ball.y >= getPosition().y - 22 && pos_ball.y <= getPosition().y + 23) )
        {
            if(m_vie > 0)
            {
                switch(effect)
                {
                    case -1:
                        m_vie -= damages;
                        m_touch = true;
                        initialize(textload);
                        spriteStatus(false , ALL);
                        m_life_lost = damages;
                        break;
                    case 0:
                        m_ice++;
                        if(m_ice_limit != ice_limit)
                            m_ice_limit = ice_limit;
                        if(m_ice == m_ice_limit)
                        {
                            m_life_lost = damages;
                            m_vie -= damages;
                            m_touch = true;
                            initialize(textload);
                            m_clock.restart();
                            m_ice++;
                            m_status = m_effect::ice;
                            setTexture(textload->getTexture("ice_bloon.png") , ICE);
                            spriteStatus(true , ICE);
                            m_earn_money = true;
                        }
                        break;
                    default:
                        break;
                }
                if(m_touch)
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
    return m_vie;
}

////////////////////////////////////////
// RECHERCHE DU CHEMIN QUE DOIT SUIVRE LE BALLON
////////////////////////////////////////

void Bloon::update(Textureloader* textload)
{
    if(m_clock.getElapsedTime().asMilliseconds() >= 1000 && m_ice > m_ice_limit && m_vie > 0)
    {
        m_ice = 0;
        spriteStatus(false , ICE);
    }
    if((m_ice < m_ice_limit || m_status == m_effect::none) && m_vie > 0)
    {
        for(int n(0) ; n < m_speed ; ++n)
        {
            m_way++;
            if(m_direction[0] == true && m_find == false)
                findWay( getPosition().x + 1 , getPosition().y , 1 , textload );

            if(m_direction[2] == true && m_find == false)
                findWay( getPosition().x , getPosition().y + 1 , 3 , textload );

            if(m_direction[1] == true && m_find == false)
                findWay( getPosition().x - 1 , getPosition().y , 0 , textload );

            if(m_direction[3] == true && m_find == false)
                findWay( getPosition().x , getPosition().y - 1 , 2 , textload );

            if( m_find == false )
            {
                if(m_direction[4] == true && m_find == false)
                    findWay( getPosition().x + 1 , getPosition().y - 1 , 6 , textload );

                if(m_direction[5] == true && m_find == false)
                    findWay( getPosition().x + 1 , getPosition().y + 1 , 7 , textload );

                if(m_direction[6] == true && m_find == false)
                    findWay( getPosition().x - 1 , getPosition().y + 1 , 4 , textload );

                if(m_direction[7] == true && m_find == false)
                    findWay( getPosition().x - 1 , getPosition().y - 1 , 5 , textload );
            }
            m_find = false;
        }
    }
}
/**/
void Bloon::update()
{
}
//*/
////////////////////////////////////////
// ORDONNE LA DESTRUCTION DU BALLON
////////////////////////////////////////
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
    if(m_touch)
    {
        m_touch = false;
        if(m_status == m_effect::none && m_life_lost > 0)
            return m_earn;
        if(m_status == m_effect::ice && m_life_lost > 0 && m_earn_money == true)
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

void Bloon::setMap(string bloon_map)
{
    m_carte = bloon_map;
}
