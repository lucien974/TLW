#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

#include "Bloon.h"
#include "Tower.h"

class Wave// : public Bloon
{
    public:
        Wave(int nb_bloons , int type , int gap , int next_wave , string carte);
        ~Wave();
        int update(RenderWindow* ecran , Textureloader* textload);
        bool next();
        bool isEmpty();
        int size();
        int getBloonSpeed(int num_bloon);
        void destroyBloon(int num);
        Vector2f getBloonPosition(int num);
        bool isNearOf(int bloon_num , Vector2f tower_pos , float radius);
        int isWentOut(int n);
        int getMoney(int n);
        int getAdvance(int n);
        void isTouch(int n , Vector2f pos_ball , int damages , Textureloader* textload , int effect , int ice_limit);
    private:
        int m_gap , m_nb_bloons , m_cursor , m_type , m_way , m_damages;
        deque<Bloon*> m_bloon;
        string m_carte;
};

#endif // WAVE_H_INCLUDED
