#include "Tower.h"

Tower::Tower(int type , Textureloader* textload) : Entity()
{
    for(int r(0) ; r < 3 ; ++r)
        m_pass_canon[r] == false;
    m_up_price = false;
    m_upgrade = 1;
    m_nb_ball = 0;
    m_firerate = 0.0;
    m_type = type;
    m_clock.restart();
    m_shoot = true;
    setOrigin(40 , 60);
    m_damages = 0;
    m_cost = 0;
    m_color = sf::Color::Black;
    Init(textload);
}

Tower::Tower(int type , Textureloader* textload , sf::Vector2f position) : Entity()
{
    m_upgrade = 1;
    m_nb_ball = 0;
    m_firerate = 0.0;
    m_type = type;
    m_clock.restart();
    m_shoot = true;
    setPosition(position);
    std::cout << "tower pos : x = " << position.x << " et y = " << position.y << std::endl;
    m_damages = 0;
    m_color = sf::Color::Black;
    Init(textload);
}

Tower::~Tower()
{
    m_last_pos.clear();
    m_bullet.clear();
    m_forward.clear();
    m_incrementation.clear();
}

void Tower::update()
{
}

void Tower::iceMove(int r)
{
    m_incrementation[r]++;
    if(m_incrementation[r] < 20 )
    {
        m_forward[r].x = sin(m_bullet[r].getRotation()*(3.1415f / 180.0f));
        m_forward[r].y = -cos(m_bullet[r].getRotation()*(3.1415f / 180.0f));
    }
    if(m_incrementation[r] >= 20 && m_incrementation[r] < 90)
    {
        m_radian = (float)rand()*0.5f;
        m_forward[r].x = sin((m_bullet[r].getRotation() + m_radian)*(3.1415f / 180.0f));
        m_forward[r].y = -cos((m_bullet[r].getRotation() + m_radian)*(3.1415f / 180.0f));
    }
    if(m_incrementation[r] >= 90 && m_incrementation[r] <= 150)
    {
        m_forward[r].x = rand();
        m_forward[r].y = rand();
    }
    if(m_incrementation[r] > 150)
    {
        m_bullet.erase( m_bullet.begin() + r );
        m_last_pos.erase(m_last_pos.begin() + r);
        m_incrementation.erase(m_incrementation.begin() + r);
        m_forward.erase(m_forward.begin() + r);
    }
}

void Tower::drawBullet(sf::RenderWindow* screen)
{
    for(int r(0) ; r < m_bullet.size() ; ++r)
    {
        if(m_type_effect == m_effect::ice)
        {
            iceMove(r);
            screen->draw(m_bullet[r]);
        }
        else
        {
            sf::Vector2f bullet_to_bloon;
            bullet_to_bloon = m_last_pos[r] - m_bullet[r].getPosition();
            //std::cout << "m_bullet[" << r << "], x = " << m_bullet[r].getPosition().x << " et y = " << m_bullet[r].getPosition().y << " , @ : " << &m_bullet[r].getPosition() << std::endl;

            if((bullet_to_bloon.x*m_forward[r].x + bullet_to_bloon.y*m_forward[r].y) <= 0)
            {
                m_bullet.erase( m_bullet.begin() + r );
                m_last_pos.erase(m_last_pos.begin() + r);
                m_forward.erase(m_forward.begin() + r);
            }
            else
            {
                m_bullet[r].move(m_forward[r]);
                screen->draw(m_bullet[r]);
            }
        }

    }
}

int Tower::Fire(sf::Vector2f bloon)
{
    bool pass(false);
    m_tir = m_clock.getElapsedTime().asMilliseconds();
    if(m_tir >= m_firerate && bloon.x >= 0 && bloon.y >= 0)
    {
        m_last_pos.push_back(bloon);
        m_bullet.push_back(sf::RectangleShape(sf::Vector2f(5,12)));
        m_bullet.back().setOrigin(2 , 6);
        if(m_canon == 1 || m_pass_canon[0] == true)
        {
            pass = true;
            m_bullet.back().setPosition(getPosition().x - 7 , getPosition().y);
            if(m_bullet.back().getPosition().x == 0 && m_bullet.back().getPosition().y == 0)
                std::cout << ":(  0" << std::endl;
        }
        if(m_canon == 2 || m_pass_canon[1] == true)
        {
            pass = true;
            m_bullet.back().setPosition(getPosition().x + 7 , getPosition().y);
            if(m_bullet.back().getPosition().x == 0 && m_bullet.back().getPosition().y == 0)
                std::cout << ":(  1" << std::endl;
        }
        if(m_canon == 4 || m_pass_canon[2] == true)
        {
            pass = true;
            m_bullet.back().setPosition(getPosition().x , getPosition().y);
            if(m_bullet.back().getPosition().x == 0 && m_bullet.back().getPosition().y == 0)
                std::cout << ":(  2" << std::endl;
        }
        m_bullet.back().rotate(getRotation());
        if(m_type_effect == m_effect::ice)
        {
            pass = true;
            m_incrementation.push_back(0);
            m_bullet.back().setSize(sf::Vector2f(2,2));
            m_bullet.back().setOrigin(1 , 1);
            m_bullet.back().setPosition(getPosition().x , getPosition().y);
            /*
            m_bullet.back().move( 40*sin(m_bullet.back().getRotation()*(3.1415f / 180.0f)) ,
                                 -40*cos(m_bullet.back().getRotation()*(3.1415f / 180.0f)));
                                 //*/
        }
        if(pass == true)
        {
            bool change(false);
            /*
            if(m_pass_canon[1] == true || m_pass_canon[2] == true)
                m_pass_canon[0] = true;
            if(m_pass_canon[0] == true || m_pass_canon[2] == true)
                m_pass_canon[1] = true;
            if(m_pass_canon[1] == true || m_pass_canon[0] == true)
                m_pass_canon[2] = true;
                //*/
            if((m_canon == 5 || m_canon == 6 || m_canon == 7) && (m_pass_canon[2] == true && change == false))
            {
                m_pass_canon[2] = false;
                m_pass_canon[0] = true;
                change = true;
            }
            if((m_canon == 3 || m_canon == 5 || m_canon == 7) && (m_pass_canon[0] == true && change == false))
            {
                change = true;
                m_pass_canon[0] = false;
                m_pass_canon[1] = true;
            }
            if((m_canon == 3 || m_canon == 6 || m_canon == 7) && (m_pass_canon[1] == true && change == false))
            {
                change = true;
                m_pass_canon[1] = false;
                m_pass_canon[2] = true;
            }
            /*
            if(m_pass_canon[1] == false && m_pass_canon[0] == false && m_pass_canon[2] == false)
            {
                std::cout << m_pass_canon[0] << " " << m_pass_canon[1] << " " << m_pass_canon[2] << std::endl;
            }
            //*/
        }
        m_forward.push_back(sf::Vector2f(30 * sin(m_bullet.back().getRotation()*(3.1415f / 180.0f)) ,
                                         -30 * cos(m_bullet.back().getRotation()*(3.1415f / 180.0f))));
        m_clock.restart();
        return m_damages;
    }
    return 0;
}

void Tower::destroyBullet()
{
    if(m_bullet.size() != 0)
        m_bullet.pop_front();
}

sf::Vector2f Tower::getBullet(int a)
{
    return m_bullet[a].getPosition();
}

int Tower::getNumberBullet()
{
    return m_bullet.size();
}

int Tower::Sell()
{
    m_cost *= 0.75;
    return m_cost;
}

int Tower::getCost()
{
    return m_cost;
}

void Tower::upgradeLeft(Textureloader* textload)
{
    if(m_upgrade < 6)
        m_upgrade++;
    Init(textload);
}

void Tower::upgradeRight(Textureloader* textload)
{
    if(m_upgrade == 1)
        m_upgrade = 6;
    if(m_upgrade < 9)
        m_upgrade++;
    Init(textload);
}

void Tower::Init(Textureloader* textload)
{
    m_pass_canon[0] = true;
    m_canon = 7;
    switch(m_type)
    {
        case 1:
            m_turrets = 3;
            switch(m_upgrade)
            {
                case 1:
                    setTexture(textload->Gettexture("tower_1_1.png"));
                    m_firerate = 750.0;
                    m_portee = 100;
                    m_damages = 1;
                    m_type_effect = m_effect::none;
                    m_cost = 10;
                    break;
                case 2:
                    setTexture(textload->Gettexture("tower_1_2.png"));
                    m_firerate = 650.0;
                    m_portee = 110;
                    m_damages = 1;
                    m_color = sf::Color(50,50,50);
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 3:
                    setTexture(textload->Gettexture("tower_1_3.png"));
                    m_firerate = 600.0;
                    m_portee = 120;
                    m_damages = 1;
                    m_color = sf::Color(70,70,70);
                    m_type_effect = m_effect::none;
                    m_cost += 20;
                    break;
                case 4:
                    setTexture(textload->Gettexture("tower_1_4.png"));
                    m_firerate = 300.0;
                    m_portee = 130;
                    m_damages = 1;
                    m_color = sf::Color(90,90,90);
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 5:
                    setTexture(textload->Gettexture("tower_1_5.png"));
                    m_firerate = 100.0;
                    m_portee = 150;
                    m_damages = 1;
                    m_color = sf::Color(0,0,255);
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 6:
                    setTexture(textload->Gettexture("tower_1_6.png"));
                    m_firerate = 900.0;
                    m_portee = 120;
                    m_damages = 1;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 7:
                    setTexture(textload->Gettexture("tower_1_7.png"));
                    m_firerate = 850.0;
                    m_portee = 150;
                    m_damages = 1;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 8:
                    setTexture(textload->Gettexture("tower_1_8.png"));
                    m_firerate = 775.0;
                    m_portee = 160;
                    m_damages = 2;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 9:
                    setTexture(textload->Gettexture("tower_1_9.png"));
                    m_firerate = 700.0;
                    m_portee = 200;
                    m_damages = 3;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                default:
                    break;
            }
            break;
        case 2:
            m_turrets = 3;
            switch(m_upgrade)
            {
                case 1:
                    setTexture(textload->Gettexture("tower_2_1.png"));
                    m_firerate = 666.0;
                    m_portee = 100;
                    m_damages = 1;
                    m_type_effect = m_effect::none;
                    m_cost = 20;
                    break;
                case 2:
                    setTexture(textload->Gettexture("tower_2_2.png"));
                    m_firerate = 650.0;
                    m_portee = 150;
                    m_damages = 1;
                    m_color = sf::Color::Yellow;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 3:
                    setTexture(textload->Gettexture("tower_2_3.png"));
                    m_firerate = 600.0;
                    m_portee = 200;
                    m_damages = 1;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 4:
                    setTexture(textload->Gettexture("tower_2_4.png"));
                    m_firerate = 600.0;
                    m_portee = 250;
                    m_damages = 1;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 5:
                    setTexture(textload->Gettexture("tower_2_5.png"));
                    m_firerate = 600.0;
                    m_portee = 300;
                    m_damages = 1;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 6:
                    setTexture(textload->Gettexture("tower_2_6.png"));
                    m_firerate = 625.0;
                    m_portee = 110;
                    m_damages = 1;
                    m_color = sf::Color::Red;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 7:
                    setTexture(textload->Gettexture("tower_2_7.png"));
                    m_firerate = 600.0;
                    m_portee = 150;
                    m_damages = 2;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 8:
                    setTexture(textload->Gettexture("tower_2_8.png"));
                    m_firerate = 575.0;
                    m_portee = 160;
                    m_damages = 3;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 9:
                    setTexture(textload->Gettexture("tower_2_9.png"));
                    m_firerate = 550.0;
                    m_portee = 170;
                    m_damages = 4;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                default:
                    break;
            }
            break;
        case 3:
            m_turrets = 2;
            switch(m_upgrade)
            {
                case 1:
                    setTexture(textload->Gettexture("tower_3_1.png"));
                    m_firerate = 666.0;
                    m_portee = 125;
                    m_damages = 2;
                    m_type_effect = m_effect::none;
                    m_cost = 30;
                    break;
                case 2:
                    setTexture(textload->Gettexture("tower_3_2.png"));
                    m_firerate = 666.0;
                    m_portee = 125;
                    m_damages = 3;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 3:
                    setTexture(textload->Gettexture("tower_3_3.png"));
                    m_firerate = 600.0;
                    m_portee = 140;
                    m_damages = 3;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 4:
                    setTexture(textload->Gettexture("tower_3_4.png"));
                    m_firerate = 550.0;
                    m_portee = 160;
                    m_damages = 4;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 5:
                    setTexture(textload->Gettexture("tower_3_5.png"));
                    m_firerate = 500.0;
                    m_portee = 170;
                    m_damages = 5;
                    m_color = sf::Color(0,0,255,128);
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 6:
                    setTexture(textload->Gettexture("tower_3_6.png"));
                    m_firerate = 750.0;
                    m_portee = 125;
                    m_damages = 2;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 7:
                    setTexture(textload->Gettexture("tower_3_7.png"));
                    m_firerate = 700.0;
                    m_portee = 135;
                    m_damages = 2;
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 8:
                    setTexture(textload->Gettexture("tower_3_8.png"));
                    m_firerate = 650.0;
                    m_portee = 145;
                    m_damages = 4;
                    m_color = sf::Color(255,255,255);
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
                case 9:
                    setTexture(textload->Gettexture("tower_3_9.png"));
                    m_firerate = 600.0;
                    m_portee = 150;
                    m_damages = 8;
                    m_color = sf::Color(255,255,255,128);
                    m_type_effect = m_effect::none;
                    m_cost += 15;
                    break;
            }
            break;
        case 4:
            m_canon == 2;
            switch(m_upgrade)
            {
                case 1:
                    setTexture(textload->Gettexture("tower_4_1.png"));
                    m_firerate = 50;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 30;
                    m_type_effect = m_effect::ice;
                    m_cost = 40;
                    break;
                case 2:
                    setTexture(textload->Gettexture("tower_4_2.png"));
                    m_firerate = 40;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 30;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
                case 3:
                    setTexture(textload->Gettexture("tower_4_3.png"));
                    m_firerate = 30;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 30;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
                case 4:
                    setTexture(textload->Gettexture("tower_4_4.png"));
                    m_firerate = 20;
                    m_portee = 75;
                    m_damages = 1;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 30;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
                case 5:
                    setTexture(textload->Gettexture("tower_4_5.png"));
                    m_firerate = 0;
                    m_portee = 75;
                    m_damages = 1;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 30;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
                case 6:
                    setTexture(textload->Gettexture("tower_4_6.png"));
                    m_firerate = 30;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 25;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
                case 7:
                    setTexture(textload->Gettexture("tower_4_7.png"));
                    m_firerate = 25;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 20;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
                case 8:
                    setTexture(textload->Gettexture("tower_4_8.png"));
                    m_firerate = 25;
                    m_portee = 75;
                    m_damages = 1;
                    m_color = sf::Color(200,200,180,180);
                    m_nb_ball = 15;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
                case 9:
                    setTexture(textload->Gettexture("tower_4_9.png"));
                    m_firerate = 0;
                    m_portee = 75;
                    m_damages = 1;
                    m_color = sf::Color(255,255,255,200);
                    m_nb_ball = 5;
                    m_type_effect = m_effect::ice;
                    m_cost += 15;
                    break;
            }
            break;
        default:
            break;
    }
    setRange(m_portee);
    setOrigin(40 , 60);
}

int Tower::getEffect()
{
    return m_type_effect;
}

int Tower::getNbBall()
{
    if(m_type_effect == m_effect::ice)
        return m_nb_ball;
    else
        return 0;
}

std::string Tower::getPrice()
{
    std::stringstream chaine;
    chaine << m_cost;
    std::string a;
    a = chaine.str();
    return a;
}

std::string Tower::getLeftUpgrade()
{
    if(m_upgrade == 1 || m_upgrade < 5)
    {
        std::string a;
        std::stringstream b , c;
        b << m_type;
        c << (m_upgrade + 1);
        a = "tower_" + b.str() + "_" + c.str() + ".png";
        return a;
    }
    return "";
}

std::string Tower::getRightUpgrade()
{
    if((m_upgrade == 1) || (m_upgrade > 5 && m_upgrade != 9))
    {
        if(m_upgrade != 1)
        {
            std::string a;
            std::stringstream b , c;
            b << m_type;
            c << (m_upgrade + 1);
            a = "tower_" + b.str() + "_" + c.str() + ".png";
            return a;
        }
        else
        {
            std::stringstream b;
            b << m_type;
            return "tower_" + b.str() + "_6.png";
        }
    }
    return "";
}

int Tower::getUpPrice(Textureloader* textload)
{
    int up(0);
    if((m_upgrade > 5 && m_upgrade < 9) || (m_upgrade > 1 && m_upgrade < 5) || m_upgrade == 1)
    {
        if(m_upgrade == 1)
        {
            m_up_price = !m_up_price;
            if(m_up_price == false)
                up = 6;
            else
                up = 2;
        }
        else
        {
            up = m_upgrade + 1;
        }
        int c = m_upgrade;
        m_upgrade = up;
        int b(m_cost);
        Init(textload);
        int a = m_cost - b;
        m_upgrade = c;
        Init(textload);
        return a;
    }
}
