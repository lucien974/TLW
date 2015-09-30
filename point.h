#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <deque>
#include <cstdlib>

using namespace sf;

class Point
{
public:
    Point(int x , int y);
    int Retx();
    int Rety();
private:
    int m_x , m_y;
};

#endif // POINT_H_INCLUDED
