#include "Level.h"

Level::Level(Textureloader* textload)
{
    m_mouse = 0;
    m_click = false;
    m_pause_bool = false;
    m_wave = 0;
    m_pass_save = false;
    m_bool_pause = false;
    m_fichier = fopen("levels/lvl_1.txt", "r");
    m_frontinter = 0;
    m_type = 0;
    m_pass = true;
    m_passinter = false;
    m_play = 0;
    m_pause = 0;
    m_end = false;
    m_done = false;
    m_one_time = true;
    m_sprite.setTexture(textload->getTexture("grass_1.png"));
    m_sprite.scale(1.5f, 1.5f);

    m_money = 500;

    m_tower = new Multitower(textload);
    m_text_pause = new Bouton(textload->getFont("abaddon.ttf"), "PAUSE" ,
                               50, sf::Color::Green, sf::Color::Green, sf::Vector2i(450, 50));
    m_text_loose = new Bouton(textload->getFont("abaddon.ttf"), "YOU LOOSE" ,
                               100, sf::Color::Red, sf::Color::Red, sf::Vector2i(450, 150));
    m_restart = new Bouton(textload->getFont("abaddon.ttf"), "RESTART" ,
                               25, sf::Color::Red, sf::Color::Black, sf::Vector2i(450, 300));
    m_resume = new Bouton(textload->getFont("abaddon.ttf"), "RESUME" ,
                               25, sf::Color::Green, sf::Color::Red, sf::Vector2i(450, 200));
    m_text_exit = new Bouton(textload->getFont("abaddon.ttf"), "EXIT" ,
                               25, sf::Color::Green, sf::Color::Red, sf::Vector2i(450, 250));
    m_text_win = new Bouton(textload->getFont("abaddon.ttf"), "YOU WIN" ,
                               100, sf::Color::Yellow, sf::Color::Yellow, sf::Vector2i(450, 150));
    m_text_save = new Bouton(textload->getFont("abaddon.ttf"), "SAVE" ,
                               100, sf::Color::Yellow, sf::Color::White, sf::Vector2i(450, 350));
    m_life.set(textload->getFont("nb.ttf"), "", 20, sf::Color::Red, sf::Vector2i(750, 550));
    m_life.doubleBouton(textload->getFont("nb.ttf"), -3, -3, sf::Color::Black);
    m_tower_bar.setTexture(textload->getTexture("tower_bar_1.png"));
    m_tower_bar.setPosition(0, 0);
    m_bouton.setTexture(textload->getTexture("play.png"));
    m_bouton.setOrigin(25, 25);
    m_bouton.setPosition(25, 330);
    m_bp = false;
    m_first_pass = true;
    m_play_save = 0;
    m_inter_vague = 0;
    m_seek = 0;
    m_win = false;
    m_lives = 200;
    m_loose.setTexture(textload->getTexture("fond.png"));
    m_loose.setOrigin(402, 300);
    m_loose.setPosition(400, 300);
    fseek(m_fichier, 0, SEEK_END);
    m_size = ftell(m_fichier);
    fseek(m_fichier, 0, SEEK_SET);
    m_sup = false;
    m_delete = false;
    m_save = fopen("save/save.txt", "w");
    m_music.openFromFile("sons/sound_1.ogg");
    m_music.setLoop(true);
    m_music.play();
}



Level::~Level()
{
    fclose(m_fichier);
    fclose(m_save);
    unsigned int f(0);
    while (f < m_level.size())
    {
        delete m_level.at(f);
        m_level.erase(m_level.begin());
        f=0;
    }
    delete m_tower;
    delete m_text_exit;
    delete m_text_win;
    delete m_text_pause;
    delete m_text_loose;
    delete m_restart;
    delete m_resume;
    delete m_text_save;
}



void Level::launch(sf::RenderWindow *ecran, Textureloader* textload)
{
    if (m_pass == true)
    {
        m_play = 0;
        if (m_seek == m_size)
            m_play = 1;
        while (m_play != 1)
        {
            m_nbbloon.push_back(0);
            m_inter.push_back(0);
            fscanf(m_fichier, "%d %d %d %d %d", &m_nbbloon.back(), &m_inter.back(), &m_type, &m_frontinter, &m_play);
            if (m_frontinter == -1)
            {
                m_end = true;
            }
            else
            {
                m_inter_vague = m_frontinter;
            }
            m_interlevel.push_back(m_frontinter);
            m_level.push_back(new Vague(m_type, "virtual_grass_1.png"));
            m_level.back()->move(ecran, m_nbbloon.back(), m_inter.back(), textload);
        }
        m_seek = ftell(m_fichier);
        m_wave++;
        std::cout << "vague " << m_wave << std::endl;
        m_play_save = 1;
        m_pass = false;
    }
    if (m_win == false)
    {
        if (m_lives > 0)
        {
            if (m_play == 0)
            {
                m_end = false;
                unsigned int k(0);
                if (m_level.size() == 0)
                {
                    m_pass = true;
                    m_interlevel.clear();
                }
                while (k < m_level.size())
                {
                    if (k < m_play_save)
                    {
                        m_lives -= m_level[k]->move(ecran, m_nbbloon[k], m_inter[k], textload);
                    }
                    if (m_level[k]->next(m_interlevel[k]))
                    {
                        m_play_save++;
                        if (m_play_save >= m_level.size())
                            m_play_save = m_level.size();
                            std::cout << m_interlevel[k] << "pxls crossed" << std::endl;
                        m_interlevel[k] = -1;
                    }
                    if (m_level[k]->size() == true && m_interlevel[k] == -1)
                    {
                        delete m_level.at(k);
                        m_level.erase(m_level.begin() + k);
                        m_nbbloon.erase(m_nbbloon.begin() + k);
                        m_inter.erase(m_inter.begin() + k);
                        m_play_save--;
                        if (m_seek == m_size && m_level.size() == 0)
                        {
                            m_win = true;
                        }
                        else
                        {
                            m_win = false;
                        }
                    }
                    k++;
                }
                int inter[2];
                inter[0] = 0;
                for (int v(m_tower->getSize() - 1); v >= 0; --v)
                {
                    for (int n(m_level.size() - 1); n >= 0; --n)
                    {
                        for (int g(0); g < m_level[n]->getSize(); ++g)
                        {
                            if (m_level[n]->getBloon(g)->isOutOfScreen(ecran) == false)
                            {
                                if (m_level[n]->getBloon(g)->isNearOf(m_tower->getTower(v), m_tower->getTower(v)->getRange()) == true)
                                {
                                    if (m_level[n]->getBloon(g)->getIncrementation() > inter[0])
                                    {
                                        inter[0] = m_level[n]->getBloon(g)->getIncrementation();
                                        inter[1] = g;
                                        m_tri = n;
                                        m_first_pass = true;
                                    }
                                }
                            }
                        }
                    }
                    if (m_first_pass && inter[0] != 0)
                    {
                        m_tower->getTower(v)->rotateTowards(m_level[m_tri]->getBloon(inter[1]));
                        m_level[m_tri]->getBloon(inter[1])->touch(m_level[m_tri]->getBloon(inter[1])->getPosition() ,
                                                                    m_tower->getTower(v)->fire(m_level[m_tri]->getBloon(inter[1])->getPosition()) ,
                                                                    textload ,
                                                                    m_tower->getTower(v)->getEffect() ,
                                                                    m_tower->getTower(v)->getNbBall());
                        m_money += m_level[m_tri]->getBloon(inter[1])->getMoney();
                        m_first_pass = false;
                        inter[0] = 0;
                    }
                }
            }
            else
            {
                ecran->draw(m_bouton);
                if (sf::Mouse::getPosition(*ecran).x <= m_bouton.getGlobalBounds().left + m_bouton.getGlobalBounds().width &&
                   sf::Mouse::getPosition(*ecran).x >= m_bouton.getGlobalBounds().left &&
                   sf::Mouse::getPosition(*ecran).y <= m_bouton.getGlobalBounds().top + m_bouton.getGlobalBounds().height &&
                   sf::Mouse::getPosition(*ecran).y >= m_bouton.getGlobalBounds().top)
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        if (!m_tower->getStatus())
                            m_bp = true;
                    }
                }
                if (m_bp)
                {
                    m_bouton.scale(0.99f, 0.99f);
                    m_bouton.rotate(3.6);
                    if (m_bouton.getRotation() < 1 && m_bouton.getRotation() > 0)
                    {
                        m_bp = false;
                        m_bouton.scale(1/(m_bouton.getScale().x), 1/(m_bouton.getScale().y));
                        m_bouton.setRotation(-1 * m_bouton.getRotation());
                        m_play = 0;
                    }
                }
            }
            ecran->draw(m_tower_bar);
            m_money = m_tower->update(textload->getMap("virtual_grass_1.png"), ecran, textload, m_money, m_sup, m_click, m_mouse == 2);
            std::stringstream az;
            az << m_lives;
            m_life.setString(az.str());
            m_life.affiche(ecran);
            m_sup = false;
            if (m_mouse == 2)
                m_mouse = 0;
        }
        else
        {
            m_text_exit->affiche(ecran);
            m_text_loose->affiche(ecran);
            m_restart->setColor(sf::Color::Red, sf::Color::Black);
            m_restart->affiche(ecran);
            if (m_restart->inside(sf::Mouse::getPosition(*ecran), true))
            {
                m_wave = 0;
                m_lives = 200;
                m_money = 10;
                fclose(m_fichier);
                fopen("lvl_1.txt", "r");
                fseek(m_fichier, 0, SEEK_SET);
                m_seek = ftell(m_fichier);
                unsigned int k(0);
                while (k < m_level.size())
                {
                    delete m_level.at(k);
                    m_level.erase(m_level.begin());
                    k=0;
                }
                delete m_tower;
                m_tower = new Multitower(textload);
            }
            if (m_text_exit->inside(sf::Mouse::getPosition(*ecran), true))
            {
                m_done = true;
            }
        }
    }
    else
    {
        m_text_win->affiche(ecran);
        m_restart->setColor(sf::Color::Green, sf::Color::Red);
        m_restart->affiche(ecran);
        m_text_exit->affiche(ecran);
        if (m_restart->inside(sf::Mouse::getPosition(*ecran), true))
        {
            m_wave = 0;
            m_lives = 200;
            m_money = 10;
            fseek(m_fichier, 0, SEEK_SET);
            m_seek = ftell(m_fichier);
            m_win = false;
            unsigned int o(0);
            while (o < m_level.size())
            {
                delete m_level.at(o);
                m_level.erase(m_level.begin());
                o=0;
            }
            delete m_tower;
            m_tower = new Multitower(textload);
        }
        if (m_text_exit->inside(sf::Mouse::getPosition(*ecran), true))
        {
            m_done = true;
        }
    }
}



void Level::event(sf::RenderWindow *screen, Textureloader* textload)
{
    while (m_done == false)
    {
        while (screen->pollEvent(m_event))
        {
            switch (m_event.type)
            {
                case sf::Event::KeyPressed :
                    switch (m_event.key.code)
                    {
                        case sf::Keyboard::Escape :
                            m_done = true;
                            break;
                        case sf::Keyboard::Delete :
                            if (!m_delete)
                            {
                                m_sup = true;
                                m_delete = true;
                            }
                            break;
                        default :
                            break;
                    }
                    break;
                case sf::Event::KeyReleased :
                    switch (m_event.key.code)
                    {
                        case sf::Keyboard::Delete :
                            m_sup = false;
                            m_delete = false;
                            break;
                        default :
                            break;
                    }
                    break;
                case sf::Event::LostFocus :
                    m_bool_pause = true;
                    m_pause_bool = true;
                    break;
                case sf::Event::GainedFocus :
                    m_bool_pause = false;
                    break;
                default :
                    break;
            }
        }
        m_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (m_mouse == 0)
        {
            m_mouse = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
        if (m_mouse == 1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
        {
            m_mouse = 2;
        }
        screen->draw(m_sprite);
        if (m_pause_bool == false && m_bool_pause == false)
        {
            launch(screen, textload);
            m_pass_save = false;
        }
        if (m_pause_bool == true || m_bool_pause == true)
        {
            screen->draw(m_shape_pause);

            m_text_pause->affiche(screen);
            m_resume->affiche(screen);
            m_text_exit->affiche(screen);
            if (m_resume->inside(sf::Mouse::getPosition(*screen), true) && m_bool_pause == false)
            {
               m_pause_bool = false;
            }
            if (m_text_exit->inside(sf::Mouse::getPosition(*screen), true) && m_bool_pause == false)
            {
                m_done = true;
            }
        }
        screen->display();
        screen->clear();
    }

}
