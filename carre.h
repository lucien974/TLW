#ifndef CARRE_H_INCLUDED
#define CARRE_H_INCLUDED

#include "point.h"

class Carre
{
public:
    Carre(Point p1 , int distance);
    int Ret1();
    int Ret2();
    int Ret3();
    int Ret4();
private:
    std::deque<int> m_posx;
    std::deque<int> m_posy;

};

#endif // CARRE_H_INCLUDED
