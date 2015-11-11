#include "TowerManager.h"

TowerManager::TowerManager(Textureloader* textload)
{
    for(int a(1) ; a < 5 ; ++a)
        m_selection.push_back(new Tower(a,textload,sf::Vector2f(785 , 75*a + 50)));
    for(int n(0) ; n < 4 ; ++n)
    {
        m_cost_sprite.push_back(Button(textload , m_selection[n]->getPrice() , "nb",
                                sf::Color::Black , sf::Color::Yellow ,
                                12 ,  sf::Vector2i(825 , 75*n + 100)));
    }
    m_select = -1;
    m_tower_selected = -1;
    m_up[0].setPosition(50 , 555);
    m_up[1].setPosition(380 , 555);

    m_up_price[0] = new Button(textload , "" , "nb" , sf::Color::Black , sf::Color::Yellow , 12 , sf::Vector2i(80 , 555));
    m_up_price[1] = new Button(textload , "" , "nb" , sf::Color::Black , sf::Color::Yellow , 12 , sf::Vector2i(440 , 555));

    m_money = new Button(textload , "" , "nb" , sf::Color::Yellow , sf::Color::Yellow , 20 ,  sf::Vector2i(750 , 520));
    m_money->setShadows(sf::Vector2i(-3,-3));
}

TowerManager::~TowerManager()
{
    for(int a(0) ; a < 4 ; ++a)
    {
        if(m_selection[a] != NULL)
            delete m_selection[a];
    }
    for(unsigned int b(0) ; b < m_tower.size() ; ++b)
        delete m_tower[b];
    m_selection.clear();
    m_tower.clear();
}

int TowerManager::update(sf::Image carte , sf::RenderWindow* screen , Textureloader* textload , int money , bool sup , bool clic_up)
{
    std::stringstream z;
    z << money;
    z << " '";
    m_money->setSentence(z.str());
    screen->draw(*m_money);
    if(m_select == -1)
    {
        for(int a(0) ; a < 4 ; ++a)
        {
            if(m_selection[a]->getGlobalBounds(sf::Mouse::getPosition(*screen)) &&
               clic_up == true &&
               money >= m_selection[a]->getCost())
            {
                m_select = a;
            }
        }
    }
    if(m_select != -1)
    {
        sf::Vector2f a;
        a = sf::Vector2f(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
        m_selection[m_select]->setPosition(a);
        if(a.x > 0 && a.x < screen->getSize().x && a.y > 0 && a.y < screen->getSize().y)
        {
            if(carte.getPixel(a.x , a.y) != sf::Color(0,153,0) &&
               carte.getPixel(a.x , a.y) != sf::Color(0,0,255) &&
               clic_up == true)
            {
                m_tower.push_back(new Tower(m_select+1 , textload , a));
                m_selection[m_select]->drawRange(false);
                m_selection[m_select]->setPosition(785 , 75*(m_select+1) + 50);
                money -= m_selection[m_select]->getCost();
                m_select = -1;
            }
            else
            {
                m_selection[m_select]->drawRange(true);
                screen->draw(*m_selection[m_select]);
            }
        }
        else
            m_selection[m_select]->drawRange(false);
    }
    for(int y(0) ; y < 4 ; ++y)
    {
        m_cost_sprite[y].onCondition(money >= m_selection[y]->getCost());
        screen->draw(m_cost_sprite[y]);
        screen->draw(*m_selection[y]);
    }
    bool found = false , click = clic_up;
    for(unsigned int z(0) ; z < m_tower.size() ; ++z)
    {
        sf::Vector2f a;
        m_tower[z]->drawBullet(screen);
        a = sf::Vector2f(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y);
        if(m_tower_selected != -1 && a.x > 0 && a.x < screen->getSize().x && a.y > 0 && a.y < screen->getSize().y)
        {
            if(m_tower[m_tower_selected]->getGlobalBounds(sf::Mouse::getPosition(*screen)) == false &&
               carte.getPixel(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) != sf::Color(0,0,255) &&
               click == true)
            {
                click = false;
                m_tower[m_tower_selected]->drawRange(false);
                m_tower_selected = -1;
            }
        }
        if(m_tower[z]->getGlobalBounds(sf::Mouse::getPosition(*screen)) &&
           click == true &&
           found == false)
        {
            found = true;
            if(m_tower_selected != -1)
                m_tower[m_tower_selected]->drawRange(false);
            m_tower_selected = z;
            click = false;
        }
        screen->draw(*m_tower[z]);
    }
    if(m_tower_selected != -1 && m_tower_selected < (int)m_tower.size())
    {
        if(sup)
        {
            delete m_tower[m_tower_selected];
            m_tower.erase(m_tower.begin() + m_tower_selected);
        }
        else
        {
            m_tower[m_tower_selected]->drawRange(true);
            if(m_tower[m_tower_selected]->getLeftUpgrade() != "")
            {
                std::stringstream a;
                m_up[0].setTexture(textload->getTexture(m_tower[m_tower_selected]->getLeftUpgrade()));
                m_up[0].setOrigin(m_up[0].getLocalBounds().height/2 , m_up[0].getLocalBounds().width/2);

                m_up_price[0]->onCondition(money >= m_tower[m_tower_selected]->getUpPrice(textload));

                a << m_tower[m_tower_selected]->getUpPrice(textload);

                m_up_price[0]->setSentence(a.str());
                if(m_up[0].getGlobalBounds().contains(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) &&
                   clic_up == true &&
                   money >= m_tower[m_tower_selected]->getUpPrice(textload))
                {
                    money -= m_tower[m_tower_selected]->getUpPrice(textload);
                    m_tower[m_tower_selected]->upgradeLeft(textload);
                    clic_up = false;
                }
                screen->draw(m_up[0]);
                screen->draw(*m_up_price[0]);
            }
            if(m_tower[m_tower_selected]->getRightUpgrade() != "")
            {
                std::stringstream b;
                m_up[1].setTexture(textload->getTexture(m_tower[m_tower_selected]->getRightUpgrade()));
                m_up[1].setOrigin(m_up[1].getLocalBounds().height/2 , m_up[1].getLocalBounds().width/2);

                m_up_price[1]->onCondition(money >= m_tower[m_tower_selected]->getUpPrice(textload));

                b << (m_tower[m_tower_selected]->getUpPrice(textload));

                m_up_price[1]->setSentence(b.str());
                if(m_up[1].getGlobalBounds().contains(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y) &&
                   clic_up == true &&
                   money >= m_tower[m_tower_selected]->getUpPrice(textload))
                {
                    money -= m_tower[m_tower_selected]->getUpPrice(textload);
                    m_tower[m_tower_selected]->upgradeRight(textload);
                    clic_up = false;
                }
                screen->draw(m_up[1]);
                screen->draw(*m_up_price[1]);
            }
        }
    }
    return money;
}

sf::Vector2f TowerManager::getPosition(int num)
{
    return m_tower[num]->getPosition();
}

int TowerManager::getSize()
{
    return m_tower.size();
}

float TowerManager::getRange(int n)
{
    return m_tower[n]->getRange();
}

void TowerManager::rotateTowards(int n , sf::Vector2f bloon)
{
    m_tower[n]->rotateTowards(bloon);
}

int TowerManager::shoot(int n , sf::Vector2f bloon)
{
    return m_tower[n]->shoot(bloon);
}

int TowerManager::getEffect(int n)
{
    return  m_tower[n]->getEffect();
}

int TowerManager::getNbBall(int n)
{
    return m_tower[n]->getNbBall();
}

bool TowerManager::getStatus()
{
    if(m_select != -1)
        return true;
    else
        return false;
}
