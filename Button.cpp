#include "Button.h"

Button::Button()
{
    m_textload = NULL;
    m_color_hovered = Color(0,0,0);
    m_color_normal = Color(0,0,0);
    m_shadows = false;
    m_clic = true;
}

Button::Button(Textureloader *textload)
{
    m_textload = textload;
    m_color_hovered = Color(0,0,0);
    m_color_normal = Color(0,0,0);
    m_shadows = false;
    m_clic = true;
}

Button::Button(Textureloader *textload , string sentence , string font , Color color , Color hovered_color , int char_size , Vector2i position)
{
    m_textload = textload;

    m_button_normal.setString(sentence);
    m_button_normal.setFont(m_textload->getFont(font + ".ttf"));
    m_button_normal.setCharacterSize(char_size);
    m_button_normal.setOrigin(m_button_normal.getGlobalBounds().width/2 , m_button_normal.getGlobalBounds().height/2);
    m_button_normal.setPosition(position.x , position.y);
    m_button_normal.setColor(color);

    m_button_shadows.setString(sentence);
    m_button_shadows.setFont(m_textload->getFont(font + ".ttf"));
    m_button_shadows.setCharacterSize(char_size);
    m_button_shadows.setOrigin(m_button_shadows.getGlobalBounds().width/2 , m_button_shadows.getGlobalBounds().height/2);
    m_button_shadows.setPosition(position.x , position.y);
    m_button_shadows.setColor(Color::Black);

    m_color_normal = color;
    m_color_hovered = hovered_color;
    m_shadows = false;
    m_clic = true;
}

Button::~Button()
{
}

void Button::draw(RenderTarget &target, RenderStates states) const
{
    states.transform *= getTransform();
    if(m_shadows)
        target.draw(m_button_shadows);
    target.draw(m_button_normal);
}

bool Button::isInside(Vector2i pos_ext)
{
    if(m_button_normal.getGlobalBounds().contains(pos_ext.x , pos_ext.y))
    {
        if(m_button_normal.getColor() == m_color_normal)
            m_button_normal.setColor(m_color_hovered);
        if(m_clic)
        {
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                return true;
            }
            else
                return false;
        }
        else
            return true;
    }
    else
    {
        if(m_button_normal.getColor() == m_color_hovered)
            m_button_normal.setColor(m_color_normal);
        return false;
    }
}

void Button::onMouseClick(bool clic)
{
    m_clic = m_clic;
}

void Button::setShadows(Vector2i gap)
{
    m_shadows = true;
    m_button_shadows.move(gap.x , gap.y);
}

void Button::setSentence(string sentence)
{
    m_button_normal.setString(sentence);
    m_button_shadows.setString(sentence);
}

void Button::setTextureloader(Textureloader* textload)
{
    m_textload = textload;
}

void Button::setHoveredColor(Color color)
{
    m_color_hovered = color;
}

void Button::setColor(Color color)
{
    m_button_normal.setColor(color);
}

void Button::setFont(string font)
{
    m_button_normal.setFont(m_textload->getFont(font));
    m_button_shadows.setFont(m_textload->getFont(font));
}

void Button::setCharacterSize(int char_size)
{
    m_button_normal.setCharacterSize(char_size);
    m_button_shadows.setCharacterSize(char_size);
}

void Button::setPosition(Vector2f position)
{
    m_button_shadows.move(position - m_button_normal.getPosition());
    m_button_normal.move(position - m_button_normal.getPosition());
}

void Button::onCondition(bool condition)
{
    if(condition)
    {
        if(m_button_normal.getColor() == m_color_normal)
            m_button_normal.setColor(m_color_hovered);
    }
    else
    {
        if(m_button_normal.getColor() == m_color_hovered)
            m_button_normal.setColor(m_color_normal);
    }
}

Vector2i Button::getPosition()
{
    return Vector2i(m_button_normal.getPosition().x , m_button_normal.getPosition().y);
}

FloatRect Button::getGlobalBounds()
{
    return m_button_normal.getGlobalBounds();
}
