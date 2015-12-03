#include "Game.h"

Game::Game() :
m_level_name(""),
m_level_num(1),
m_number_levels(1),
m_menu(true),
m_clic(0)
{
    m_file.open("levels/game.txt", std::ios::in);
    m_file >> m_level_name;

    m_textload = new Textureloader("images/", "sons/", "polices/");
    m_textload->getTexture("heart.png");
    m_textload->getTexture("ice_bloon.png");
    for (int i = 1; i < 12; ++i)
    {
        m_textload->getTexture("bloon_" + std::to_string(i) + ".png");
    }
    for (int i(1); i < 6; ++i)
    {
        m_textload->getTexture("bloon_shield_" + std::to_string(i) + ".png");
    }

    m_background.setTexture(m_textload->getTexture("fond.png"));

    m_textload->setTextureFolder("images/" + m_level_name + "/");

    m_screen = new sf::RenderWindow(sf::VideoMode(900, 600, 32), "BALLONS WAR");
    m_screen->setFramerateLimit(60);
    m_screen->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - 450, sf::VideoMode::getDesktopMode().height/2 - 300));

    m_level = new Level(m_textload, m_screen, "levels/" + m_level_name + "/lvl_" + std::to_string(m_level_num) + ".txt");

    m_start = new Menu(m_textload, "abaddon", 50, sf::Color::Green, sf::Color::Black);
    m_start->setTitle("BALLONS\n  WAR", sf::Vector2i(450, 150));
    m_start->newButton(PLAY, sf::Vector2i(0, 200));
    m_start->newButton(EXIT, sf::Vector2i(0, 100));
    m_start->onMouseClick(true, PLAY);

    m_mouse = new Particle(10.0, 100, sf::Vector2f(0.0, -3.0));
    m_mouse->setForce("P", sf::Vector2f(0.0, 1.01));
    m_mouse->setRandomForce("Fireworks", sf::Vector2f(1.0, -20.0), 30);

    m_screen->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - 450, sf::VideoMode::getDesktopMode().height/2 - 300));
}

Game::~Game()
{
    m_file.close();
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
    if (!m_file)
    {
        m_screen->close();
        std::cout << "Game file don't found" << std::endl;
    }
    while (m_screen->isOpen())
    {
        while (m_screen->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::LostFocus:
                    m_clic = 0;
                    break;
                default:
                    break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_clic == 1)
        {
            m_clic = 2;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true && m_clic == 0)
        {
            m_clic = 1;
        }

        if (m_menu)
        {
            std::string a;
            m_screen->draw(m_background);
            a = m_start->update(m_screen, m_clic);
            if (m_clic == 2)
                m_clic = 0;
            m_mouse->update(gen, *m_screen);
            m_screen->draw(*m_mouse);
            if (a == PLAY)
                m_menu = false;
            if (a == EXIT)
                m_screen->close();
            m_screen->display();
            m_screen->clear();
            gen = 3;
        }
        else
        {
            m_level->run(m_screen, m_textload);
            if (m_number_levels < NB_LEVELS && m_level->isDone() == false)
            {
                ++m_level_num;
                ++m_number_levels;
                if (m_file.eof() == false)
                {
                    std::string b;
                    m_file >> b;
                    if (b != m_level_name)
                    {
                        m_level_name = b;
                        m_level_num = 1;
                        m_textload->setTextureFolder("images/" + m_level_name + "/");
                        m_textload->clearLevel();
                    }
                    m_level->changeLevel("levels/" + m_level_name + "/lvl_" + std::to_string(m_level_num) + ".txt");
                }
                else
                {
                    std::cout << "File error not enough levels (" << m_number_levels << " instead of " << NB_LEVELS << ")" << std::endl;
                    m_screen->close();
                }
            }
            else
            {
                if (m_level->isDone() == false)
                {
                    m_level->forceRunning(m_screen, m_textload);
                }
                else
                {
                    m_level->close();
                    m_screen->close();
                }
            }
        }
    }
}
