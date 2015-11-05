#ifndef MULTITOUR_H_INCLUDED
#define MULTITOUR_H_INCLUDED

#include "Tower.h"
#include "Button.h"

class Multitower
{
    public:
        Multitower(Textureloader* textload);
        ~Multitower();
        int update(Image carte , RenderWindow* screen , Textureloader* textload , int money , bool sup , bool clic_up);
        int getSize();
        bool getStatus();
        Vector2f getPosition(int num);
        float getRange(int n);
        void rotateTowards(int n , Vector2f bloon);
        int shoot(int n , Vector2f bloon);
        int getEffect(int n);
        int getNbBall(int n);
    private:
        deque<Tower*> m_tower , m_selection;
        deque<Button> m_cost_sprite;
        int m_select , m_tower_selected;
        Sprite m_up[2];
        Button *m_up_price[2] , *m_money;
};


#endif // MULTITOUR_H_INCLUDED
