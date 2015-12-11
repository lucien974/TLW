#include "Menu.h"

Menu::Menu(Textureloader* textload, std::string font, int size, sf::Color color, sf::Color color_hovered) :
m_textload(textload),
m_color_normal(color),
m_color_hovered(color_hovered),
m_size(size),
m_font(font),
m_last_button(""),
m_select("")
{
}

Menu::~Menu()
{
    for (auto &key : m_buttons)
    {
        delete key.second;
    }
    m_buttons.clear();
}

std::string Menu::update(sf::RenderWindow* screen, char clic)
{
    m_select = "";
    if (m_background.getFillColor() != sf::Color(0, 0, 0))
        screen->draw(m_background);
    for (auto &key : m_buttons)
    {
        if (key.second->isInside(sf::Mouse::getPosition(*screen), clic))
            m_select = key.first;
        screen->draw(*key.second);
    }
    return m_select;
}

void Menu::setTitle(std::string sentence, sf::Vector2i position)
{
    m_buttons[TITLE] = new Button(m_textload, sentence, m_font, m_color_normal, m_color_normal, 2*m_size, position);
    m_last_button = TITLE;
}

void Menu::newButton(std::string type, sf::Vector2i gap)
{
    sf::Vector2i inter;
    inter.x = m_buttons[m_last_button]->getPosition().x;
    inter.y = m_buttons[m_last_button]->getPosition().y;
    m_buttons[type] = new Button(m_textload, type, m_font, m_color_normal, m_color_hovered, m_size, inter + gap);
    m_last_button = type;
}

void Menu::setShadows()
{
    for (auto &key : m_buttons)
    {
        if (key.first != TITLE)
            key.second->setShadows(sf::Vector2i(-3, -3));
    }
}

void Menu::setBackground(sf::Color color)
{
    m_background.setSize(sf::Vector2f(900, 800));
    m_background.setFillColor(color);
}

void Menu::onMouseClick(bool clic, std::string type)
{
    std::map<std::string, Button*>::iterator it;
    it = m_buttons.find(type);
    if (it != m_buttons.end())
        m_buttons[type]->onMouseClick(clic);
    else
    {
        std::stringstream error;
        error << "Button " << type << " not found";
        throw std::runtime_error(error.str());
    }
}
