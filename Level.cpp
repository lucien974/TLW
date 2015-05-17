#include "Level.h"

Level::Level(sf::Image carte_v , Textureloader* textload)
{
    m_bool_pause = false;
    m_fichier = fopen("levels/lvl_1.txt" , "r");
    m_nbbloon = 0;
    m_inter = 0;
    m_frontinter = 0;
    m_type = 0;
    m_pass = true;
    m_carte_v = carte_v;
    m_passinter = false;
    m_play = 0;
    m_pause = 0;
    m_end = false;
    m_done = false;
    m_one_time = true;
    m_sprite.setTexture(textload->Gettexture("grass_1.png"));
    m_sprite.scale(1.5f , 1.5f);
    m_money = 100;
    m_tower = new Multitower(carte_v , textload);
    m_text_pause = new Bouton(textload->Getfont("abaddon.ttf") , "PAUSE" ,
                               50 , sf::Color::Green , sf::Color::Green , sf::Vector2i(450 , 50));
    m_text_loose = new Bouton(textload->Getfont("abaddon.ttf") , "YOU LOOSE" ,
                               100  , sf::Color::Red , sf::Color::Red , sf::Vector2i(450,150));
    m_restart = new Bouton(textload->Getfont("abaddon.ttf") , "RESTART" ,
                               25  , sf::Color::Red , sf::Color::Black , sf::Vector2i(450,300));
    m_resume = new Bouton(textload->Getfont("abaddon.ttf") , "RESUME" ,
                               25  , sf::Color::Green , sf::Color::Red , sf::Vector2i(450,200));
    m_text_exit = new Bouton(textload->Getfont("abaddon.ttf") , "EXIT" ,
                               25  , sf::Color::Green , sf::Color::Red , sf::Vector2i(450,250));
    m_text_win = new Bouton(textload->Getfont("abaddon.ttf") , "YOU WIN" ,
                               100  , sf::Color::Yellow , sf::Color::Yellow , sf::Vector2i(450,150));
    m_tower_bar.setTexture(textload->Gettexture("tower_bar_1.png"));
    m_tower_bar.setPosition(750,0);
    m_bouton.setTexture(textload->Gettexture("play.png"));
    m_bouton.setOrigin(25 , 25);
    m_bouton.setPosition(25 , 330);
    m_bp = false;
    m_first_pass = true;
    m_play_save = 0;
    m_inter_vague = 0;
    m_seek = 0;
    m_win = false;
    m_lives = 200;
    m_loose.setTexture(textload->Gettexture("fond.png"));
    m_loose.setOrigin( 402 , 300 );
    m_loose.setPosition(400 , 300);
    fseek(m_fichier , 0 , SEEK_END);
    m_size = ftell(m_fichier);
    fseek(m_fichier , 0 , SEEK_SET);
    m_sup = false;
    m_delete = false;
}

Level::~Level()
{
    fclose(m_fichier);
    int f(0);
    while( f < m_level.size() )
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
}

void Level::Launch(sf::RenderWindow *ecran , Textureloader* textload)
{
    if(m_pass == true)
    {
        m_play = 0;
        std::cout << "wave create" << std::endl;
        while(m_play != 1)
        {
            fscanf( m_fichier , "%d %d %d %d %d" , &m_nbbloon , &m_inter , &m_type , &m_frontinter , &m_play);
            if( m_frontinter == -1 )
            {
                m_end = true;
            }
            else
            {
                m_inter_vague = m_frontinter;
            }
            m_interlevel.push_back(m_frontinter);
            m_level.push_back(new Vague(m_carte_v , m_type));
            m_level.back()->Move(ecran , m_nbbloon , m_inter , textload);
        }
        m_seek = ftell(m_fichier);
        std::cout << "wave succesfully created" << std::endl;
        if(m_seek == m_size)
            m_win = true;
        else
            m_win = false;
        m_play_save = 1;
        m_pass = false;
    }
    if(m_win == false)
    {
        if(m_lives > 0)
        {
            if(m_play == 0)
            {
                m_end = false;
                int k(0);
                if(m_level.size() == 0)
                {
                    m_pass = true;
                    m_interlevel.clear();
                }
                while( k < m_level.size() )
                {
                    if(k < m_play_save)
                    {
                        m_lives -= m_level[k]->Move(ecran , m_nbbloon , m_inter , textload);
                    }
                    if(m_level[k]->Next(m_interlevel[k]))
                    {
                        m_play_save++;
                        if(m_play_save >= m_level.size())
                            m_play_save = m_level.size();
                    }
                    if( m_level[k]->Size() == true )
                    {
                        delete m_level.at(k);
                        m_level.erase(m_level.begin() + k);
                        m_play_save--;
                    }
                    k++;
                }
                int inter[2];
                inter[0] = 0;
                for( int v(m_tower->Getsize() - 1) ; v >= 0  ; --v )
                {
                    for( int n(m_level.size() - 1) ; n >= 0 ; --n )
                    {
                        for( int g(0) ; g < m_level[n]->Getsize() ; ++g )
                        {
                            if(m_level[n]->Getbloon(g)->isNearOf(m_tower->Gettower(v) , m_tower->Getrange(v)))
                            {
                                if(m_level[n]->Getbloon(g)->Getincrementation() > inter[0])
                                {
                                    inter[0] = m_level[n]->Getbloon(g)->Getincrementation();
                                    inter[1] = g;
                                    m_tri = n;
                                    m_first_pass = true;
                                }
                            }
                        }
                    }
                    if(m_first_pass && inter[0] != 0)
                    {
                        m_tower->Gettower(v)->rotateTowards(m_level[m_tri]->Getbloon(inter[1]));
                        m_level[m_tri]->Getbloon(inter[1])->Touch(0 , 0 , m_tower->Gettower(v)->Fire() , textload);
                        m_money += m_level[m_tri]->Getbloon(inter[1])->Getmoney();
                        m_first_pass = false;
                        inter[0] = 0;
                    }
                }
            }
            else
            {
                ecran->draw(m_bouton);
                if(sf::Mouse::getPosition(*ecran).x <= m_bouton.getGlobalBounds().left + m_bouton.getGlobalBounds().width &&
                   sf::Mouse::getPosition(*ecran).x >= m_bouton.getGlobalBounds().left &&
                   sf::Mouse::getPosition(*ecran).y <= m_bouton.getGlobalBounds().top + m_bouton.getGlobalBounds().height &&
                   sf::Mouse::getPosition(*ecran).y >= m_bouton.getGlobalBounds().top )
                {
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        if(!m_tower->Getstatus())
                            m_bp = true;
                    }
                }
                if(m_bp)
                {
                    m_bouton.scale(0.99f , 0.99f);
                    m_bouton.rotate(3.6);
                    if(m_bouton.getRotation() < 1 && m_bouton.getRotation() > 0)
                    {
                        m_bp = false;
                        m_bouton.scale( 1/(m_bouton.getScale().x) , 1/(m_bouton.getScale().y) );
                        m_bouton.setRotation( -1 * m_bouton.getRotation() );
                        m_play = 0;
                    }
                }
            }
            ecran->draw(m_tower_bar);
            m_money = m_tower->Panel(m_sup , ecran , m_money , m_lives , textload);
            m_sup = false;
        }
        else
        {
            m_text_exit->Affiche(ecran);
            m_text_loose->Affiche(ecran);
            m_restart->Setcolor(sf::Color::Red , sf::Color::Black);
            m_restart->Affiche(ecran);
            if(m_restart->Inside(sf::Mouse::getPosition(*ecran) , true))
            {
                m_lives = 200;
                fseek(m_fichier , 0 , SEEK_SET);
                m_seek = ftell(m_fichier);
                int k(0);
                while( k < m_level.size() )
                {
                    delete m_level.at(k);
                    m_level.erase(m_level.begin());
                    k=0;
                }
            }
            if(m_text_exit->Inside(sf::Mouse::getPosition(*ecran) , true))
            {
                m_done = true;
            }
        }
    }
    else
    {
        m_text_win->Affiche(ecran);
        m_restart->Setcolor(sf::Color::Green , sf::Color::Red);
        m_restart->Affiche(ecran);
        m_text_exit->Affiche(ecran);
        if(m_restart->Inside(sf::Mouse::getPosition(*ecran) , true))
        {
            m_lives = 200;
            fseek(m_fichier , 0 , SEEK_SET);
            m_seek = ftell(m_fichier);
            m_win = false;
            int o(0);
            while( o < m_level.size() )
            {
                delete m_level.at(o);
                m_level.erase(m_level.begin());
                o=0;
            }
        }
        if(m_text_exit->Inside(sf::Mouse::getPosition(*ecran) , true))
        {
            m_done = true;
        }
    }
}

void Level::Event(sf::RenderWindow *screen ,  Textureloader* textload)
{
    while(m_done == false)
    {
        screen->pollEvent(m_event);
        switch(m_event.type)
        {
                break;
            case sf::Event::KeyPressed:
                switch(m_event.key.code)
                {
                    case sf::Keyboard::Escape:
                        m_done = true;
                        break;
                    case sf::Keyboard::Delete:
                        std::cout << "sup button pressed" << std::endl;
                        if(!m_delete)
                        {
                            std::cout << "sup = true" << std::endl;
                            m_sup = true;
                            m_delete = true;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch(m_event.key.code)
                {
                    case sf::Keyboard::Delete:
                        std::cout << "sup button release" << std::endl;
                        m_sup = false;
                        m_delete = false;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::LostFocus:
                m_bool_pause = true;
                break;
            default:
                break;
        }
        screen->draw(m_sprite);
        if(m_bool_pause == false)
        {
            Launch(screen , textload);
        }
        else
        {
            screen->draw(m_shape_pause);
            m_text_pause->Affiche(screen);
            m_resume->Affiche(screen);
            m_text_exit->Affiche(screen);
            if(m_resume->Inside(sf::Mouse::getPosition(*screen) , true))
            {
               m_bool_pause = false;
            }
            if(m_text_exit->Inside(sf::Mouse::getPosition(*screen) , true))
            {
                m_done = true;
            }
        }
        screen->display();
        screen->clear();
    }

}
