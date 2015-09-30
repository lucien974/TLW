#ifndef ENTITY_H
#define ENTITY_H

#include <sstream>
#include <iostream>
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

class Entity: public sf::Transformable, public sf::Drawable {

	public:
		Entity();
		virtual ~Entity();
		void setTexture(sf::Texture& texture);
		void setTexture(sf::Texture& texture , sf::Texture& texture_2);
		void setEffect(sf::Texture& texture , int effect);
		void disableEffect();
		void otherSpritesState(bool a);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		bool isColliding(Entity *entity);
		bool isNearOf(Entity *entity, float radius);
		bool isOutOfScreen(sf::RenderWindow* screen);
		void rotateTowards(Entity *entity);
		bool getGlobalBounds(sf::Vector2i a);
		void setRange(int range);
		void drawRange(bool range);
		int getRange();
		virtual void update() = 0;

	private:
		sf::Sprite m_sprite , m_sprite_2 , m_sprite_effect;
        bool m_twice , m_effect_aviable , m_range_aviable;
		enum m_effect{none = -1 , ice = 0 , burn = 1 , glue = 2 , reverse = 3};
		sf::CircleShape m_range;
};

#endif //ENTITY_H
