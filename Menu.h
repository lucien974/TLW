#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <string>
#include <map>

#include "Button.h"
#include "Include.h"

class Menu
{
    public:
        Menu(Textureloader* textload, std::string font, int size, sf::Color color, sf::Color color_hovered);
        ~Menu();
        std::string update(sf::RenderWindow* screen, char clic);
        void setTitle(std::string sentence, sf::Vector2i position);
        void newButton(std::string type, sf::Vector2i gap);
        void setBackground(sf::Color color);
        void onMouseClick(bool clic, std::string type);
        void setShadows();

    private:
        std::map<std::string, Button*> m_buttons;
        sf::RectangleShape m_background;
        Textureloader *m_textload;
        sf::Color m_color_normal, m_color_hovered;
        int m_size;
        std::string m_font, m_last_button, m_select;
};

#endif // MENU_H_INCLUDED
