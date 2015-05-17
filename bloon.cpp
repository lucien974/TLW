#include "bloon.h"

Bloon::Bloon(sf::Image carte_v , int type , Textureloader* textload) : Entity()
{
    m_vie = 0;
    m_speed = 0;
    m_carte_v = carte_v;
    for( int m(0) ; m < 8 ; m++ )
    {
        m_direction[m] = true;
    }
    m_hunt = false;
    m_enter = true;
    m_sound.setBuffer(textload->Getbuffer("pop.ogg"));
    m_earn = 0;
    m_way = 0;
    m_first = true;
    m_touch = false;
    m_kill = false;
    Init(type , textload);
    m_exit = false;
}

Bloon::~Bloon()
{

}

////////////////////////////////////////
// INITIALISATION
////////////////////////////////////////

void Bloon::Init(int type , Textureloader* textload)
{
    m_vie = type;
    std::string ndefich = "";
    int inter(m_earn);
    switch(type)
    {
        case 1:
            ndefich = "bloon_1.png";
            m_speed = 1;
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
            m_speed = 4;
            m_earn = 5;
            break;
        case 6:
            ndefich = "bloon_6.png";
            m_speed = 4;
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
    }
    if(m_first == true)
    {
        m_first = false;
    }
    else
    {
        if(m_touch == true)
        {
            m_earn = 0;
        }
    }
    if(inter > m_earn)
        m_earn = inter;
    setTexture(textload->Gettexture(ndefich));
}

void Bloon::Findway(int x, int y , int postab)
{
    if(x < m_carte_v.getSize().x && y < m_carte_v.getSize().y)
    {
        m_color = m_carte_v.getPixel(x,y);

        if( m_color.b == 0 && m_color.r == 255 && m_color.g == 0 && m_enter == true)
        {
            m_enter = false;
            setPosition(x,y);
        }
        if( m_color == sf::Color::White && m_hunt == true)
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
            m_carte_v.setPixel(x,y,sf::Color::Black);
        }
        if( m_color == sf::Color::Blue && m_hunt == true )
        {
            setPosition(x,y);
            m_kill = true;
        }
        m_position_x = getPosition().x;
        m_position_y = getPosition().y;
    }
}

int Bloon::Getdamages()
{
    if(m_kill == true)
    {
        m_exit = true;
        m_kill = false;
        std::cout << m_vie << std::endl;
        return m_vie;
    }
    return 0;
}

int Bloon::Touch(int ball_pos_x , int ball_pos_y , int damages , Textureloader* textload)
{
    ball_pos_x = getPosition().x;
    ball_pos_y = getPosition().y;
    if(damages > 0)
    {
        if( (ball_pos_x >= getPosition().x - getOrigin().x && ball_pos_x <= getPosition().x - getOrigin().x + 60) &&
            (ball_pos_y >= getPosition().y - getOrigin().y && ball_pos_y <= getPosition().y - getOrigin().y + 60) )
        {
            m_vie -= damages;
            if(m_vie > 0)
            {
                m_sound.play();
                Init(m_vie , textload);
            }
            else
            {
                m_exit = true;
                m_touch = true;
            }
            return 0;
        }
    }
    return damages;
}

////////////////////////////////////////
// RECHERCHE DU CHEMIN QUE DOIT SUIVRE LE BALLON
////////////////////////////////////////

void Bloon::update()
{
    m_way++;
    m_position_x = getPosition().x;
    m_position_y = getPosition().y;
    for(int n(0) ; n < m_speed ; ++n)
    {
        if(m_hunt == false)
        {
            for( int za(0) ; za < m_carte_v.getSize().x ; za++ )
            {
                for( int j(0) ; j < m_carte_v.getSize().y ; j++ )
                {
                    Findway( za , j , -1 );
                }
            }
            m_hunt = true;
        }
        if(m_direction[0] == true && m_find == false)
            Findway( m_position_x + 1 , m_position_y , 1 );

        if(m_direction[2] == true && m_find == false)
            Findway( m_position_x , m_position_y + 1 , 3 );

        if(m_direction[1] == true && m_find == false)
            Findway( m_position_x - 1 , m_position_y , 0 );

        if(m_direction[3] == true && m_find == false)
            Findway( m_position_x , m_position_y - 1 , 2 );

        if( m_find == false )
        {
            if(m_direction[4] == true && m_find == false)
                Findway( m_position_x + 1 , m_position_y - 1 , 6 );

            if(m_direction[5] == true && m_find == false)
                Findway( m_position_x + 1 , m_position_y + 1 , 7 );

            if(m_direction[6] == true && m_find == false)
                Findway( m_position_x - 1 , m_position_y + 1 , 4 );

            if(m_direction[7] == true && m_find == false)
                Findway( m_position_x - 1 , m_position_y - 1 , 5 );
        }
        m_find = false;
    }
}

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
    if(m_touch == true)
    {
        m_touch = false;
        return m_earn;
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
