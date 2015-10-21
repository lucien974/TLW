#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED

#include "Bloon.h"

class Bouton
{
    public:
        Bouton();
        Bouton(sf::Font& font, std::string message, int char_size, sf::Color color, sf::Color color_change, sf::Vector2i position);
        Bouton(sf::Texture& texture, sf::Vector2f pos);
        ~Bouton();
        void set(sf::Font& font, std::string message, int char_size, sf::Color color, sf::Color color_change, sf::Vector2i position);
        void set(sf::Font& font, std::string message, int char_size, sf::Color color, sf::Vector2i position);
        bool isInside(sf::Vector2i pos_ext, bool clic);
        bool setup(sf::Vector2i pos_ext);
        void affiche(sf::RenderWindow* screen);
        void doubleBouton(sf::Font& font, int ecart_x, int ecart_y, sf::Color color);
        void move(int x, int y);
        void setColor(sf::Color color, sf::Color color_change);
        void changeColor(bool status);
        void setString(std::string a);
        sf::Vector2f getPos() const;

    private:
        sf::Text m_text, m_text_2;
        sf::Color m_color, m_color_change;
        sf::Sprite m_sprite;
        std::string m_message;
        int m_char_size;
        bool m_deux;
};

#endif // BOUTON_H_INCLUDED
