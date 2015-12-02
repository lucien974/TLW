#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Include.h"

class Particle : public sf::Transformable, public sf::Drawable
{
    public:
        Particle();
        Particle(float mass, unsigned int limit, sf::Vector2f v0);
        ~Particle();
        void update(int number_of_generation, sf::RenderWindow &screen);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void normalize(std::string forceName);
        void rebound(sf::Vector2f direction);
        void setLimit(unsigned int limit);
        void setMass(float mass);
        void setForce(std::string name, sf::Vector2f f);
        void setInitialSpeed(sf::Vector2f v0);
        void setRandomForce(std::string name, sf::Vector2f f, float angle);

    private:
        std::deque<std::pair<sf::RectangleShape, std::pair<sf::Vector2f, unsigned int>>> m_particles;
        std::map<std::string, sf::Vector2f> m_forces;
        std::map<std::string, std::pair<float, std::pair<float, float>>> m_random_forces;
        sf::Vector2f m_v0;
        float m_mass;
        unsigned int m_limit, m_advance, m_follow_color;
};

#endif // CURSOR_H_INCLUDED
