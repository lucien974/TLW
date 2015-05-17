#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include <deque>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include "entity.h"
#include "Textureloader.h"

class Tower : public Entity
{
  public:
      Tower(int type , Textureloader* textload , int cost);
      int Fire();
      virtual ~Tower();
      void update();
      void Range(sf::RenderWindow* screen);
      int Getrange();
      int Sell();
  private:
      sf::Texture m_texture;
      sf::Sprite m_tower;
      sf::Clock m_clock;
      sf::Time m_time;
      sf::CircleShape m_range;
      bool m_shoot;
      float m_angle , m_tir, m_firerate;
      int m_portee , m_cost;
};

#endif // TOWER_H_INCLUDED
