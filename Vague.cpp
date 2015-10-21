#include "Vague.h"

Vague::Vague(int type, std::string carte) :
m_inter(0),
m_nbbloon(0),
m_cursor(0),
m_nbvague(0),
m_type(type),
m_way(0),
m_damages(0),
m_read(true),
m_already(false),
m_carte(carte)
{
}



Vague::~Vague()
{
    for (unsigned int n(0); n < m_bloon.size(); ++n)
    {
        delete m_bloon.front();
        m_bloon.pop_front();
    }
    for (unsigned int ty(0); ty < m_sound.size(); ++ty)
    {
        while (m_sound[ty]->getStatus() == sf::Sound::Playing)
            ;
        delete m_sound.back();
        m_sound.pop_back();
    }
}



int Vague::move(sf::RenderWindow* ecran, int nbbloon, int inter, Textureloader* textload)
{
    m_damages = 0;
    m_nbbloon = nbbloon;
    m_inter = inter;
    if (m_read == true)
    {
        m_read = false;
        m_cursor = inter;
    }

    if (m_cursor == m_inter && m_nbvague <= m_nbbloon)
    {
        m_bloon.push_back(new Bloon(m_type, textload, m_carte));
        m_cursor = 0;
        m_nbvague++;
    }

    m_way++;
    m_cursor++;
    for(unsigned int k(0); k < m_bloon.size(); ++k)
    {
        m_bloon[k]->update(textload);
        if (m_bloon[k]->getHealth() > 0)
        {
            ecran->draw(*m_bloon[k]);
        }
        m_damages += m_bloon[k]->getDamages();
        if (m_bloon[k]->isWentOut() == true)
        {
            m_sound.push_back(NULL);
            m_sound.back() = new sf::Sound(textload->getBuffer("pop.ogg"));
            (m_sound.back())->play();
            delete m_bloon.at(k);
            m_bloon.erase(m_bloon.begin() + k);
        }
        for (unsigned int c(0); c < m_sound.size(); ++c)
        {
            if (m_sound[c]->getStatus() == sf::Sound::Stopped)
            {
                delete m_sound[c];
                m_sound.erase(m_sound.begin() + c);
            }
        }
    }
    return m_damages;
}



bool Vague::next(int distance) const
{
    if (m_way == distance)
    {
        return true;
    }
    else
    {
        return false;
    }
}



bool Vague::size() const
{
    if (m_bloon.size() == 0 && m_nbvague >= m_nbbloon)
    {
        return true;
    }
    else
    {
        return false;
    }
}



Bloon* Vague::getBloon(int a)
{
    return m_bloon.at(a);
}



int Vague::getSize() const
{
    return m_bloon.size();
}



int Vague::getBloonSpeed(int num_bloon) const
{
    return m_bloon[num_bloon]->getSpeed();
}
