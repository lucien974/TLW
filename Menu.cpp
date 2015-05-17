#include "Menu.h"

Interface::Interface(Textureloader* textload)
{
    m_fond.setTexture(textload->Gettexture("fond.png"));
    m_fond.setPosition(0,0);
    m_bouton_play = new Bouton( textload->Getfont("danger.ttf") , "PLAY" ,
                                25 , sf::Color::Red , sf::Color::Black , sf::Vector2i(950,100) );
    m_bouton_play->Doublebutton(textload->Getfont("danger.ttf"),4,4,sf::Color::White);
    m_bouton_exit = new Bouton( textload->Getfont("danger.ttf") , "EXIT" ,
                                25 , sf::Color::Red , sf::Color::Black , sf::Vector2i(950,525) );
    m_bouton_exit->Doublebutton(textload->Getfont("danger.ttf"),4,4,sf::Color::White);
    m_name = new Bouton( textload->Getfont("danger.ttf") , "TOWER  DEFENSE" ,
                         25 , sf::Color::Red , sf::Color::Black , sf::Vector2i(450,600) );
    m_name->Doublebutton(textload->Getfont("danger.ttf"),4,4,sf::Color::White);
    m_fusion.setTexture(textload->Gettexture("bloon_11.png"));
    m_fusion.scale(1.5,1.5);
    m_fusion.setPosition(370,270);
    m_anim_1 = true;
    m_anim_2 = false;
    m_anim_3 = false;
    m_anim_4 = false;
    tpssuiv = 0;
    m_explo = 1;
    m_anim_5 = false;
    m_left.setSize(sf::Vector2f(400, 600));
    m_right.setSize(sf::Vector2f(400, 600));
    m_left.setFillColor(sf::Color::Red);
    m_right.setFillColor(sf::Color::Red);
    m_left.setPosition(0 , 0);
    m_right.setPosition(400,0);
    m_explosion.setPosition(400,300);
    m_explosion.setFillColor(sf::Color::Blue);
    m_pass = true;
    m_end = false;
    m_view.setCenter(400,300);
    m_view.setSize(900,600);
    srand(time(NULL));
    m_alea = 0;
    m_click = false;
    m_tower = new Tower(1 , textload , 1);
    m_tower->setPosition(405 , 302);
    m_tower_2 = new Tower(1 , textload , 1);
    m_tower_2->setPosition(405 , 302);
    m_inter = new Tower(1 , textload , 1);
    m_exit = true;
}

Interface::~Interface()
{
    delete m_white;
    delete m_black;
    delete m_inter;
    delete m_tower;
    delete m_tower_2;
    delete m_bouton_play;
    delete m_bouton_exit;
    delete m_name;
}

void Interface::Update(sf::RenderWindow* screen , Textureloader* textload)
{
    if(!m_anim_4 || !m_anim_5)
    {
        screen->draw(m_fond);
    }
    if(m_pass)
    {
        m_image.loadFromFile("images/part_1.png");
        m_white = new Bloon(m_image , 6 , textload);
        m_image.loadFromFile("images/part_2.png");
        m_black = new Bloon(m_image , 5 , textload);
        m_black->Setspeed(10);
        m_white->Setspeed(10);
        m_pass = false;
        m_end = false;
    }
    if(m_anim_1 == true)
    {
        screen->draw(*m_tower);
        if(!m_anim_2)
            screen->draw(*m_tower_2);
        if( m_white->Exit() == false ||  m_black->Exit() == false )
        {
            m_tower_2->rotateTowards(m_black);
            m_tower->rotateTowards(m_white);
            m_white->update();
            m_black->update();
            screen->draw(*m_white);
            screen->draw(*m_black);
            if(m_white->isNearOf(m_tower , 200))
            {
                m_white->Touch(0 , 0 , m_tower->Fire() , textload);
            }
            if(m_black->isNearOf(m_tower_2 , 200))
            {
                m_black->Touch(0 , 0 , m_tower_2->Fire() , textload);
            }
        }
        if( m_white->Exit() == true ||  m_black->Exit() == true )
        {
            m_anim_1 = true;
            m_anim_2 = true;
        }
    }
    if(m_anim_2 == true)
    {
        if(m_explo < 550)
        {
            screen->setView(screen->getDefaultView());
            m_explo+=5;
            screen->draw(m_explosion);
            m_explosion.setRadius(m_explo);
            m_explosion.setFillColor(sf::Color::Blue);
            m_explosion.setPosition(450 - m_explo,300 - m_explo);
        }
        else
        {
            if(m_explo < 510)
            {
                m_explo = 600;
                screen->setView(screen->getDefaultView());
            }
            m_bouton_play->Affiche(screen);
            m_bouton_exit->Affiche(screen);
            m_name->Affiche(screen);
            if(m_bouton_play->Getpos().x > 100)
            {
                m_bouton_play->Move(-10 , 0);
            }
            else
            {
                m_anim_3 = true;
            }
            if(m_bouton_exit->Getpos().x > 650)
            {
                m_bouton_exit->Move(-10,0);
            }
            if(m_name->Getpos().y > 30)
            {
                m_name->Move(0,-10);
            }
        }
    }
    if(m_anim_3 == true)
    {
        m_inter->setPosition(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
        if(m_inter->isNearOf(m_tower , 900))
        {
            m_tower->rotateTowards(m_inter);
        }
        screen->draw(*m_tower);
        if(m_bouton_play->Inside(sf::Mouse::getPosition(*screen) , true))
        {
            m_end = true;
            std::cout << "PLAY" << std::endl;
        }
        if(m_bouton_exit->Inside(sf::Mouse::getPosition(*screen) , true))
        {
            m_end = true;
            m_exit = true;
            std::cout << "EXIT" << std::endl;
        }
        else
        {
            m_exit = false;
        }
    }
    if(!m_exit)
    {
        if(m_anim_5)
        {
            if(m_anim_4 == true)
            {
                m_fond_texture.loadFromFile("images/grass_1.png");
                m_fond.setTexture(m_fond_texture);
                m_fond.scale(sf::Vector2f(1.5,1.5));
                m_fond.setPosition(0,0);
                m_anim_4 = false;
                m_anim_3 = false;
                m_anim_1 = false;
                m_anim_2 = false;
            }
            screen->draw(m_fond);
            screen->draw(m_left);
            screen->draw(m_right);
            if(m_left.getPosition().x > -400)
                m_left.move(-5 , 0);
            if(m_right.getPosition().x < 800)
                m_right.move(5 , 0);
            else
                m_end = true;
        }
    }
}

bool Interface::Boucle(sf::RenderWindow* screen , Textureloader* textload)
{
    while(m_end == false)
    {
        screen->pollEvent(m_event);
        switch(m_event.type)
        {
            case sf::Event::Closed:
                //m_end = true;
                break;
            case sf::Event::KeyPressed:
                switch(m_event.key.code)
                {
                    case sf::Keyboard::Escape:
                        m_end = true;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                m_click = true;
                break;
            default:
                break;
        }
        Update(screen , textload);
        screen->display();
        screen->clear();
    }
    return m_exit;
}
