#include "Game.h"

Game::Game() :
m_menu(true),
m_clic(0)
{
    m_textload = new Textureloader("images/", "sons/", "polices/");

    m_background.setTexture(m_textload->getTexture("fond.png"));

    m_screen = new sf::RenderWindow(sf::VideoMode(900, 600, 32), "TOWER DEFENSE");

    m_level = new Level(m_textload, m_screen);

    m_start = new Menu(m_textload, "abaddon", 50, sf::Color::Green, sf::Color::Black);
    m_start->setTitle("BALLONS\n  WAR", sf::Vector2i(450, 150));
    m_start->newButton(PLAY, sf::Vector2i(0, 200));
    m_start->newButton(EXIT, sf::Vector2i(0, 100));
    m_start->onMouseClick(true, PLAY);

    m_mouse = new Particle(10.0, 100, sf::Vector2f(0.0, -3.0));
    m_mouse->setForce("P", sf::Vector2f(0.0, 1.01));
    m_mouse->setRandomForce("Fireworks", sf::Vector2f(1.0, -20.0), 30);
}

Game::~Game()
{
    delete m_start;
    delete m_level;
    delete m_textload;
    delete m_screen;
    delete m_mouse;
}

void Game::update()
{
    sf::Event event;
    int gen = 3;
    while (m_screen->isOpen())
    {
        while (m_screen->pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
                gen = 3;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_clic == 1)
        {
            m_clic = 2;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true && m_clic == 0)
        {
            m_clic = 1;
        }

        if (m_menu)
        {
            string a;
            m_screen->draw(m_background);
            a = m_start->update(m_screen, m_clic);
            m_mouse->update(gen, *m_screen);
            m_screen->draw(*m_mouse);
            if (a == PLAY)
                m_menu = false;
            if (a == EXIT)
                m_screen->close();
            m_screen->display();
            m_screen->clear();
            sf::sleep(sf::milliseconds(30));
            m_screen->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - 450, sf::VideoMode::getDesktopMode().height/2 - 300));

            gen = 3;
        }
        else
        {
            m_level->event(m_screen, m_textload);
            m_screen->close();
        }
    }
}
