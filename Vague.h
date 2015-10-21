#ifndef VAGUE_H_INCLUDED
#define VAGUE_H_INCLUDED

#include "Bloon.h"
#include "Tower.h"

class Vague
{
    public:
        Vague(int type, std::string carte);
        ~Vague();
        int move(sf::RenderWindow* ecran, int nbbloon, int inter, Textureloader* textload);
        bool next(int distance) const;
        bool size() const;
        Bloon* getBloon(int a);
        int getSize() const;
        int getBloonSpeed(int num_bloon) const;

    private:
        int m_inter, m_nbbloon, m_cursor, m_nbvague, m_type, m_way, m_damages;
        std::deque<Bloon*> m_bloon;
        bool m_read, m_already;
        std::deque<sf::Sound*> m_sound;
        std::string m_carte;
};

#endif // VAGUE_H_INCLUDED
