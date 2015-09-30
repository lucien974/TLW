#include "bloon.h"

Bloon::Bloon(int type , Textureloader* textload , std::string carte) : Entity()
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
    Init(textload);
    m_exit = false;
    m_carte = carte;
    setPosition(textload->getRedPxl(carte));
    m_status = m_effect::none;
    //setEffect(textload->Gettexture("ice_bloon.png"));
}

Bloon::~Bloon()
{
}

////////////////////////////////////////
// INITIALISATION
////////////////////////////////////////

void Bloon::Init(Textureloader* textload)
{
    std::string ndefich = "";
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
    if(m_vie > 9 && m_vie <= 20)
    {
        m_earn = 15;
        m_speed = 3;
        setTexture(textload->Gettexture("bloon_1.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie <= 30 && m_vie > 20)
    {
        m_earn = 25;
        m_speed = 4;
        setTexture(textload->Gettexture("bloon_2.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie <= 40 && m_vie > 30)
    {
        m_earn = 35;
        m_speed = 5;
        setTexture(textload->Gettexture("bloon_3.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie <= 50 && m_vie > 40)
    {
        m_earn = 45;
        m_speed = 5;
        setTexture(textload->Gettexture("bloon_4.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie <= 60 && m_vie > 50)
    {
        m_earn = 55;
        m_speed = 8;
        setTexture(textload->Gettexture("bloon_5.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie <= 70 && m_vie > 60)
    {
        m_earn = 65;
        m_speed = 8;
        setTexture(textload->Gettexture("bloon_6.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie <= 80 && m_vie > 70)
    {
        m_earn = 75;
        m_speed = 4;
        setTexture(textload->Gettexture("bloon_7.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie <= 90 && m_vie > 80)
    {
        m_earn = 85;
        m_speed = 4;
        setTexture(textload->Gettexture("bloon_8.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie < 100 && m_vie > 90)
    {
        m_earn = 95;
        m_speed = 4;
        setTexture(textload->Gettexture("bloon_9.png") , textload->Gettexture("bloon_shield.png"));
    }
    if(m_vie > 100 && m_vie <= 120)
    {
        m_earn = 15;
        m_speed = 3;
        setTexture(textload->Gettexture("bloon_1.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie <= 130 && m_vie > 120)
    {
        m_earn = 25;
        m_speed = 6;
        setTexture(textload->Gettexture("bloon_2.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie <= 140 && m_vie > 130)
    {
        m_earn = 35;
        m_speed = 7;
        setTexture(textload->Gettexture("bloon_3.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie <= 150 && m_vie > 140)
    {
        m_earn = 100;
        m_speed = 7;
        setTexture(textload->Gettexture("bloon_4.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie <= 160 && m_vie > 150)
    {
        m_earn = 105;
        m_speed = 12;
        setTexture(textload->Gettexture("bloon_5.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie <= 170 && m_vie > 160)
    {
        m_earn = 110;
        m_speed = 15;
        setTexture(textload->Gettexture("bloon_6.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie <= 180 && m_vie > 170)
    {
        m_earn = 115;
        m_speed = 6;
        setTexture(textload->Gettexture("bloon_7.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie <= 190 && m_vie > 180)
    {
        m_earn = 120;
        m_speed = 6;
        setTexture(textload->Gettexture("bloon_8.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie < 200 && m_vie > 190)
    {
        m_earn = 125;
        m_speed = 6;
        setTexture(textload->Gettexture("bloon_9.png") , textload->Gettexture("bloon_shield_1.png"));
    }
    if(m_vie < 10 || m_vie == 100 || m_vie == 200)
        setTexture(textload->Gettexture(ndefich));
}

void Bloon::Findway(int x, int y , int postab , Textureloader* textload)
{
    if(x < textload->Getmap(m_carte).getSize().x && y < textload->Getmap(m_carte).getSize().y)
    {
        m_color = textload->Getmap(m_carte).getPixel(x,y);
        if( m_color == sf::Color::White)
        {
            setPosition(x,y);
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
            setPosition(x,y);
            m_exit = true;
        }
    }
}

int Bloon::Getdamages()
{
    if(m_exit == true && m_touch == false)
    {
        return m_vie;
    }
    return 0;
}

int Bloon::Touch(sf::Vector2f pos_ball , int damages , Textureloader* textload , int effect , int ice_limit)
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
                        Init(textload);
                        disableEffect();
                        m_life_lost = damages;
                        break;
                    case 0:
                        m_ice++;
                        if(m_ice_limit != ice_limit)
                            m_ice_limit = ice_limit;
                        if(m_ice == m_ice_limit)
                        {
                            m_vie -= damages;
                            m_touch = true;
                            Init(textload);
                            m_clock.restart();
                            m_ice++;
                            m_status = m_effect::ice;
                            setEffect(textload->Gettexture("ice_bloon.png") , m_status);
                            m_earn_money = true;
                        }
                        break;
                    default:
                        disableEffect();
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

void Bloon::Update(Textureloader* textload)
{
    if(m_clock.getElapsedTime().asMilliseconds() >= 1000 && m_ice > m_ice_limit && m_vie > 0)
    {
        m_ice = 0;
        disableEffect();
    }
    if((m_ice < m_ice_limit || m_status == m_effect::none) && m_vie > 0)
    {
        for(int n(0) ; n < m_speed ; ++n)
        {
            m_way++;
            if(m_direction[0] == true && m_find == false)
                Findway( getPosition().x + 1 , getPosition().y , 1 , textload );

            if(m_direction[2] == true && m_find == false)
                Findway( getPosition().x , getPosition().y + 1 , 3 , textload );

            if(m_direction[1] == true && m_find == false)
                Findway( getPosition().x - 1 , getPosition().y , 0 , textload );

            if(m_direction[3] == true && m_find == false)
                Findway( getPosition().x , getPosition().y - 1 , 2 , textload );

            if( m_find == false )
            {
                if(m_direction[4] == true && m_find == false)
                    Findway( getPosition().x + 1 , getPosition().y - 1 , 6 , textload );

                if(m_direction[5] == true && m_find == false)
                    Findway( getPosition().x + 1 , getPosition().y + 1 , 7 , textload );

                if(m_direction[6] == true && m_find == false)
                    Findway( getPosition().x - 1 , getPosition().y + 1 , 4 , textload );

                if(m_direction[7] == true && m_find == false)
                    Findway( getPosition().x - 1 , getPosition().y - 1 , 5 , textload );
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
bool Bloon::Exit()
{
    return m_exit;
}

int Bloon::Getspeed()
{
    return m_speed;
}

int Bloon::Getmoney()
{
    if(m_touch)
    {
        m_touch == false;
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

int Bloon::Getincrementation()
{
    return m_way;
}

void Bloon::Setspeed(int speed)
{
    m_speed = speed;
}
