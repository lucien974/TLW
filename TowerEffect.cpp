#include "TowerEffect.h"

TowerEffect::TowerEffect(int effect)
: m_effect(effect)
{}

bool TowerEffect::update(int &incrementation, sf::Vector2f &bullet_to_bloon, sf::Vector2f &bullet_forward, float tower_rotation)
{
    switch (m_effect)
    {
        case m_tower_effect::none:
            if ((bullet_to_bloon.x*bullet_forward.x + bullet_to_bloon.y*bullet_forward.y) <= 0)
                return false;
            else
                return true;
            break;
        case m_tower_effect::ice:
            return iceMove(incrementation, bullet_to_bloon, bullet_forward, tower_rotation);
            break;
        default:
            throw std::runtime_error("Unknown effect");
            break;
    }
}

bool TowerEffect::iceMove(int &incrementation, sf::Vector2f &bullet_to_bloon, sf::Vector2f &bullet_forward, float tower_rotation)
{
    incrementation++;
    float a, radian;
    if (incrementation < 150)
    {
        a = sqrt(bullet_to_bloon.x*bullet_to_bloon.x + bullet_to_bloon.y*bullet_to_bloon.y)/5;
    }
    if (incrementation < 20)
    {
        bullet_forward.x = a*std::sin(tower_rotation*(3.1415f / 180.0f));
        bullet_forward.y = -a*std::cos(tower_rotation*(3.1415f / 180.0f));
    }
    else if (incrementation >= 20 && incrementation < 90)
    {
        radian = rand()*0.5f;
        bullet_forward.x = a*std::sin((tower_rotation + radian)*(3.1415f / 180.0f));
        bullet_forward.y = -a*std::cos((tower_rotation + radian)*(3.1415f / 180.0f));
    }
    else if (incrementation >= 90 && incrementation <= 150)
    {
        bullet_forward.x = rand()%5 - 2;
        bullet_forward.y = rand()%5 - 2;
    }
    else if (incrementation > 150)
    {
        return false;
    }
    return true;
}
