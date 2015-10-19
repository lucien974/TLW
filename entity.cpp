#include "entity.h"

Entity::Entity(): sf::Drawable(), m_range(0.f, std::size_t(30))
{
    m_range_aviable = false;
}

Entity::~Entity()
{
    m_sprite.clear();
    m_draw_status.clear();
}

void Entity::setTexture(sf::Texture& texture , std::string name)
{
	m_sprite[name].setTexture(texture);
	m_sprite[name].setOrigin(m_sprite[name].getGlobalBounds().height/2, m_sprite[name].getGlobalBounds().width/2);
	m_draw_status[name] = true;
	if(m_sprite.size() > 1)
    {
        m_sprite[name].setPosition(m_sprite.begin()->second.getPosition());
    }
}

void Entity::setOrigin(int a , int b)
{
    for(auto &ent1 : m_sprite)
    {
        ent1.second.setOrigin(a, b);
    }
}

float Entity::getRotation()
{
    return m_sprite.begin()->second.getRotation();
}

void Entity::setTexture(sf::Texture& texture , sf::Vector2f origin , std::string name)
{
    setTexture(texture , name);
    m_sprite[name].setOrigin(origin.x , origin.y);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if(m_range_aviable == true)
        target.draw(m_range);
    for(auto &ent1 : m_sprite)
    {
        //std::cout << ent1.first << std::endl;
        std::string a;
        if(ent1.first == ICE)
        {
            //std::cout << "Yes"  << std::endl;
            a = ent1.first;
        }
        if(m_draw_status.at(ent1.first) == true)
        {
            target.draw(ent1.second);
            /*
            if(ent1.first == BLOON)
            {
                std::cout << "No"  << std::endl;
            }
            //*/
        }
    }
}

bool Entity::isColliding(Entity *entity)
{
    m_sprite_it = m_sprite.begin();
    if(m_sprite_it->second.getGlobalBounds().contains(entity->m_sprite.begin()->second.getPosition()))
    {
        return true;
    }
	return false;
}

sf::Vector2f Entity::getPosition()
{
    return (m_sprite.begin()->second.getPosition());
}

bool Entity::isNearOf(Entity *entity, float radius) {
	const sf::Vector2f pos1 = m_sprite.begin()->second.getPosition();
	const sf::Vector2f pos2 = entity->m_sprite.begin()->second.getPosition();
	/*
	 * Équation d'un cercle r² = (x-a)² + (y-b)²
	 * Si (x-a)² + (y-b)² <= r², alors le point (a,b) est dans ou sur le cercle
	 * Sinon il est en dehors
	 */
	return (pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2)) <= pow(radius, 2);
}

bool Entity::isOutOfScreen(sf::RenderWindow* screen)
{
	if(m_sprite.begin()->second.getPosition().x > 0 &&
    m_sprite.begin()->second.getPosition().x < 900 &&

    m_sprite.begin()->second.getPosition().y > 0 &&
    m_sprite.begin()->second.getPosition().y < 600)
    {
        return false;
    }
    return true;
}

void Entity::setPosition(sf::Vector2f a)
{
    for(auto &ent1 : m_sprite)
    {
        ent1.second.setPosition(a);
    }
}

void Entity::setPosition(int x , int y)
{
    for(auto &ent1 : m_sprite)
    {
        ent1.second.setPosition(x,y);
    }
}

void Entity::rotateTowards(Entity *entity) {
	const sf::Vector2f pos1 = m_sprite.begin()->second.getPosition();
	const sf::Vector2f pos2 = entity->m_sprite.begin()->second.getPosition();

    float x, y, angle;

    x = pos2.x - pos1.x;
    y = pos2.y - pos1.y;

    angle = std::acos(y/std::sqrt(x*x + y*y))*(180.0f / 3.1415f) + 180.0f;
    if(x > 0)
    {
        angle*=-1;
    }
    /*
    for(int i(0) ; i < m_sprite.size() ; ++i)
    {
        m_sprite.begin()->second.setRotation(angle);
    }
    //*/
    for(auto &ent1 : m_sprite)
    {
        ent1.second.setRotation(angle);
    }
}

void Entity::spriteStatus(bool a , std::string name)
{
    m_sprite_it = m_sprite.find(name);
    if(m_sprite_it != m_sprite.end())
    {
        m_draw_status[name] = a;
        /*
        if(name == ICE)
        {
            m_sprite[BLOON].setColor(sf::Color(0 ,
                                     0 ,
                                     0 ,
                                     128));
        }
        //*/
    }
    else
    {
    }
}

bool Entity::getGlobalBounds(sf::Vector2i a)
{
    sf::FloatRect size = m_sprite.begin()->second.getGlobalBounds();
    if((a.x >= size.left /*+ position.x - origin.x*/ && a.x <= size.left + size.width /*+ position.x - origin.x*/) &&
        (a.y >= size.top /*+ position.y - origin.y*/ && a.y <= size.top + size.height /*+ position.y - origin.y*/))
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

int Entity::lastSprite()
{
    return m_sprite.size() - 1;
}

void Entity::drawRange(bool range)
{
    m_range_aviable = range;
    m_range.setPosition(m_sprite.begin()->second.getPosition());
}

int Entity::getRange()
{
    return (int)(m_range.getRadius());
}
