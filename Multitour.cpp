#include "Multitour.h"

Multitower::Multitower(Textureloader* textload)
{
    for(int a(1) ; a < 5 ; ++a)
        m_selection.push_back(new Tower(a,textload,sf::Vector2f(785 , 75*a + 50)));
    for(int n(0) ; n < 4 ; ++n)
    {
        m_cost_sprite.push_back(Bouton());
        m_cost_sprite.back().set(textload->Getfont("nb.ttf") , m_selection[n]->getPrice() ,
                                 12 , sf::Color::Black , sf::Color::Yellow , sf::Vector2i(825 , 75*n + 100));
    }
    m_select = -1;
    m_tower_selected = -1;
    m_up[0].setPosition(50 , 555);
    m_up[1].setPosition(380 , 555);
    m_up_price[0].set(textload->Getfont("nb.ttf") , "" ,
                      12 , sf::Color::Black , sf::Color::Yellow , sf::Vector2i(80 , 555));
    m_up_price[1].set(textload->Getfont("nb.ttf") , "" ,
                      12 , sf::Color::Black , sf::Color::Yellow , sf::Vector2i(440 , 555));
}

Multitower::~Multitower()
{
    for(int a(0) ; a < 4 ; ++a)
        delete m_selection[a];
    for(int b(0) ; b < m_tower.size() ; ++b)
        delete m_tower[b];
    m_selection.clear();
    m_tower.clear();
}

int Multitower::update(sf::Image carte , sf::RenderWindow* screen , Textureloader* textload , int money , bool sup)
{
    if(m_select == -1)
    {
        for(int a(0) ; a < 4 ; ++a)
        {
            if(m_selection[a]->getGlobalBounds(sf::Mouse::getPosition(*screen)) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
            {
                std::cout << "ALLRIGHT" << std::endl;
                m_select = a;
            }
        }
    }
    if(m_select != -1)
    {
        m_selection[m_select]->setPosition(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
        if(carte.getPixel(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) != sf::Color(0,153,0) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
        {
            m_tower.push_back(new Tower(m_select+1 , textload , (sf::Vector2f)sf::Mouse::getPosition(*screen)));
            m_selection[m_select]->drawRange(false);
            m_selection[m_select]->setPosition(785 , 75*(m_select+1) + 50);
            m_select = -1;
        }
        else
        {
            m_selection[m_select]->drawRange(true);
            screen->draw(*m_selection[m_select]);
        }
    }
    for(int y(0) ; y < 4 ; ++y)
    {
        if(y != m_select)
            screen->draw(*m_selection[y]);
        m_cost_sprite[y].changeColor(money >= m_selection[y]->getCost());
        m_cost_sprite[y].affiche(screen);
        screen->draw(*m_selection[y]);
    }
    bool p(false);
    for(int z(0) ; z < m_tower.size() ; ++z)
    {
        m_tower[z]->drawBullet(screen);

        if(m_tower[z]->getGlobalBounds(sf::Mouse::getPosition(*screen)) == false &&
           carte.getPixel(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) != sf::Color(0,0,255) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Left) == true &&
           p == false)
        {
            //std::cout << "money : " << money << std::endl;
            if(m_tower_selected != -1)
                m_tower[m_tower_selected]->drawRange(false);
            m_tower_selected = -1;
            //m_tower[m_tower_selected]->drawRange(false);
        }

        /**/
        if(m_tower[z]->getGlobalBounds(sf::Mouse::getPosition(*screen)) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Left) == true &&
           p == false)
        {
            std::cout << ";)" << std::endl;
            if(m_tower_selected != -1)
                m_tower[m_tower_selected]->drawRange(false);
            m_tower_selected = z;
            p = true;
        }
        //*/

        screen->draw(*m_tower[z]);
        if(m_tower_selected != -1)
            m_tower[m_tower_selected]->drawRange(true);
    }
    if(m_tower_selected != -1)
    {
        bool x,y;
        if(m_tower[m_tower_selected]->getLeftUpgrade() != "")
        {
            x = true;
            std::stringstream a;
            m_up[0].setTexture(textload->Gettexture(m_tower[m_tower_selected]->getLeftUpgrade()));
            m_up[0].setOrigin(m_up[0].getLocalBounds().height/2 , m_up[0].getLocalBounds().width/2);
            m_up_price[0].changeColor(money < m_tower[m_tower_selected]->getUpPrice(textload));
            a << m_tower[m_tower_selected]->getUpPrice(textload);
            m_up_price[0].setString(a.str());
            if(m_up[0].getGlobalBounds().contains(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) &&
               carte.getPixel(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) == sf::Color(0,0,255) &&
               sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                money -= m_tower[m_tower_selected]->getUpPrice(textload);
                m_tower[m_tower_selected]->upgradeLeft(textload);
            }
        }
        else
        {
            x = false;
        }
        if(m_tower[m_tower_selected]->getRightUpgrade() != "")
        {
            y = true;
            std::stringstream b;
            m_up[1].setTexture(textload->Gettexture(m_tower[m_tower_selected]->getRightUpgrade()));
            m_up[1].setOrigin(m_up[1].getLocalBounds().height/2 , m_up[1].getLocalBounds().width/2);
            m_up_price[1].changeColor(money < m_tower[m_tower_selected]->getUpPrice(textload));
            b << m_tower[m_tower_selected]->getUpPrice(textload);
            m_up_price[1].setString(b.str());
            if(m_up[1].getGlobalBounds().contains(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) &&
               carte.getPixel(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) == sf::Color(0,0,255) &&
               sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                money -= m_tower[m_tower_selected]->getUpPrice(textload);
                m_tower[m_tower_selected]->upgradeRight(textload);
            }
        }
        else
        {
            y = false;
        }
        if(sup)
        {
            delete m_tower[m_tower_selected];
            m_tower.erase(m_tower.begin() + m_tower_selected);
        }
        else
        {
            if(x)
            {
               screen->draw(m_up[0]);
               m_up_price[0].affiche(screen);

            }
            if(y)
            {
                screen->draw(m_up[1]);
                m_up_price[1].affiche(screen);
            }
        }
    }
    return money;
}

int Multitower::getSize()
{
    return m_tower.size();
}

Tower* Multitower::getTower(int b)
{
    return m_tower[b];
}

bool Multitower::getStatus()
{
    if(m_select != -1)
        return true;
    else
        return false;
}
