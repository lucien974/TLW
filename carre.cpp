#include "carre.h"

Carre::Carre(Point p1 , int distance)
{
    m_posx.push_back( p1.Retx() );
    m_posy.push_back( p1.Rety() );
    m_posx.push_back( p1.Retx() + distance );
    m_posy.push_back( p1.Rety() + distance );
}

int Carre::Ret1()
{
    return m_posx.at(0);
}

int Carre::Ret2()
{
    return m_posy.at(0);
}

int Carre::Ret3()
{
    return m_posx.at(1);
}

int Carre::Ret4()
{
    return m_posy.at(1);
}
