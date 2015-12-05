#include "Entity.h"

Entity::Entity() :
sf::Drawable(),
m_range_aviable(false)
{
}

Entity::~Entity()
{
    m_sprite.clear();
    m_draw_status.clear();
}

void Entity::setTexture(const sf::Texture& texture, std::string name)
{
    m_sprite[name].setTexture(texture);
    m_sprite[name].setOrigin(m_sprite[name].getGlobalBounds().width/2, m_sprite[name].getGlobalBounds().height/2);
    m_draw_status[name] = true;
    if (m_sprite.size() > 1)
    {
        m_sprite[name].setPosition(m_sprite.begin()->second.getPosition());
    }
}

void Entity::setOrigin(int a, int b)
{
    for (auto &ent1 : m_sprite)
    {
        ent1.second.setOrigin(a, b);
    }
}

float Entity::getRotation()
{
    return m_sprite.begin()->second.getRotation();
}

void Entity::setTexture(const sf::Texture& texture, sf::Vector2f origin, std::string name)
{
    setTexture(texture, name);
    m_sprite[name].setOrigin(origin.x, origin.y);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (m_range_aviable == true)
        target.draw(m_range);
    for (auto &ent1 : m_sprite)
    {
        if (m_draw_status.at(ent1.first) == true)
        {
            target.draw(ent1.second);
            /*
            if (ent1.first == BLOON)
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
    if (m_sprite_it->second.getGlobalBounds().contains(entity->m_sprite.begin()->second.getPosition()))
    {
        return true;
    }
    return false;
}

sf::Vector2f Entity::getPosition()
{
    return (m_sprite.begin()->second.getPosition());
}

bool Entity::isNearOf(Entity *entity, float radius)
{
    const sf::Vector2f pos1 = m_sprite.begin()->second.getPosition();
    const sf::Vector2f pos2 = entity->m_sprite.begin()->second.getPosition();
    /*
     * �quation d'un cercle r� = (x-a)� + (y-b)�
     * Si (x-a)� + (y-b)� <= r�, alors le point (a, b) est dans ou sur le cercle
     * Sinon il est en dehors
     */
    return (pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2)) <= pow(radius, 2);
}

bool Entity::isInRange(sf::Vector2f position, float radius)
{
    const sf::Vector2f pos1 = m_sprite.begin()->second.getPosition();
    /*
     * �quation d'un cercle r� = (x-a)� + (y-b)�
     * Si (x-a)� + (y-b)� <= r�, alors le point (a, b) est dans ou sur le cercle
     * Sinon il est en dehors
     */
    return (pow((position.x - pos1.x), 2) + pow((position.y - pos1.y), 2)) <= pow(radius, 2);
}

bool Entity::isOutOfScreen(sf::RenderWindow* screen)
{
    sf::Vector2u winSize = screen->getSize();
    if (m_sprite.begin()->second.getPosition().x > 0 &&
    m_sprite.begin()->second.getPosition().x < winSize.x &&

    m_sprite.begin()->second.getPosition().y > 0 &&
    m_sprite.begin()->second.getPosition().y < winSize.y)
    {
        return false;
    }
    return true;
}

void Entity::setPosition(sf::Vector2f a)
{
    for (auto &ent1 : m_sprite)
    {
        ent1.second.setPosition(a);
    }
}

void Entity::setPosition(int x, int y)
{
    for (auto &ent1 : m_sprite)
    {
        ent1.second.setPosition(x, y);
    }
}

void Entity::rotateTowards(Entity *entity)
{
    const sf::Vector2f pos1 = m_sprite.begin()->second.getPosition();
    const sf::Vector2f pos2 = entity->m_sprite.begin()->second.getPosition();

    float x, y, angle;

    x = pos2.x - pos1.x;
    y = pos2.y - pos1.y;

    angle = std::acos(y/std::sqrt(x*x + y*y))*(180.0f / 3.1415f) + 180.0f;
    if (x > 0)
    {
        angle*=-1;
    }
    for (auto &ent1 : m_sprite)
    {
        ent1.second.setRotation(angle);
    }
}

void Entity::rotateTowards(sf::Vector2f pos2)
{
    const sf::Vector2f pos1 = m_sprite.begin()->second.getPosition();

    float x, y, angle;

    x = pos2.x - pos1.x;
    y = pos2.y - pos1.y;

    angle = std::acos(y/std::sqrt(x*x + y*y))*(180.0f / 3.1415f) + 180.0f;
    if (x > 0)
    {
        angle*=-1;
    }
    for (auto &ent1 : m_sprite)
    {
        ent1.second.setRotation(angle);
    }
}

void Entity::spriteStatus(bool a, std::string name)
{
    m_sprite_it = m_sprite.find(name);
    if (m_sprite_it != m_sprite.end())
    {
        m_draw_status[name] = a;
        /*
        if (name == ICE)
        {
            m_sprite[BLOON].setColor(sf::Color(0,
                                     0,
                                     0,
                                     128));
        }
        //*/
    }
    else
    {
    }
}

sf::FloatRect Entity::getGlobalBounds()
{
    sf::FloatRect size = m_sprite.begin()->second.getGlobalBounds();
    return size;
}

void Entity::setRange(int range)
{
    m_range.setRadius(range);
    m_range.setFillColor(sf::Color(0, 128, 128, 128));
    m_range.setOutlineThickness(1.0);
    m_range.setOutlineColor(sf::Color(255, 255, 255, 128));
    m_range.setOrigin(m_range.getGlobalBounds().width / 2, m_range.getGlobalBounds().height / 2);
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
    return static_cast<int>(m_range.getRadius());
}

void Entity::move(float x, float y)
{
    for (auto &key : m_sprite)
    {
        key.second.move(x, y);
        if (key.first == TOWER)
            m_range.move(x, y);
    }
}
