#include "Button.h"

Button::Button() :
Button(nullptr)
{
}

Button::Button(Textureloader *textload) :
Button(textload, {}, {}, {0, 0, 0}, {0, 0, 0}, 0, {0, 0})
{
}

Button::Button(Textureloader *textload, std::string sentence, std::string font, sf::Color color, sf::Color hovered_color, int char_size, sf::Vector2i position) :
m_textload(textload),
m_color_normal(color),
m_color_hovered(hovered_color),
m_gap(sf::Vector2f(0, 0)),
m_shadows(false),
m_clic(true)
{
    if (!font.empty())
    {
        m_button_normal.setString(sentence);
        m_button_normal.setFont(m_textload->getFont(font + ".ttf"));
        m_button_normal.setCharacterSize(char_size);
        m_button_normal.setOrigin(m_button_normal.getGlobalBounds().width/2, m_button_normal.getGlobalBounds().height/2);
        m_button_normal.setPosition(position.x, position.y);
        m_button_normal.setColor(color);

        m_button_shadows.setString(sentence);
        m_button_shadows.setFont(m_textload->getFont(font + ".ttf"));
        m_button_shadows.setCharacterSize(char_size);
        m_button_shadows.setOrigin(m_button_shadows.getGlobalBounds().width/2, m_button_shadows.getGlobalBounds().height/2);
        m_button_shadows.setPosition(position.x, position.y);
        m_button_shadows.setColor(sf::Color::Black);
    }
}

Button::~Button()
{
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (m_shadows)
        target.draw(m_button_shadows);
    target.draw(m_button_normal);
}

bool Button::isInside(sf::Vector2i pos_ext, char clic)
{
    if (m_button_normal.getGlobalBounds().contains(pos_ext.x, pos_ext.y))
    {
        if (m_button_normal.getColor() == m_color_normal)
            m_button_normal.setColor(m_color_hovered);
        if (m_clic)
        {
            if (clic == 2)
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
        if (m_button_normal.getColor() == m_color_hovered)
            m_button_normal.setColor(m_color_normal);
        return false;
    }
}

void Button::onMouseClick(bool clic)
{
    m_clic = clic;
}

void Button::setShadows(sf::Vector2i gap)
{
    m_shadows = true;
    m_button_shadows.move(gap.x, gap.y);
}

void Button::setSentence(std::string sentence)
{
    m_button_normal.setString(sentence);
    m_button_shadows.setString(sentence);
}

void Button::setTextureloader(Textureloader* textload)
{
    m_textload = textload;
}

void Button::setHoveredColor(sf::Color color)
{
    m_color_hovered = color;
}

void Button::setColor(sf::Color color)
{
    m_button_normal.setColor(color);
}

void Button::setFont(std::string font)
{
    m_button_normal.setFont(m_textload->getFont(font));
    m_button_shadows.setFont(m_textload->getFont(font));
}

void Button::setCharacterSize(int char_size)
{
    m_button_normal.setCharacterSize(char_size);
    m_button_shadows.setCharacterSize(char_size);
}

void Button::setPosition(sf::Vector2f position)
{
    m_button_shadows.move(position - m_button_normal.getPosition());
    m_button_normal.move(position - m_button_normal.getPosition());
}

void Button::onCondition(bool condition)
{
    if (condition)
    {
        if (m_button_normal.getColor() == m_color_normal)
            m_button_normal.setColor(m_color_hovered);
    }
    else
    {
        if (m_button_normal.getColor() == m_color_hovered)
            m_button_normal.setColor(m_color_normal);
    }
}

sf::Vector2i Button::getPosition()
{
    return sf::Vector2i(m_button_normal.getPosition().x, m_button_normal.getPosition().y);
}

sf::FloatRect Button::getGlobalBounds()
{
    return m_button_normal.getGlobalBounds();
}

void Button::move(float x, float y)
{
    m_button_normal.move(x, y);
    m_button_shadows.move(x, y);
}

void Button::setOrigin(sf::Vector2f origin)
{
    m_button_normal.setOrigin(origin);
    m_button_shadows.setOrigin(origin);
}

void Button::setOrigin(float x, float y)
{
    m_button_normal.setOrigin(x, y);
    m_button_shadows.setOrigin(x, y);
}

sf::FloatRect Button::getLocalBounds()
{
    sf::FloatRect local;
    local = m_button_normal.getLocalBounds();
    if (m_shadows)
    {
        local.width += m_gap.x;
        local.height += m_gap.y;
    }
    return local;
}

float Button::getCharacterSize()
{
    return m_button_normal.getCharacterSize();
}
