#include "Menu.h"
#include "Level.h"
#include "Textureloader.h"

/// Fait : le PLAY
/// à Faire : moins de ballons ;)

int main ( int argc, char** argv )
{
    /**/
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::RenderWindow *window;
    window = new sf::RenderWindow(sf::VideoMode(900,600 , 32) , "THE LAST WAR" , sf::Style::Titlebar | sf::Style::Close, settings);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    Textureloader* textload;
    textload = new Textureloader("images/" , "sons/" , "polices/");

    Interface *menu;
    menu = new Interface(textload);

    sf::Image image;
    image.loadFromFile("images/virtual_grass_1.png");
    Level niv(image , textload);
    if(menu->Boucle(window , textload))
    {

    }
    else
    {
        niv.Event(window , textload);
    }

    return EXIT_SUCCESS;
}
