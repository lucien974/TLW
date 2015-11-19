#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "Include.h"

class Entity: public sf::Transformable, public sf::Drawable
{
    public:
        Entity();
        virtual ~Entity();
        void setTexture(sf::Texture& texture, std::string name);
        void setPosition(sf::Vector2f a);
        void setPosition(int x, int y);
        void setTexture(sf::Texture& texture, sf::Vector2f origin, std::string name);
        void disableEffect();
        void spriteStatus(bool a, std::string name);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        bool isColliding(Entity *entity);
        bool isNearOf(Entity *entity, float radius);
        bool isInRange(sf::Vector2f position, float radius);
        bool isOutOfScreen(sf::RenderWindow* screen);
        void rotateTowards(Entity *entity);
        sf::FloatRect getGlobalBounds();
        void setRange(int range);
        void drawRange(bool range);
        void setOrigin(int a, int b);
        float getRotation();
        sf::Vector2f getPosition();
        int lastSprite();
        int getRange();
        void rotateTowards(sf::Vector2f pos2);
        virtual void update() = 0;

    protected:
        enum m_effect{none = -1, ice = 0, burn = 1, glue = 2, reverse = 3};

    private:
        std::map<std::string, sf::Sprite> m_sprite;
        std::map<std::string, sf::Sprite>::iterator m_sprite_it;
        std::map<std::string, bool> m_draw_status;
        std::map<std::string, bool>::iterator m_draw_status_it;
        bool m_range_aviable;
        sf::CircleShape m_range;
};

#endif //ENTITY_H_INCLUDED
