#include "Tower.h"

Tower::Tower(int type, Textureloader* textload, sf::Vector2f position) :
Entity(),
m_shoot(true),
m_up_price(false),
m_tir(0.0f),
m_firerate(0.0f),
m_radian(0.0f),
m_portee(0),
m_cost(0),
m_type(type),
m_damages(0),
m_turrets(0),
m_nb_ball(0),
m_type_effect(0),
m_upgrade(1),
m_canon(0),
m_color(sf::Color::Black)
{
    for (int r(0); r < 3; ++r)
        m_pass_canon[r] = false;
    initialize(textload);
    m_effect_move = new TowerEffect(m_type_effect);
    setPosition(position);
    m_clock.restart();
}

Tower::~Tower()
{
    m_last_pos.clear();
    m_bullet.clear();
    m_forward.clear();
    m_incrementation.clear();
    delete m_effect_move;
}

void Tower::update()
{
}

void Tower::drawBullet(sf::RenderWindow* screen)
{
    for (unsigned int r(0); r < m_bullet.size(); ++r)
    {
        sf::Vector2f bullet_to_bloon = m_last_pos[r] - m_bullet[r].getPosition();
        if (m_effect_move->update(m_incrementation[r], bullet_to_bloon, m_forward[r], m_bullet[r].getRotation()))
        {
            m_bullet[r].move(m_forward[r]);
            screen->draw(m_bullet[r]);
        }
        else
        {
            switch (m_type_effect)
            {
                case m_effect::none:
                    m_bullet.erase(m_bullet.begin() + r);
                    m_last_pos.erase(m_last_pos.begin() + r);
                    m_forward.erase(m_forward.begin() + r);
                    break;
                case m_effect::ice:
                    m_bullet.erase(m_bullet.begin() + r);
                    m_last_pos.erase(m_last_pos.begin() + r);
                    m_incrementation.erase(m_incrementation.begin() + r);
                    m_forward.erase(m_forward.begin() + r);
                    break;
                default:
                    std::cout << "unknown type of tower" << std::endl;
                    break;
            }
        }
    }
}

int Tower::shoot(sf::Vector2f bloon)
{
    bool pass(false);
    m_tir = m_clock.getElapsedTime().asMilliseconds();
    if (m_tir >= m_firerate && bloon.x >= 0 && bloon.y >= 0 && m_bullet.size() < 15000)
    {
        m_last_pos.push_back(bloon);
        m_bullet.push_back(sf::RectangleShape(sf::Vector2f(5, 12)));
        m_bullet.back().setOrigin(2, 6);
        m_bullet.back().setFillColor(m_color);
        if (m_canon == 1 || m_pass_canon[0] == true)
        {
            pass = true;
            m_bullet.back().setPosition(getPosition().x - 7, getPosition().y);
        }
        if (m_canon == 2 || m_pass_canon[1] == true)
        {
            pass = true;
            m_bullet.back().setPosition(getPosition().x + 7, getPosition().y);
        }
        if (m_canon == 4 || m_pass_canon[2] == true)
        {
            pass = true;
            m_bullet.back().setPosition(getPosition().x, getPosition().y);
        }
        if (m_bullet.back().getPosition().x == 0 && m_bullet.back().getPosition().y == 0)
        {
            std::cout << "error, x : " << getPosition().x << ", y : " << getPosition().y << ", pass : " << pass << std::endl;
            std::cout << "0 : " << m_pass_canon[0] << ", 1 : " << m_pass_canon[1] << ", 2 : " << m_pass_canon[2] << std::endl;
        }
        m_bullet.back().rotate(getRotation());
        if (m_type_effect == m_effect::ice)
        {
            pass = true;
            m_incrementation.push_back(0);
            m_bullet.back().setSize(sf::Vector2f(2, 2));
            m_bullet.back().setOrigin(1, 1);
            m_bullet.back().setPosition(getPosition().x, getPosition().y);
        }
        if (pass == true)
        {
            bool change(false);
            if ((m_canon == 5 || m_canon == 6 || m_canon == 7) && (m_pass_canon[2] == true && change == false))
            {
                m_pass_canon[2] = false;
                m_pass_canon[0] = true;
                change = true;
            }
            if ((m_canon == 3 || m_canon == 5 || m_canon == 7) && (m_pass_canon[0] == true && change == false))
            {
                change = true;
                m_pass_canon[0] = false;
                m_pass_canon[1] = true;
            }
            if ((m_canon == 3 || m_canon == 6 || m_canon == 7) && (m_pass_canon[1] == true && change == false))
            {
                change = true;
                m_pass_canon[1] = false;
                m_pass_canon[2] = true;
            }
        }
        m_forward.push_back(sf::Vector2f(30 * std::sin(m_bullet.back().getRotation()*(3.1415f / 180.0f)),
                                         -30 * std::cos(m_bullet.back().getRotation()*(3.1415f / 180.0f))));
        m_clock.restart();
        return m_damages;
    }
    return 0;
}

void Tower::destroyBullet()
{
    if (m_bullet.size() != 0)
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

int Tower::sell()
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
    if (m_upgrade < 6)
        m_upgrade++;
    initialize(textload);
}

void Tower::upgradeRight(Textureloader* textload)
{
    if (m_upgrade < 9 && m_upgrade > 5)
        m_upgrade++;
    else if (m_upgrade == 1)
        m_upgrade = 6;
    initialize(textload);
}

void Tower::initialize(Textureloader* textload)
{
    m_pass_canon[0] = true;
    m_canon = 7;
    getTowerPrice();
    switch (m_type)
    {
        case 1:
            m_turrets = 3;
            m_type_effect = m_effect::none;
            switch (m_upgrade)
            {
                case 1:
                    setTexture(textload->getTexture("tower_1_1.png"), TOWER);
                    m_firerate = 750.0;
                    m_portee = 100;
                    m_damages = 1;
                    break;
                case 2:
                    setTexture(textload->getTexture("tower_1_2.png"), TOWER);
                    m_firerate = 650.0;
                    m_portee = 110;
                    m_damages = 1;
                    m_color = sf::Color(50, 50, 50);
                    break;
                case 3:
                    setTexture(textload->getTexture("tower_1_3.png"), TOWER);
                    m_firerate = 600.0;
                    m_portee = 120;
                    m_damages = 1;
                    m_color = sf::Color(70, 70, 70);
                    break;
                case 4:
                    setTexture(textload->getTexture("tower_1_4.png"), TOWER);
                    m_firerate = 300.0;
                    m_portee = 130;
                    m_damages = 1;
                    m_color = sf::Color(90, 90, 90);
                    break;
                case 5:
                    setTexture(textload->getTexture("tower_1_5.png"), TOWER);
                    m_firerate = 100.0;
                    m_portee = 150;
                    m_damages = 1;
                    m_color = sf::Color(0, 0, 255);
                    break;
                case 6:
                    setTexture(textload->getTexture("tower_1_6.png"), TOWER);
                    m_firerate = 900.0;
                    m_portee = 120;
                    m_damages = 1;
                    break;
                case 7:
                    setTexture(textload->getTexture("tower_1_7.png"), TOWER);
                    m_firerate = 850.0;
                    m_portee = 150;
                    m_damages = 1;
                    break;
                case 8:
                    setTexture(textload->getTexture("tower_1_8.png"), TOWER);
                    m_firerate = 775.0;
                    m_portee = 160;
                    m_damages = 2;
                    break;
                case 9:
                    setTexture(textload->getTexture("tower_1_9.png"), TOWER);
                    m_firerate = 700.0;
                    m_portee = 200;
                    m_damages = 3;
                    break;
                default:
                    break;
            }
            break;
        case 2:
            m_turrets = 3;
            m_type_effect = m_effect::none;
            switch (m_upgrade)
            {
                case 1:
                    setTexture(textload->getTexture("tower_2_1.png"), TOWER);
                    m_firerate = 666.0;
                    m_portee = 100;
                    m_damages = 1;
                    break;
                case 2:
                    setTexture(textload->getTexture("tower_2_2.png"), TOWER);
                    m_firerate = 650.0;
                    m_portee = 150;
                    m_damages = 1;
                    m_color = sf::Color::Yellow;
                    break;
                case 3:
                    setTexture(textload->getTexture("tower_2_3.png"), TOWER);
                    m_firerate = 600.0;
                    m_portee = 200;
                    m_damages = 1;
                    break;
                case 4:
                    setTexture(textload->getTexture("tower_2_4.png"), TOWER);
                    m_firerate = 600.0;
                    m_portee = 250;
                    m_damages = 1;
                    break;
                case 5:
                    setTexture(textload->getTexture("tower_2_5.png"), TOWER);
                    m_firerate = 600.0;
                    m_portee = 300;
                    m_damages = 1;
                    break;
                case 6:
                    setTexture(textload->getTexture("tower_2_6.png"), TOWER);
                    m_firerate = 625.0;
                    m_portee = 110;
                    m_damages = 1;
                    m_color = sf::Color::Red;
                    break;
                case 7:
                    setTexture(textload->getTexture("tower_2_7.png"), TOWER);
                    m_firerate = 600.0;
                    m_portee = 150;
                    m_damages = 2;
                    break;
                case 8:
                    setTexture(textload->getTexture("tower_2_8.png"), TOWER);
                    m_firerate = 575.0;
                    m_portee = 160;
                    m_damages = 3;
                    break;
                case 9:
                    setTexture(textload->getTexture("tower_2_9.png"), TOWER);
                    m_firerate = 550.0;
                    m_portee = 170;
                    m_damages = 4;
                    break;
                default:
                    break;
            }
            break;
        case 3:
            m_turrets = 2;
            m_type_effect = m_effect::none;
            switch (m_upgrade)
            {
                case 1:
                    setTexture(textload->getTexture("tower_3_1.png"), TOWER);
                    m_firerate = 666.0;
                    m_portee = 125;
                    m_damages = 2;
                    break;
                case 2:
                    setTexture(textload->getTexture("tower_3_2.png"), TOWER);
                    m_firerate = 666.0;
                    m_portee = 125;
                    m_damages = 3;
                    break;
                case 3:
                    setTexture(textload->getTexture("tower_3_3.png"), TOWER);
                    m_firerate = 600.0;
                    m_portee = 140;
                    m_damages = 3;
                    break;
                case 4:
                    setTexture(textload->getTexture("tower_3_4.png"), TOWER);
                    m_firerate = 550.0;
                    m_portee = 160;
                    m_damages = 4;
                    break;
                case 5:
                    setTexture(textload->getTexture("tower_3_5.png"), TOWER);
                    m_firerate = 500.0;
                    m_portee = 170;
                    m_damages = 5;
                    m_color = sf::Color(0, 0, 255, 128);
                    break;
                case 6:
                    setTexture(textload->getTexture("tower_3_6.png"), TOWER);
                    m_firerate = 750.0;
                    m_portee = 125;
                    m_damages = 2;
                    break;
                case 7:
                    setTexture(textload->getTexture("tower_3_7.png"), TOWER);
                    m_firerate = 700.0;
                    m_portee = 135;
                    m_damages = 2;
                    break;
                case 8:
                    setTexture(textload->getTexture("tower_3_8.png"), TOWER);
                    m_firerate = 650.0;
                    m_portee = 145;
                    m_damages = 4;
                    m_color = sf::Color(255, 255, 255);
                    break;
                case 9:
                    setTexture(textload->getTexture("tower_3_9.png"), TOWER);
                    m_firerate = 600.0;
                    m_portee = 150;
                    m_damages = 8;
                    m_color = sf::Color(255, 255, 255, 128);
                    break;
            }
            break;
        case 4:
            m_canon = 2;
            m_type_effect = m_effect::ice;
            switch (m_upgrade)
            {
                case 1:
                    setTexture(textload->getTexture("tower_4_1.png"), TOWER);
                    m_firerate = 50;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 30;
                    break;
                case 2:
                    setTexture(textload->getTexture("tower_4_2.png"), TOWER);
                    m_firerate = 40;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 30;
                    break;
                case 3:
                    setTexture(textload->getTexture("tower_4_3.png"), TOWER);
                    m_firerate = 30;
                    m_portee = 80;
                    m_damages = 2;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 30;
                    break;
                case 4:
                    setTexture(textload->getTexture("tower_4_4.png"), TOWER);
                    m_firerate = 20;
                    m_portee = 90;
                    m_damages = 3;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 30;
                    break;
                case 5:
                    setTexture(textload->getTexture("tower_4_5.png"), TOWER);
                    m_firerate = 0;
                    m_portee = 100;
                    m_damages = 3;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 30;
                    break;
                case 6:
                    setTexture(textload->getTexture("tower_4_6.png"), TOWER);
                    m_firerate = 30;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 25;
                    break;
                case 7:
                    setTexture(textload->getTexture("tower_4_7.png"), TOWER);
                    m_firerate = 25;
                    m_portee = 75;
                    m_damages = 0;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 20;
                    break;
                case 8:
                    setTexture(textload->getTexture("tower_4_8.png"), TOWER);
                    m_firerate = 25;
                    m_portee = 75;
                    m_damages = 1;
                    m_color = sf::Color(200, 200, 180, 180);
                    m_nb_ball = 15;
                    break;
                case 9:
                    setTexture(textload->getTexture("tower_4_9.png"), TOWER);
                    m_firerate = 5;
                    m_portee = 75;
                    m_damages = 2;
                    m_color = sf::Color(255, 255, 255, 200);
                    m_nb_ball = 5;
                    break;
            }
            break;
        default:
            break;
    }
    setRange(m_portee);
    setOrigin(40, 60);
}

int Tower::getEffect()
{
    return m_type_effect;
}

int Tower::getNbBall()
{
    if (m_type_effect == m_effect::ice)
        return m_nb_ball;
    else
        return 0;
}

std::string Tower::getPrice()
{
    return std::to_string(m_cost);
}

std::string Tower::getLeftUpgrade()
{
    if (m_upgrade == 1 || m_upgrade < 5)
    {
        return "tower_" + std::to_string(m_type) + "_" + std::to_string(m_upgrade + 1) + ".png";
    }
    return "";
}

std::string Tower::getRightUpgrade()
{
    if ((m_upgrade == 1) || (m_upgrade > 5 && m_upgrade < 9))
    {
        if (m_upgrade != 1)
        {
            return "tower_" + std::to_string(m_type) + "_" + std::to_string(m_upgrade + 1) + ".png";
        }
        else
        {
            return "tower_" + std::to_string(m_type) + "_6.png";
        }
    }
    return "";
}

int Tower::getLeftUpPrice(Textureloader* textload)
{
    if (m_upgrade < 6)
    {
        int cost(0);
        ++m_upgrade;
        cost = m_cost;
        getTowerPrice();
        cost = m_cost - cost;
        --m_upgrade;
        getTowerPrice();
        return cost;
    }
    return 0;
}

int Tower::getRightUpPrice(Textureloader* textload)
{
    int cost(0);
    if (m_upgrade > 5 && m_upgrade < 9)
    {
        cost = m_cost;
        ++m_upgrade;
        getTowerPrice();
        cost = m_cost - cost;
        --m_upgrade;
        getTowerPrice();
    }
    else if (m_upgrade == 1)
    {
        cost = m_cost;
        m_upgrade = 6;
        getTowerPrice();
        cost = m_cost - cost;
        m_upgrade = 1;
        getTowerPrice();
    }
    return cost;
}

void Tower::getTowerPrice()
{
    switch (m_type)
    {
        case 1:
            m_turrets = 3;
            switch (m_upgrade)
            {
                case 1:
                    m_cost = 10;
                    break;
                case 2:
                    m_cost += 15;
                    break;
                case 3:
                    m_cost += 20;
                    break;
                case 4:
                    m_cost += 15;
                    break;
                case 5:
                    m_cost += 15;
                    break;
                case 6:
                    m_cost += 15;
                    break;
                case 7:
                    m_cost += 15;
                    break;
                case 8:
                    m_cost += 15;
                    break;
                case 9:
                    m_cost += 15;
                    break;
                default:
                    break;
            }
            break;
        case 2:
            m_turrets = 3;
            switch (m_upgrade)
            {
                case 1:
                    m_cost = 20;
                    break;
                case 2:
                    m_cost += 15;
                    break;
                case 3:
                    m_cost += 15;
                    break;
                case 4:
                    m_cost += 15;
                    break;
                case 5:
                    m_cost += 15;
                    break;
                case 6:
                    m_cost += 15;
                    break;
                case 7:
                    m_cost += 15;
                    break;
                case 8:
                    m_cost += 15;
                    break;
                case 9:
                    m_cost += 15;
                    break;
                default:
                    break;
            }
            break;
        case 3:
            m_turrets = 2;
            switch (m_upgrade)
            {
                case 1:
                    m_cost = 30;
                    break;
                case 2:
                    m_cost += 15;
                    break;
                case 3:
                    m_cost += 15;
                    break;
                case 4:
                    m_cost += 15;
                    break;
                case 5:
                    m_cost += 15;
                    break;
                case 6:
                    m_cost += 15;
                    break;
                case 7:
                    m_cost += 15;
                    break;
                case 8:
                    m_cost += 15;
                    break;
                case 9:
                    m_cost += 15;
                    break;
            }
            break;
        case 4:
            m_canon = 2;
            switch (m_upgrade)
            {
                case 1:
                    m_cost = 60;
                    break;
                case 2:
                    m_cost += 15;
                    break;
                case 3:
                    m_cost += 175;
                    break;
                case 4:
                    m_cost += 450;
                    break;
                case 5:
                    m_cost += 1750;
                    break;
                case 6:
                    m_cost += 150;
                    break;
                case 7:
                    m_cost += 300;
                    break;
                case 8:
                    m_cost += 550;
                    break;
                case 9:
                    m_cost += 1500;
                    break;
            }
            break;
        default:
            break;
    }
}
