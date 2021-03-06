#include "Particle.h"

Particle::Particle() :
Particle(1, 1, {0.0f, 0.0f})
{
}

Particle::Particle(float mass, unsigned int limit, sf::Vector2f v0) :
m_v0(v0),
m_mass(mass),
m_limit(limit),
m_advance(0),
m_follow_color(100)
{
}

Particle::~Particle()
{
}

void Particle::setForce(std::string name, sf::Vector2f f)
{
    m_forces[name] = f;
}

void Particle::normalize(std::string forceName)
{
    auto searchForces = m_forces.find(forceName);
    auto searchRandomForces = m_random_forces.find(forceName);

    if (searchForces != m_forces.end())
    {
        searchForces->second /= std::sqrt(std::pow(searchForces->second.x, 2.f) + std::pow(searchForces->second.y, 2.f));
    }
    else if (searchRandomForces != m_random_forces.end())
    {
        searchRandomForces->second.first = 1;
    }
    else
    {
        std::stringstream error;
        error << "Error force " << forceName << " not found";
        throw std::runtime_error(error.str());
    }
}

void Particle::setRandomForce(std::string name, sf::Vector2f f, float angle)
{
    float length = (sqrt(f.x*f.x + f.y*f.y));
    f.x /= length;
    f.y /= length;
    angle *= PI/180.0f;
    float a=std::acos(f.x)-angle, b=std::acos(f.x)+angle;
    while (a > 2*PI)
        a-=PI;
    while (a < 0)
        a+=2*PI;
    while (b > 2*PI)
        b-=PI;
    while (b < 0)
        b+=2*PI;
    m_random_forces[name] = std::make_pair(length, std::make_pair(a, b));
}

void Particle::setInitialSpeed(sf::Vector2f v0)
{
    m_v0 = v0;
}

void Particle::update(int number_of_generation, sf::RenderWindow &screen)
{
    sf::Vector2f vect(0.0, 0.0);
    sf::Vector2f rand_vect(0.0, 0.0);
    unsigned int j=0;
    while (j < m_particles.size())
    {
        if (m_particles[j].first.getPosition().x > 0 &&
           m_particles[j].first.getPosition().x < 900 &&
           m_particles[j].first.getPosition().y > 0 &&
           m_particles[j].first.getPosition().y < 600)
        {
            vect = (m_particles[j].second.first/m_mass) * static_cast<float>(m_particles[j].second.second) + m_v0;
            m_particles[j].first.move(vect);
            m_particles[j].second.second++;
            j++;
        }
        else
        {
            m_particles.erase(m_particles.begin() + j);
        }
    }
    vect = sf::Vector2f(0.0, 0.0);
    if (m_particles.size() < m_limit)
    {
        for (int i = 0; i < number_of_generation; ++i)
        {
            for (auto &key : m_forces)
            {
                vect += key.second;
            }
            for (auto &key : m_random_forces)
            {
                float angle=0.0;
                if (key.second.second.second > key.second.second.first)
                {
                    angle = (rand()/(float)RAND_MAX)*(key.second.second.second - key.second.second.first) + key.second.second.first;
                }
                if (key.second.second.second < key.second.second.first)
                    angle = (rand()/RAND_MAX)*(key.second.second.first - key.second.second.second) + key.second.second.second;
                while (angle >= 2*PI)
                    angle-=2*PI;
                rand_vect.x = std::cos(angle)*key.second.first;
                rand_vect.y = std::sin(angle)*key.second.first;
                vect += rand_vect;
            }
            m_particles.push_back(std::make_pair(sf::RectangleShape(sf::Vector2f(3, 3)), std::make_pair(vect, 0)));
            m_particles.back().first.setPosition(sf::Mouse::getPosition(screen).x, sf::Mouse::getPosition(screen).y);
            if (m_follow_color <= 255)
                m_particles.back().first.setFillColor(sf::Color(0, 0, m_follow_color));
            else if (m_follow_color <= 2*255)
                m_particles.back().first.setFillColor(sf::Color(0, m_follow_color-255, 255));
            else if (m_follow_color <= 3*255)
                m_particles.back().first.setFillColor(sf::Color(0, 255, 3*255 - m_follow_color));
            else if (m_follow_color <= 4*255)
                m_particles.back().first.setFillColor(sf::Color(m_follow_color - 3*255, 255, 0));
            else if (m_follow_color <= 5*255)
                m_particles.back().first.setFillColor(sf::Color(255, 5*255 - m_follow_color, 0));
            else if (m_follow_color <= 6*255)
                m_particles.back().first.setFillColor(sf::Color(255, 0, m_follow_color - 5*255));
            else if (m_follow_color <= 7*255)
                m_particles.back().first.setFillColor(sf::Color(255, m_follow_color - 6*255, 255));
            else if (m_follow_color <= 8*255)
                m_particles.back().first.setFillColor(sf::Color(255, 8*255 - m_follow_color, 255));
            else if (m_follow_color <= 9*255)
                m_particles.back().first.setFillColor(sf::Color(255, 0, 9*255 - m_follow_color));
            else if (m_follow_color <= 10*255)
                m_particles.back().first.setFillColor(sf::Color(255, m_follow_color - 9*255, 0));
            else if (m_follow_color <= 11*255)
                m_particles.back().first.setFillColor(sf::Color(11*255 - m_follow_color, 255, 0));
            else if (m_follow_color <= 12*255)
                m_particles.back().first.setFillColor(sf::Color(0, 255, m_follow_color - 11*255));
            else if (m_follow_color <= 13*255)
                m_particles.back().first.setFillColor(sf::Color(0, 13*255 - m_follow_color, 255));
            else if (m_follow_color <= 14*255 - 128)
                m_particles.back().first.setFillColor(sf::Color(0, 0, 14*255 - m_follow_color));
            else
            {
                m_follow_color=128;
                m_particles.back().first.setFillColor(sf::Color(0, 0, m_follow_color));
            }
            m_follow_color++;
        }
    }
    m_advance++;
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (auto &key : m_particles)
    {
        target.draw(key.first);
    }
}

void Particle::setMass(float mass)
{
    m_mass = mass;
}

void Particle::setLimit(unsigned int limit)
{
    m_limit = limit;
}
