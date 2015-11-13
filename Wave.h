#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

#include "Bloon.h"
#include "Tower.h"

class Wave
{
    public:
        Wave(int nb_bloons, int type, int gap, int next_wave, string carte);
        ~Wave();
        int update(sf::RenderWindow* ecran, Textureloader* textload);
        bool next();
        bool isEmpty();
        int size();
        int getBloonSpeed(int num_bloon);
        void destroyBloon(int num);
        sf::Vector2f getBloonPosition(int num);
        bool isNearOf(int bloon_num, sf::Vector2f tower_pos, float radius);
        int isWentOut(int n);
        int getMoney(int n);
        int getAdvance(int n);
        void isTouch(int n, sf::Vector2f pos_ball, int damages, Textureloader* textload, int effect, int ice_limit);
    private:
        int m_gap, m_nb_bloons, m_cursor, m_type, m_way;
        deque<Bloon*> m_bloon;
        string m_carte;
};

#endif // WAVE_H_INCLUDED
