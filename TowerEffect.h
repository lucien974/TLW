#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include <iostream>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "Include.h"

class TowerEffect
{
    public:
        TowerEffect(int effect);
        bool update(int &incrementation, sf::Vector2f &bullet_to_bloon, sf::Vector2f &bullet_forward, float tower_rotation);
        bool iceMove(int &incrementation, sf::Vector2f &bullet_to_bloon, sf::Vector2f &bullet_forward, float tower_rotation);
    private:
        int m_effect;
        enum m_tower_effect{none = -1, ice = 0, burn = 1, glue = 2, reverse = 3};
};

#endif // EFFECT_H_INCLUDED
