#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED

#include "bloon.h"

class Bouton
{
    public:
        Bouton( sf::Font& font , std::string message , int char_size , sf::Color color , sf::Color color_change , sf::Vector2i position );
        ~Bouton();
        bool Inside(sf::Vector2i pos_ext , bool clic);
        void Affiche(sf::RenderWindow* screen);
        void Doublebutton( sf::Font& font , int ecart_x , int ecart_y , sf::Color color );
        void Move( int x , int y );
        void Setcolor(sf::Color color , sf::Color color_change);
        sf::Vector2f Getpos();
    private:
        sf::Text m_text , m_text_2;
        sf::Color m_color , m_color_change;
        std::string m_message;
        int m_char_size;
        bool m_deux;
};

#endif // BOUTON_H_INCLUDED
