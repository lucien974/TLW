#include "Interface.h"
#include "Level.h"
#include "Textureloader.h"

/// Fait : Le JEU
/// à Faire : Amelioration : Carte virtuel en ref

int main (int argc, char** argv)
{
    sf::RenderWindow *window;
    window = new sf::RenderWindow(sf::VideoMode(900, 600, 32), "Tower Defense", sf::Style::Titlebar | sf::Style::Close);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    Textureloader* textload;
    textload = new Textureloader("images/", "sons/", "polices/");

    Interface *menu;
    menu = new Interface(textload);

    Level niv(textload);
    niv.event(window, textload);

    return 0;
}
