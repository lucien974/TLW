#include "Vague.h"

Vague::Vague(sf::Image carte_v , int type)
{
    m_inter = 0;
    m_nbbloon = 0;
    m_cursor = 0;
    m_carte = carte_v;
    m_read = true;
    m_nbvague = 0;
    m_type = type;
    m_way = 0;
    m_already = false;
    m_damages = 0;
}

int Vague::Move(sf::RenderWindow* ecran , int nbbloon , int inter , Textureloader* textload)
{
    m_damages = 0;
    if(m_read == true)
    {
        m_read = false;
        m_cursor = inter;
    }
    m_nbbloon = nbbloon;
    m_inter = inter;
    if( m_cursor == m_inter && m_nbvague < m_nbbloon )
    {
        m_bloon.push_back(new Bloon(m_carte , m_type , textload));
        m_cursor = 0;
        m_nbvague++;
    }
    m_way++;
    m_cursor++;
    int k(0);
    while( k < m_bloon.size() )
    {
        m_bloon[k]->update();
        ecran->draw(*m_bloon[k]);
        m_damages += m_bloon[k]->Getdamages();
        if( m_bloon[k]->Exit() == true )
        {
            m_sound.push_back(new sf::Sound(textload->Getbuffer("pop.ogg")));
            (m_sound.back())->play();
            std::cout << "pop play" << std::endl;
            delete m_bloon.at(k);
            m_bloon.erase(m_bloon.begin() + k);
        }
        k++;
        for(int c(0) ; c < m_sound.size() ; ++c)
        {
            std::cout << "size sound : " << m_sound.size() << std::endl;
            if(m_sound[c]->getStatus() == m_sound[c]->Stopped)
            {
                std::cout << "pop" << c << " stopped" << std::endl;
                delete m_sound[c];
                m_sound.erase(m_sound.begin() + c);
            }
        }
    }
    return m_damages;
}

bool Vague::Next(int distance)
{
    if(m_way == distance)
        return true;
    else
        return false;
}

int Vague::Size()
{
    if(m_bloon.size() == 0 && m_nbvague >= m_nbbloon)
        return true;
    else
        return false;
}

Vague::~Vague()
{
    m_sound.clear();
    for( int n(0) ; n < m_bloon.size() ; ++n )
    {
        delete m_bloon.front();
        m_bloon.pop_front();
    }
    for(int ty(0) ; ty < m_sound.size() ; ++ty)
    {
        std::cout << "sound" << ty << " deleted" << std::endl;
        delete m_sound[ty];
        m_sound.erase(m_sound.begin() + ty);
    }
}

Bloon* Vague::Getbloon(int a)
{
    return m_bloon.at(a);
}

int Vague::Getsize()
{
    return m_bloon.size();
}

int Vague::Getbloonspeed(int num_bloon)
{
    return Getbloon(num_bloon)->Getspeed();
}
