#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Button.h"

class Menu
{
    public:
        Menu(Textureloader* textload , string font , int size , Color color , Color color_hovered);
        ~Menu();
        string update(sf::RenderWindow* screen);
        void setTitle(string sentence , Vector2i position);
        void newButton(string type , Vector2i gap);
        void setBackground(Color color);
        void onMouseClick(bool clic , string type);

    private:
        map<string , Button*> m_buttons;
        sf::RectangleShape m_background;
        Textureloader *m_textload;
        Color m_color_normal , m_color_hovered;
        int m_size;
        string m_font , m_last_button , m_select;
};

#endif // MENU_H_INCLUDED
