#include "Menu.h"

Menu::Menu(Textureloader* textload , string font , int size , Color color , Color color_hovered)
{
    m_textload = textload;
    m_font = font;
    m_size = size;
    m_color_normal = color;
    m_color_hovered = color_hovered;
    m_select = m_last_button = "";
}

Menu::~Menu()
{
    for(auto &key : m_buttons)
    {
        delete key.second;
    }
    m_buttons.clear();
}

string Menu::update(sf::RenderWindow* screen)
{
    m_select = "";
    screen->draw(m_background);
    for(auto &key : m_buttons)
    {
        if(key.second->isInside(Mouse::getPosition(*screen)))
            m_select = key.first;
        screen->draw(*key.second);
    }
    return m_select;
}

void Menu::setTitle(string sentence , Vector2i position)
{
    m_buttons[TITLE] = new Button(m_textload , sentence , m_font , m_color_normal , m_color_normal , 2*m_size , position);
    m_last_button = TITLE;
}

void Menu::newButton(string type , Vector2i gap)
{
    Vector2i inter;
    inter.x = m_buttons[m_last_button]->getPosition().x;
    inter.y = m_buttons[m_last_button]->getPosition().y;
    m_buttons[type] = new Button(m_textload , type , m_font , m_color_normal , m_color_hovered , m_size , inter + gap);
    m_last_button = type;
}

void Menu::setBackground(Color color)
{
    m_background.setSize(Vector2f(900,800));
    m_background.setFillColor(color);
}

void Menu::onMouseClick(bool clic , string type)
{
    map<string , Button*>::iterator it;
    it = m_buttons.find(type);
    if(it != m_buttons.end())
        m_buttons[type]->onMouseClick(clic);
}
