#ifndef CARRE_H_INCLUDED
#define CARRE_H_INCLUDED

#include "Point.h"

class Carre
{
    public:
        Carre(Point p1, int distance);
        int ret1();
        int ret2();
        int ret3();
        int ret4();

    private:
        std::deque<int> m_posx;
        std::deque<int> m_posy;
};

#endif // CARRE_H_INCLUDED
