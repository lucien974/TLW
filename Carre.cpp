#include "Carre.h"

Carre::Carre(Point p1, int distance)
{
    m_posx.push_back(p1.Retx());
    m_posy.push_back(p1.Rety());
    m_posx.push_back(p1.Retx() + distance);
    m_posy.push_back(p1.Rety() + distance);
}



int Carre::ret1()
{
    return m_posx.at(0);
}



int Carre::ret2()
{
    return m_posy.at(0);
}



int Carre::ret3()
{
    return m_posx.at(1);
}



int Carre::ret4()
{
    return m_posy.at(1);
}
