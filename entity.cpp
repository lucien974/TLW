#include "entity.h"

Entity::Entity(): sf::Drawable() {

}

Entity::~Entity() {

}

void Entity::setTexture(sf::Texture& texture) {
	m_sprite = sf::Sprite(texture);
	sf::FloatRect size = m_sprite.getGlobalBounds();
	setOrigin(size.height/2, size.width/2);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}

bool Entity::isColliding(Entity *entity) {
	const sf::Vector2f pos1 = getPosition();
	const sf::Vector2f pos2 = entity->getPosition();
	if(pos2.x >= pos1.x && pos2.x <= pos1.x && pos2.y >= pos1.y && pos2.y <= pos1.x) {
		return true;
	}
	return false;
}

bool Entity::isNearOf(Entity *entity, int radius) {
	const sf::Vector2f pos1 = getPosition();
	const sf::Vector2f pos2 = entity->getPosition();
	/*
	 * Équation d'un cercle r² = (x-a)² + (y-b)²
	 * Si (x-a)² + (y-b)² <= r², alors le point (a,b) est dans ou sur le cercle
	 * Sinon il est en dehors
	 */
	return (pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2)) <= pow(radius, 2);
}

bool Entity::isOutOfScreen() {
	return false;
	//TODO
}

void Entity::rotateTowards(Entity *entity) {
	const sf::Vector2f pos1 = getPosition();
	const sf::Vector2f pos2 = entity->getPosition();

    float x, y, angle;

    x = pos2.x - pos1.x;
    y = pos2.y - pos1.y;

    angle = acos(y/sqrt(x*x + y*y))*(180.0f / 3.1415);
    if(x > 0)
    {
        angle*=-1;
        angle += 180.0;
    }
    else
        angle+=180.0;
    setRotation(angle);
}
