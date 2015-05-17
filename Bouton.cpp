#include "Bouton.h"

Bouton::Bouton(sf::Font& font , std::string message , int char_size , sf::Color color , sf::Color color_change , sf::Vector2i position)
{
    m_text.setFont(font);
    m_text.setString(message);
    m_text.setCharacterSize(char_size);
    m_text.setColor(color);
    m_text.setOrigin((m_text.getLocalBounds().width / 2) , (m_text.getLocalBounds().height /2));
    m_text.setPosition(position.x,position.y);
    m_color_change = color_change;
    m_color = color;
    m_deux = false;
    m_message = message;
    m_char_size = char_size;
}

Bouton::~Bouton()
{

}

bool Bouton::Inside(sf::Vector2i pos_ext , bool clic)
{
    m_text.setColor(m_color);
    if(pos_ext.x <= m_text.getGlobalBounds().left + m_text.getGlobalBounds().width &&
       pos_ext.x >= m_text.getGlobalBounds().left &&
       pos_ext.y <= m_text.getGlobalBounds().top + m_text.getGlobalBounds().height &&
       pos_ext.y >= m_text.getGlobalBounds().top )
    {
        m_text.setColor(m_color_change);
        if(clic)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

void Bouton::Affiche(sf::RenderWindow* screen)
{
    if(m_deux)
    {
        screen->draw(m_text_2);
    }
    screen->draw(m_text);
}

void Bouton::Doublebutton( sf::Font& font , int ecart_x , int ecart_y , sf::Color color )
{
    m_text_2.setFont(font);
    m_text_2.setString(m_message);
    m_text_2.setCharacterSize(m_char_size);
    m_text_2.setColor(color);
    m_text_2.setOrigin((m_text_2.getLocalBounds().width / 2) , (m_text_2.getLocalBounds().height /2));
    m_text_2.setPosition( m_text.getPosition().x + ecart_x , m_text.getPosition().y + ecart_y );
    m_deux = true;
}

void Bouton::Move(int x , int y)
{
    m_text.move(x,y);
    if(m_deux)
        m_text_2.move(x,y);
}

void Bouton::Setcolor(sf::Color color , sf::Color color_change)
{
    m_color_change = color_change;
    m_color = color;
}

sf::Vector2f Bouton::Getpos()
{
    return m_text.getPosition();
}
