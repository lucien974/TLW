#include "Game.h"

Game::Game()
{
    std::locale::global(std::locale("en_US.utf8"));
	std::wcout.imbue(std::locale());

    m_textload = new Textureloader("images/" , "sons/" , "polices/");

    m_background.setTexture(m_textload->getTexture("fond.png"));

    m_screen = new sf::RenderWindow(sf::VideoMode(900,600 , 32) , "TOWER DEFENSE");

    m_level = new Level(m_textload , m_screen);

    m_start = new Menu(m_textload , "abaddon" , 50 , sf::Color::Green , sf::Color::Black);
    m_start->setTitle("BALLONS\n  WAR" , sf::Vector2i(450 , 150));
    m_start->newButton(PLAY , sf::Vector2i(0,200));
    m_start->newButton(EXIT , sf::Vector2i(0,100));
    m_start->onMouseClick(true , PLAY);

    m_menu = true;
}

Game::~Game()
{
    delete m_start;
    delete m_level;
    delete m_textload;
    delete m_screen;
}

void Game::update()
{
    while(m_screen->isOpen())
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_clic == 1)
        {
            m_clic = 2;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true && m_clic == 0)
        {
            m_clic = 1;
        }

        if(m_menu)
        {
            string a;
            m_screen->draw(m_background);
            a = m_start->update(m_screen , m_clic);
            if(a == PLAY)
                m_menu = false;
            if(a == EXIT)
                m_screen->close();
            m_screen->display();
            m_screen->clear();
            sf::sleep(sf::milliseconds(30));
            m_screen->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - 450 , sf::VideoMode::getDesktopMode().height/2 - 300));
        }
        else
        {
            m_level->event(m_screen , m_textload);
            m_screen->close();
        }
    }
}
