#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <map>
#include <cmath>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define BLOON "bloon"
#define SHIELD "shield"
#define TOWER "tower"
#define ICE "ice"
#define GLUE "glue"
#define ALL "all"

namespace Effect {
    enum Effect {None = -1, Ice = 0, Burn = 1, Glue = 2, Reverse = 3};
}

class Entity: public sf::Transformable, public sf::Drawable
{
    public:
        Entity();
        virtual ~Entity();
        void setTexture(sf::Texture& texture, std::string name);
        void setPosition(sf::Vector2f a);
        void setPosition(int x, int y);
        void setTexture(sf::Texture& texture, sf::Vector2f origin, std::string name);
        void spriteStatus(bool a, std::string name);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void drawRange(bool range);
        bool isColliding(Entity *entity);
        bool isNearOf(Entity *entity, float radius);
        bool isOutOfScreen(sf::RenderWindow* screen) const;
        void rotateTowards(Entity *entity);
        bool getGlobalBounds(sf::Vector2i a) const;
        void setOrigin(int a, int b);
        int getRange() const;
        void setRange(int range);
        float getRotation() const;
        sf::Vector2f getPosition() const;
        int getLastSprite() const;
        virtual void update() = 0;

    private:
        std::map<std::string, sf::Sprite> m_sprite;
        std::map<std::string, sf::Sprite>::iterator m_sprite_it;
        std::map<std::string, bool> m_draw_status;
        std::map<std::string, bool>::iterator m_draw_status_it;
        bool m_range_aviable;
        sf::CircleShape m_range;
};

#endif //ENTITY_H
