#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>
#include <SFML/Graphics.hpp>

class Entity: public sf::Transformable, public sf::Drawable {

	public:
		Entity();
		virtual ~Entity();
		void setTexture(sf::Texture& texture);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		bool isColliding(Entity *entity);
		bool isNearOf(Entity *entity, int radius);
		bool isOutOfScreen();
		void rotateTowards(Entity *entity);
		virtual void update() = 0;

	private:
		sf::Sprite m_sprite;

};

#endif //ENTITY_H
