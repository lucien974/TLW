#include "entity.h"

Entity::Entity(): sf::Drawable() {
    m_twice = false;
    m_effect_aviable = false;
    m_range_aviable = false;
}

Entity::~Entity() {

}

void Entity::setTexture(sf::Texture& texture , sf::Texture& texture_2) {
	m_sprite = sf::Sprite(texture);
	sf::FloatRect size = m_sprite.getGlobalBounds();
	setOrigin(size.height/2, size.width/2);
    m_sprite_2 = sf::Sprite(texture_2);
    m_twice = true;
}

void Entity::setTexture(sf::Texture& texture) {
	m_sprite.setTexture(texture);
	sf::FloatRect size = m_sprite.getGlobalBounds();
	setOrigin(size.height/2, size.width/2);
	m_twice = false;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	if(m_range_aviable)
    {
        target.draw(m_range);
    }
	target.draw(m_sprite, states);
	if(m_twice)
    {
        target.draw(m_sprite_2 , states);
    }
    if(m_effect_aviable)
    {
        target.draw(m_sprite_effect , states);
    }
}

bool Entity::isColliding(Entity *entity)
{
	if(m_sprite.getGlobalBounds().contains(entity->getPosition()))
    {
		return true;
	}
	return false;
}

bool Entity::isNearOf(Entity *entity, float radius) {
	const sf::Vector2f pos1 = getPosition();
	const sf::Vector2f pos2 = entity->getPosition();
	/*
	 * Équation d'un cercle r² = (x-a)² + (y-b)²
	 * Si (x-a)² + (y-b)² <= r², alors le point (a,b) est dans ou sur le cercle
	 * Sinon il est en dehors
	 */
	return (pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2)) <= pow(radius, 2);
}

bool Entity::isOutOfScreen(sf::RenderWindow* screen)
{
	if(getPosition().x > 0 &&
    getPosition().x < 900 &&

    getPosition().y > 0 &&
    getPosition().y < 600)
    {
        return false;
    }
    return true;
}

void Entity::rotateTowards(Entity *entity) {
	const sf::Vector2f pos1 = getPosition();
	const sf::Vector2f pos2 = entity->getPosition();

    float x, y, angle;

    x = pos2.x - pos1.x;
    y = pos2.y - pos1.y;

    angle = acos(y/sqrt(x*x + y*y))*(180.0f / 3.1415f) + 180.0f;
    if(x > 0)
    {
        angle*=-1;
    }
    setRotation(angle);
}

void Entity::setEffect(sf::Texture& texture , int effect)
{
    if(effect > -1)
    {
        m_sprite_effect = sf::Sprite(texture);
        sf::FloatRect size = m_sprite.getGlobalBounds();
        setOrigin(size.height/2, size.width/2);
        m_effect_aviable = true;
    }
    else
        m_effect_aviable = false;
}

void Entity::disableEffect()
{
    m_effect_aviable = false;
}

void Entity::otherSpritesState(bool a)
{
    m_twice = a;
}

bool Entity::getGlobalBounds(sf::Vector2i a)
{
    sf::FloatRect size = m_sprite.getGlobalBounds();
    sf::Vector2f position = getPosition();
    sf::Vector2f origin = getOrigin();
    if((a.x >= size.left + position.x - origin.x && a.x <= size.width + position.x - origin.x) &&
        (a.y >= size.top + position.y - origin.y && a.y <= size.height + position.y - origin.y))
        return true;
    else
        return false;
}

void Entity::setRange(int range)
{
    m_range.setFillColor(sf::Color(0,0,255,128));
    m_range.setRadius(range);
    m_range.setOrigin(m_range.getGlobalBounds().width / 2 , m_range.getGlobalBounds().height / 2);
}

void Entity::drawRange(bool range)
{
    m_range_aviable = range;
    m_range.setPosition(getPosition());
}

int Entity::getRange()
{
    return (int)(m_range.getRadius());
}
