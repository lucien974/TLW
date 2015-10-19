#include "Vague.h"

Vague::Vague(int type, std::string carte)
{
    m_inter = 0;
    m_nbbloon = 0;
    m_cursor = 0;
    m_read = true;
    m_nbvague = 0;
    m_type = type;
    m_way = 0;
    m_already = false;
    m_damages = 0;
    m_carte = carte;
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
    if (m_read == true)
    {
        m_read = false;
        m_cursor = inter;
    }
    m_nbbloon = nbbloon;
    m_inter = inter;
    if (m_cursor == m_inter && m_nbvague <= m_nbbloon)
    {
        m_bloon.push_back(new Bloon(m_type, textload, m_carte));
        m_cursor = 0;
        m_nbvague++;
    }
    m_way++;
    m_cursor++;
    unsigned int k(0);
    while (k < m_bloon.size())
    {
        m_bloon[k]->update(textload);
        if (m_bloon[k]->getHealth() > 0)
        {
            ecran->draw(*m_bloon[k]);
        }
        m_damages += m_bloon[k]->getDamages();
        if (m_bloon[k]->exit() == true)
        {
            m_sound.push_back(NULL);
            m_sound.back() = new sf::Sound(textload->getBuffer("pop.ogg"));
            (m_sound.back())->play();
            delete m_bloon.at(k);
            m_bloon.erase(m_bloon.begin() + k);
        }
        k++;
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



bool Vague::next(int distance)
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



bool Vague::size()
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



int Vague::getSize()
{
    return m_bloon.size();
}



int Vague::getBloonSpeed(int num_bloon)
{
    return getBloon(num_bloon)->getSpeed();
}
