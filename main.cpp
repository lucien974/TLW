#include "Menu.h"
#include "Level.h"
#include "Textureloader.h"

/// Fait : Le JEU
/// à Faire : Amelioration : Carte virtuel en ref

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
    window = new sf::RenderWindow(sf::VideoMode(900,600 , 32) , "TOWER DEFENSE" , sf::Style::Titlebar | sf::Style::Close, settings);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    Textureloader* textload;
    textload = new Textureloader("images/" , "sons/" , "polices/");

    //Interface *menu;
    //menu = new Interface(textload);

    Level niv(textload , window);
    //sf::Thread thread(&Level::physicsMotor , &niv);
    /*
    if(menu->Boucle(window , textload))
    {

    }
    else
    {
        niv.Event(window , textload);
    }
    //*/
    niv.event(window , textload);
    delete textload;
    return 0;
}
