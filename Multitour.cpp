#include "Multitour.h"

Multitower::Multitower(sf::Image carte_v , Textureloader* textload)
{
    m_carte = carte_v;
    /*
    m_choice.setTexture(textload->Gettexture("tower_1.png"));
    m_choice.setPosition(840,60);
    ///*/
    int pos_y(60);
    for(int go(0) ; go < 2 ; ++go)
    {
        std::stringstream a;
        a << go+1;
        m_choice.push_back(NULL);
        m_choice.back() = new sf::Sprite(textload->Gettexture("tower_" + a.str() +".png"));
        m_choice.back()->setPosition(840,pos_y);
        m_choice.back()->setOrigin(40,60);
        m_cost.push_back(10 + (10*go));
        pos_y += 80;
        std::stringstream ss;
        ss << m_cost.back();
        m_sprite_cost.push_back(NULL);
        m_sprite_cost.back() = new sf::Text( ss.str() , textload->Getfont("nb.ttf") , 10 );
        m_sprite_cost.back()->setColor(sf::Color::Black);
        m_sprite_cost.back()->setPosition(800 , 45 + (80*go));
    }
    m_sprite_money.setFont(textload->Getfont("nb.ttf"));
    m_lives.setFont(textload->Getfont("nb.ttf"));
    m_sprite_money.setCharacterSize(20);
    m_lives.setCharacterSize(20);
    m_sprite_money.setColor(sf::Color::Yellow);
    m_lives.setColor(sf::Color::Red);
    m_sprite_money.setPosition(450 , 20);
    m_set = false;
    m_button_pressed = false;
    m_type = 1;
    m_rayon.setFillColor(sf::Color(0, 0, 255, 128));
    m_select = -1;
    m_sel = 0;
    m_suppression = false;
}

Multitower::~Multitower()
{
    for(int h(0) ; h < m_tower.size() ; ++h)
    {
        delete m_tower.back();
        m_tower.pop_back();
    }
}

int Multitower::Panel(bool sup , sf::RenderWindow* screen , int money , int lives , Textureloader* textload)
{
    std::stringstream ss;
    ss << money;
    std::string str = ss.str();
    m_sprite_money.setString(str);
    std::stringstream ar;
    ar << lives;
    str = ar.str();
    m_lives.setString(str);
    if(m_set)
    {
        m_choice[m_sel]->setPosition(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y );
        m_rayon.setPosition(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y );
        screen->draw(m_rayon);
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_button_pressed = true;
    }
    else
    {
        m_button_pressed = false;
    }
    if(m_set == true && m_button_pressed == false)
    {
        m_set = false;
        m_choice[m_sel]->setPosition(840 , 60 + (80 * m_sel));
        if(Settower(screen , textload))
            return money - m_cost[m_sel];
        else
            return money;
    }
    screen->pollEvent(m_event);
    for( int ah(0) ; ah < m_choice.size() ; ++ah )
    {
        screen->draw(*m_choice[ah]);
        screen->draw(*m_sprite_cost[ah]);
    }
    screen->draw(m_sprite_money);
    screen->draw(m_lives);
    m_suppression = sup;
    for(int t(0) ; t < m_tower.size() ; ++t)
    {
        if( sf::Mouse::getPosition(*screen).x >= (*m_tower[t]).getPosition().x - 20 &&
            sf::Mouse::getPosition(*screen).x <= (*m_tower[t]).getPosition().x + 20 &&
            sf::Mouse::getPosition(*screen).y >= (*m_tower[t]).getPosition().y - 60 &&
            sf::Mouse::getPosition(*screen).y <= (*m_tower[t]).getPosition().y + 20 )
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(m_select == -1)
                {
                    m_select = t;
                    std::cout << "tower" << t << " selected" << std::endl;
                }
            }
        }
        else
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(t == m_select)
                {
                    m_select = -1;
                    std::cout << "no tower selected" << std::endl;
                }
            }
        }
        if(t == m_select)
        {
            m_tower[t]->Range(screen);
            screen->draw(*m_tower[t]);
            if(m_suppression)
            {
                std::cout << "delete tower" << t << std::endl;
                money += m_tower[t]->Sell();
                delete m_tower[t];
                m_tower.erase( m_tower.begin() + t );
                m_suppression = false;
            }
        }
        else
            screen->draw(*m_tower[t]);
    }
    for(int yu(0) ; yu < m_choice.size() ; ++yu)
    {
        if(money >= m_cost[yu])
        {
            m_sprite_cost[yu]->setColor(sf::Color::Yellow);
            if( sf::Mouse::getPosition(*screen).x >= m_choice[yu]->getGlobalBounds().left &&
                sf::Mouse::getPosition(*screen).x <= m_choice[yu]->getGlobalBounds().left + m_choice[yu]->getGlobalBounds().width &&
                sf::Mouse::getPosition(*screen).y >= m_choice[yu]->getGlobalBounds().top &&
                sf::Mouse::getPosition(*screen).y <= m_choice[yu]->getGlobalBounds().top + m_choice[yu]->getGlobalBounds().height )
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(m_set == false)
                    {
                        m_set = true;
                        m_choice[yu]->setPosition(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
                        m_button_pressed = true;
                        m_rayon.setRadius(100.0);
                        m_rayon.setOrigin(m_rayon.getGlobalBounds().width / 2 , m_rayon.getGlobalBounds().height / 2);
                        m_rayon.setPosition(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
                        m_sel = yu;
                    }
                }
            }
        }
        else
        {
            m_sprite_cost[yu]->setColor(sf::Color::Black);
        }
    }
    return money;
}

bool Multitower::Settower(sf::RenderWindow* screen , Textureloader* textload)
{
    if(sf::Mouse::getPosition(*screen).x < m_carte.getSize().x && sf::Mouse::getPosition(*screen).y < m_carte.getSize().y)
    {
        m_color = m_carte.getPixel(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
        if(m_color == sf::Color::Black)
        {
            m_tower.push_back(NULL);
            m_tower.back() = new Tower(m_sel + 1 , textload , m_cost[m_sel]);
            m_tower.back()->setPosition(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
            m_tower.back()->update();
            m_choice[m_sel]->setPosition(840,60 + (m_sel * 80));
            return true;
        }
    }
    return false;
}

int Multitower::Getsize()
{
    return m_tower.size();
}

Tower* Multitower::Gettower(int b)
{
    return m_tower[b];
}

bool Multitower::Getstatus()
{
    return m_set;
}

int Multitower::Getrange(int n)
{
    return m_tower[n]->Getrange();
}
