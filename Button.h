#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Textureloader.h"


class Button : public Transformable, public Drawable
{
    public:
        Button();
        Button(Textureloader* textload);
        Button(Textureloader *textload , string sentence , string font , Color color , Color hovered_color , int char_size , Vector2i position);
        //virtual ~Button();
        ~Button();
        void draw(RenderTarget &target, RenderStates states) const;
        bool isInside(Vector2i pos_ext);
        void onMouseClick(bool clic); /// in default m_clic = true;
        void setShadows(Vector2i gap);
        void setSentence(string sentence);
        void setTextureloader(Textureloader* textload);
        void setHoveredColor(Color color);
        void setColor(Color color);
        void setFont(string font);
        void setCharacterSize(int char_size);
        void setPosition(Vector2f position);
        void onCondition(bool condition);
        Vector2i getPosition();
        FloatRect getGlobalBounds();
		//virtual void update() = 0;
    private:
        Textureloader *m_textload;
        Text m_button_normal , m_button_shadows;
        Color m_color_normal , m_color_hovered;
        bool m_shadows , m_clic;
};

#endif // BOUTON_H_INCLUDED
