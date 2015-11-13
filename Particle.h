#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include "Include.h"

#define PI 3.141592

using namespace std;

class Particle : public sf::Transformable, public sf::Drawable
{
    public:
        Particle();
        Particle(float mass, unsigned int limit, sf::Vector2f v0);
        ~Particle();
        void update(int number_of_generation, sf::RenderWindow &screen);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void normalise(string a);
        void rebound(sf::Vector2f direction);
        void setLimit(unsigned int limit);
        void setMass(float mass);
        void setForce(string name, sf::Vector2f f);
        void setInitialSpeed(sf::Vector2f v0);
        void setRandomForce(string name, sf::Vector2f f, float angle);
    private:
        deque<pair<sf::RectangleShape, pair<sf::Vector2f, unsigned int>>> m_particles;
        map<string, sf::Vector2f> m_forces;
        map<string, pair<float, pair<float, float>>> m_random_forces;
        sf::Vector2f m_v0;
        float m_mass;
        unsigned int m_limit, m_advance, m_follow_color;
};

#endif // CURSOR_H_INCLUDED
