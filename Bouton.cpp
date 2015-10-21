#include "Bouton.h"

Bouton::Bouton()
{

}



Bouton::Bouton(sf::Font& font, std::string message, int char_size, sf::Color color, sf::Color color_change, sf::Vector2i position)
{
    set(font, message, char_size, color, color_change, position);
}



Bouton::Bouton(sf::Texture& texture, sf::Vector2f pos)
{
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
    m_sprite.setPosition(pos);
}



Bouton::~Bouton()
{
}



void Bouton::set(sf::Font& font, std::string message, int char_size, sf::Color color, sf::Color color_change, sf::Vector2i position)
{
    set(font, message, char_size, color, position);
    m_color_change = color_change;
}



void Bouton::set(sf::Font& font, std::string message, int char_size, sf::Color color, sf::Vector2i position)
{
    m_text.setFont(font);
    m_text.setString(message);
    m_text.setCharacterSize(char_size);
    m_text.setColor(color);
    m_text.setOrigin((m_text.getLocalBounds().width / 2), (m_text.getLocalBounds().height /2));
    m_text.setPosition(position.x, position.y);
    m_color = color;
    m_deux = false;
    m_message = message;
    m_char_size = char_size;
}



bool Bouton::isInside(sf::Vector2i pos_ext, bool clic)
{
    if (m_text.getColor() != m_color)
    {
        m_text.setColor(m_color);
    }

    sf::FloatRect textBounds = m_text.getGlobalBounds();
    if (pos_ext.x <= textBounds.left + textBounds.width &&
       pos_ext.x >= textBounds.left &&
       pos_ext.y <= textBounds.top + textBounds.height &&
       pos_ext.y >= textBounds.top)
    {
        if (m_text.getColor() != m_color_change)
        {
            m_text.setColor(m_color_change);
        }
        if (clic)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}



bool Bouton::setup(sf::Vector2i pos_ext)
{
    sf::FloatRect spriteBounds = m_sprite.getGlobalBounds();
    if (pos_ext.x <= spriteBounds.left + spriteBounds.width &&
       pos_ext.x >= spriteBounds.left &&
       pos_ext.y <= spriteBounds.top + spriteBounds.height &&
       pos_ext.y >= spriteBounds.top)
    {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                return true;
            }
            return false;
    }
    return false;
}



void Bouton::affiche(sf::RenderWindow* screen)
{
    if (m_deux)
    {
        screen->draw(m_text_2);
    }
    screen->draw(m_text);
}



void Bouton::doubleBouton(sf::Font& font, int ecart_x, int ecart_y, sf::Color color)
{
    m_text_2.setFont(font);
    m_text_2.setString(m_message);
    m_text_2.setCharacterSize(m_char_size);
    m_text_2.setColor(color);
    m_text_2.setOrigin((m_text_2.getLocalBounds().width / 2), (m_text_2.getLocalBounds().height /2));
    m_text_2.setPosition(m_text.getPosition().x + ecart_x, m_text.getPosition().y + ecart_y);
    m_deux = true;
}



void Bouton::move(int x, int y)
{
    m_text.move(x, y);
    if (m_deux)
        m_text_2.move(x, y);
}



void Bouton::setColor(sf::Color color, sf::Color color_change)
{
    m_color_change = color_change;
    m_color = color;
}



void Bouton::changeColor(bool status)
{
    if (status == true)
    {
        if (m_text.getColor() != m_color)
            m_text.setColor(m_color);
    }
    else
    {
        if (m_text.getColor() != m_color_change)
            m_text.setColor(m_color_change);
    }
}



void Bouton::setString(std::string a)
{
    m_text.setString(a);
    m_text_2.setString(a);
}



sf::Vector2f Bouton::getPos() const
{
    return m_text.getPosition();
}
