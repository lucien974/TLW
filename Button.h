#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Textureloader.h"


class Button : public sf::Transformable, public sf::Drawable
{
    public:
        Button();
        Button(Textureloader* textload);
        Button(Textureloader *textload , string sentence , string font , sf::Color color , sf::Color hovered_color , int char_size , sf::Vector2i position);
        ~Button();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        bool isInside(sf::Vector2i pos_ext);
        void onMouseClick(bool clic); /// in default m_clic = true;
        void setShadows(sf::Vector2i gap);
        void setSentence(string sentence);
        void setTextureloader(Textureloader* textload);
        void setHoveredColor(sf::Color color);
        void setColor(sf::Color color);
        void setFont(string font);
        void setCharacterSize(int char_size);
        void setPosition(sf::Vector2f position);
        void onCondition(bool condition);
        sf::Vector2i getPosition();
        sf::FloatRect getGlobalBounds();
    private:
        Textureloader *m_textload;
        sf::Text m_button_normal , m_button_shadows;
        sf::Color m_color_normal , m_color_hovered;
        bool m_shadows , m_clic;
};

#endif // BOUTON_H_INCLUDED
