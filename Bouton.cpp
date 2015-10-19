#include "Bouton.h"

Bouton::Bouton()
{

}



Bouton::Bouton(sf::Font& font, std::string message, int char_size, sf::Color color, sf::Color color_change, sf::Vector2i position)
{
    m_text.setFont(font);
    m_text.setString(message);
    m_text.setCharacterSize(char_size);
    m_text.setColor(color);
    m_text.setOrigin((m_text.getLocalBounds().width / 2), (m_text.getLocalBounds().height /2));
    m_text.setPosition(position.x, position.y);
    m_color_change = color_change;
    m_color = color;
    m_deux = false;
    m_message = message;
    m_char_size = char_size;
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
    m_text.setFont(font);
    m_text.setString(message);
    m_text.setCharacterSize(char_size);
    m_text.setColor(color);
    m_text.setOrigin((m_text.getLocalBounds().width / 2), (m_text.getLocalBounds().height /2));
    m_text.setPosition(position.x, position.y);
    m_color_change = color_change;
    m_color = color;
    m_deux = false;
    m_message = message;
    m_char_size = char_size;
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



bool Bouton::inside(sf::Vector2i pos_ext, bool clic)
{
    if (m_text.getColor() != m_color)
        m_text.setColor(m_color);
    if (pos_ext.x <= m_text.getGlobalBounds().left + m_text.getGlobalBounds().width &&
       pos_ext.x >= m_text.getGlobalBounds().left &&
       pos_ext.y <= m_text.getGlobalBounds().top + m_text.getGlobalBounds().height &&
       pos_ext.y >= m_text.getGlobalBounds().top)
    {
        if (m_text.getColor() != m_color_change)
            m_text.setColor(m_color_change);
        if (clic)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}



bool Bouton::setup(sf::Vector2i pos_ext)
{
    if (pos_ext.x <= m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width &&
       pos_ext.x >= m_sprite.getGlobalBounds().left &&
       pos_ext.y <= m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height &&
       pos_ext.y >= m_sprite.getGlobalBounds().top)
    {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                return true;
            }
            else
            {
                return false;
            }
    }
    else
    {
        return false;
    }
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
        if (m_text.getColor() != m_color)
            m_text.setColor(m_color);
    if (status == false)
        if (m_text.getColor() != m_color_change)
            m_text.setColor(m_color_change);
}



void Bouton::setString(std::string a)
{
    m_text.setString(a);
    m_text_2.setString(a);
}



sf::Vector2f Bouton::getPos()
{
    return m_text.getPosition();
}
