#ifndef VAGUE_H_INCLUDED
#define VAGUE_H_INCLUDED

#include "bloon.h"
#include "Tower.h"

class Vague// : public Bloon
{
public:
    Vague(sf::Image carte_v , int type);
    ~Vague();
    int Move(sf::RenderWindow* ecran , int nbbloon , int inter , Textureloader* textload);
    bool Next(int distance);
    int Size();
    Bloon* Getbloon(int a);
    int Getsize();
    int Getbloonspeed(int num_bloon);
private:
    int m_inter , m_nbbloon , m_cursor , m_nbvague , m_type , m_way , m_damages;
    std::deque<Bloon*> m_bloon;
    std::deque<Tower*> m_tower;
    sf::Image m_carte;
    bool m_read , m_already;
    std::deque<sf::Sound*> m_sound;
};

#endif // VAGUE_H_INCLUDED
