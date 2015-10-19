#ifndef ENTITY_H
#define ENTITY_H

#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <deque>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>
#include <time.h>
#include <cmath>
#include <deque>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstddef>

#define BLOON "bloon"
#define SHIELD "shield"
#define TOWER "tower"
#define ICE "ice"
#define GLUE "glue"
#define ALL "all"

class Entity: public sf::Transformable, public sf::Drawable {

	public:
		Entity();
		virtual ~Entity();
		void setTexture(sf::Texture& texture , std::string name);
		void setPosition(sf::Vector2f a);
		void setPosition(int x , int y);
		void setTexture(sf::Texture& texture , sf::Vector2f origin , std::string name);
		void disableEffect();
		void spriteStatus(bool a , std::string name);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		bool isColliding(Entity *entity);
		bool isNearOf(Entity *entity, float radius);
		bool isOutOfScreen(sf::RenderWindow* screen) const;
		void rotateTowards(Entity *entity);
		bool getGlobalBounds(sf::Vector2i a);
		void setRange(int range);
		void drawRange(bool range);
		void setOrigin(int a , int b);
		float getRotation();
		sf::Vector2f getPosition();
		int lastSprite();
		int getRange();
		virtual void update() = 0;

	private:
		std::map<std::string , sf::Sprite> m_sprite;
		std::map<std::string , sf::Sprite>::iterator m_sprite_it;
        std::map<std::string , bool> m_draw_status;
        std::map<std::string , bool>::iterator m_draw_status_it;
        bool m_range_aviable;
		sf::CircleShape m_range;
    protected:
        enum m_effect{none = -1 , ice = 0 , burn = 1 , glue = 2 , reverse = 3};
};

#endif //ENTITY_H
