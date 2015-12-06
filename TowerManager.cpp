#include "TowerManager.h"

TowerManager::TowerManager(Textureloader* textload) :
m_select(-1),
m_select_upgrade(-1),
m_tower_selected(-1),
m_selection_position(sf::Vector2f(0, 0))
{
    m_textload = textload;
    for (int a(1); a < 5; ++a)
        m_selection.push_back(std::make_tuple(new Tower(a, m_textload, sf::Vector2f(0, 0)), PI/4, NB_ANIMATION));
    for (int n(0); n < 4; ++n)
    {

        m_cost_sprite.push_back(Button(m_textload, std::to_string(std::get<0>(m_selection[n])->getCost()), "nb",
                                sf::Color::Black, sf::Color::Yellow,
                                12, sf::Vector2i(825, 75*n + 100)));
    }
    /*
    m_up[0].setPosition(50, 555);
    m_up[1].setPosition(380, 555);
    //*/
    for (int i(0); i < NB_UPGRADES; ++i)
    {
        std::get<1>(m_up[i]) = i*PI;
        std::get<2>(m_up[i]) = NB_ANIMATION;
    }

    m_up_price[0] = new Button(m_textload, "", "nb", sf::Color::Black, sf::Color::Yellow, 12, sf::Vector2i(80, 555));
    m_up_price[1] = new Button(m_textload, "", "nb", sf::Color::Black, sf::Color::Yellow, 12, sf::Vector2i(440, 555));

    m_money = new Button(m_textload, "", "nb", sf::Color::Yellow, sf::Color::Yellow, 20, sf::Vector2i(750, 520));
    m_money->setShadows(sf::Vector2i(-3, -3));
}

TowerManager::~TowerManager()
{
    for (int a(0); a < 4; ++a)
    {
        if (std::get<0>(m_selection[a]) != nullptr)
            delete std::get<0>(m_selection[a]);
    }

    for (unsigned int b(0); b < m_tower.size(); ++b)
        delete m_tower[b];

    for (unsigned int i(0); i < 2; ++i)
    {
      delete m_up_price[i];
    }

    delete m_money;

    m_selection.clear();
    m_tower.clear();
}

int TowerManager::update(const sf::Image &virtual_map, sf::RenderWindow* screen, int money, bool sup, char *clic)
{
    bool clic_up(*clic == 2);
    m_money->setSentence(std::to_string(money) + " '");
    screen->draw(*m_money);

    bool found = false, click = clic_up;
    /**/
    for (unsigned int i(0); i < m_tower.size(); ++i)
    {
        sf::Vector2f a;
        m_tower[i]->drawBullet(screen);
        a = sf::Vector2f(sf::Mouse::getPosition(*screen).x, sf::Mouse::getPosition(*screen).y);
        if (m_tower_selected != -1 && a.x > 0 && a.x < screen->getSize().x && a.y > 0 && a.y < screen->getSize().y)
        {
            if (((a.x < m_tower[m_tower_selected]->getPosition().x - 40 ||
                a.x > m_tower[m_tower_selected]->getPosition().x + 40) ||
                (a.y < m_tower[m_tower_selected]->getPosition().y - 40 ||
                a.y > m_tower[m_tower_selected]->getPosition().y + 40)) &&
                virtual_map.getPixel(sf::Mouse::getPosition(*screen).x, sf::Mouse::getPosition(*screen).y) != sf::Color(0, 0, 128) &&
                click == true &&
                (m_select_upgrade == -1))
            {
                click = false;
                m_tower[m_tower_selected]->drawRange(false);
                m_tower_selected = -1;
            }
        }
        if (((sf::Mouse::getPosition(*screen).x > m_tower[i]->getPosition().x - 20 &&
            sf::Mouse::getPosition(*screen).x < m_tower[i]->getPosition().x + 20) &&
            (sf::Mouse::getPosition(*screen).y > m_tower[i]->getPosition().y - 20 &&
            sf::Mouse::getPosition(*screen).y < m_tower[i]->getPosition().y + 20)) &&
            click == true &&
            found == false)
        {
            found = true;
            if (m_tower_selected != -1)
                m_tower[m_tower_selected]->drawRange(false);
            m_tower_selected = i;
            m_select_upgrade = -1;
            click = false;
        }
        screen->draw(*m_tower[i]);
    }
    /**/
    if (m_select_upgrade == -1)
    {
        money = selectTowersManager(screen, money, virtual_map, clic_up);
        clic_up = false;
    }
    if (m_tower_selected != -1 && m_tower_selected < static_cast<int>(m_tower.size()) && m_select == -1)
    {
        if (sup)
        {
            m_textload->setForbidPosition(m_tower[m_tower_selected]->getPosition(), "virtual_map.png", sf::Color(0, 0, 0));
            money += m_tower[m_tower_selected]->sell();
            delete m_tower[m_tower_selected];
            m_tower.erase(m_tower.begin() + m_tower_selected);
            m_tower_selected = -1;
        }
        else
        {
            m_tower[m_tower_selected]->drawRange(true);
            money = selectUpgradeManager(screen, money, clic_up);
        }
    }
    if (m_select != -1)
        m_select_upgrade = -1;
    int n = money;
    if ((click == false || money != n) && *clic == 2)
    {
        *clic = 0;
    }
    return money;
}

int TowerManager::selectUpgradeManager(sf::RenderWindow *screen, int money, bool clic_up)
{
    if (m_select == -1)
    {
        switch (m_select_upgrade)
        {
            case -1:
                initialUpgradePosition(screen, money);
                break;
            case 0:
                towersUpgradeAnimation(screen);
                break;
            case 1:
                money = selectUpgrade(screen, money, clic_up);
                break;
            default:
                std::cout << "unknown upgrade command" << std::endl;
                break;
        }
    }
    return money;
}

void TowerManager::initialUpgradePosition(sf::RenderWindow *screen, int money)
{
    for (int i(0); i < NB_UPGRADES && m_tower_selected != -1; ++i)
    {
        if (m_tower[m_tower_selected]->getUpgrade(i) != "")
        {
            std::get<0>(m_up[i]).setTexture(m_textload->getTexture(m_tower[m_tower_selected]->getUpgrade(i)));
            std::get<0>(m_up[i]).setOrigin(40, 60);
            std::get<0>(m_up[i]).setPosition(m_tower[m_tower_selected]->getPosition());
            std::get<1>(m_up[i]) = i*PI;

            m_up_price[i]->setSentence(std::to_string(m_tower[m_tower_selected]->getUpgradePrice(m_textload, i)));
            m_up_price[i]->setOrigin(m_up_price[i]->getLocalBounds().width/2, m_up_price[i]->getCharacterSize()/2);
            m_up_price[i]->setPosition(sf::Vector2f(std::get<0>(m_up[i]).getPosition().x, std::get<0>(m_up[i]).getPosition().y));
            m_up_price[i]->onCondition(money >= m_tower[m_tower_selected]->getUpgradePrice(m_textload, i));

            screen->draw(std::get<0>(m_up[i]));
            screen->draw(*m_up_price[i]);
        }
        else
        {
            std::get<0>(m_up[i]).setPosition(-1, -1);
        }
    }
    m_select_upgrade = 0;
}

void TowerManager::towersUpgradeAnimation(sf::RenderWindow *screen)
{
    int no_animation(0);
    for (int i(0); i < NB_UPGRADES; ++i)
    {
        if (std::get<2>(m_up[i]) > 0)
        {
            if (std::get<0>(m_up[i]).getPosition() != sf::Vector2f(-1, -1))
            {
                --std::get<2>(m_up[i]);
                std::get<0>(m_up[i]).move(std::cos(std::get<1>(m_up[i]))*5, std::sin(std::get<1>(m_up[i]))*5);
                m_up_price[i]->move(std::cos(std::get<1>(m_up[i]))*5, std::sin(std::get<1>(m_up[i]))*5);
            }
        }
        else
        {
            m_select_upgrade = 1;
            std::get<2>(m_up[i]) = NB_ANIMATION;
        }
        if (std::get<0>(m_up[i]).getPosition() != sf::Vector2f(-1, -1))
        {
            screen->draw(std::get<0>(m_up[i]));
            screen->draw(*m_up_price[i]);
        }
        else
        {
            ++no_animation;
        }
    }
    if (no_animation == 2)
        m_select_upgrade = 1;
}

int TowerManager::selectUpgrade(sf::RenderWindow *screen, int money, bool clic_up)
{
    sf::Vector2f a;
    int diselect(0);
    a = sf::Vector2f(sf::Mouse::getPosition(*screen).x, sf::Mouse::getPosition(*screen).y);
    for (int i(0); i < NB_UPGRADES && m_tower_selected != -1 && m_select_upgrade != -1; ++i)
    {
        if (std::get<0>(m_up[i]).getPosition() != sf::Vector2f(-1, -1) && m_tower[m_tower_selected]->getUpgrade(i) != "")
        {
            screen->draw(std::get<0>(m_up[i]));
            screen->draw(*m_up_price[i]);
        }
        if (clic_up == true)
        {
            if (a.x > 0 && a.x < screen->getSize().x && a.y > 0 && a.y < screen->getSize().y &&
                a.x > std::get<0>(m_up[i]).getPosition().x - 20 && a.x < std::get<0>(m_up[i]).getPosition().x + 20 &&
                a.y > std::get<0>(m_up[i]).getPosition().y - 20 && a.y < std::get<0>(m_up[i]).getPosition().y + 20 &&
                money >= m_tower[m_tower_selected]->getUpgradePrice(m_textload, i))
            {
                money -= m_tower[m_tower_selected]->getUpgradePrice(m_textload, i);
                m_tower[m_tower_selected]->upgrade(m_textload, i);
                m_select_upgrade = -1;
            }
            else
            {
                ++diselect;
            }
        }
    }
    if (diselect == 2)
    {
        m_tower[m_tower_selected]->drawRange(false);
        m_tower_selected = -1;
        m_select_upgrade = -1;
    }
    return money;
}

int TowerManager::selectTowersManager(sf::RenderWindow *screen, int money, const sf::Image &virtual_map, bool clic_up)
{
    for (int i(0); i < 4; ++i)
    {
        m_cost_sprite[i].onCondition(money >= std::get<0>(m_selection[i])->getCost());
    }
    switch (m_select)
    {
        case -1:
            initialPosition(screen, virtual_map, clic_up);
            break;
        case 0:
            towersAnimation(screen);
            break;
        case 1:
            money = selectTowers(screen, money, clic_up);
            break;
        default:
            std::cout << "unknown tower command" << std::endl;
            break;
    }
    return money;
}

void TowerManager::initialPosition(sf::RenderWindow *screen, const sf::Image &virtual_map, bool clic_up)
{
    sf::Vector2f a;
    a = sf::Vector2f(sf::Mouse::getPosition(*screen).x, sf::Mouse::getPosition(*screen).y);
    if (a.x > 0 && a.x < screen->getSize().x && a.y > 0 && a.y < screen->getSize().y)
    {
        if (virtual_map.getPixel(a.x + 15, a.y + 15) == sf::Color(0, 0, 0))
        {
            if (clic_up == true)
            {
                for (int i(0); i < 4; ++i)
                {
                    std::get<1>(m_selection[i]) = i*(PI/2);
                    std::get<0>(m_selection[i])->setPosition(a);
                    m_cost_sprite[i].setPosition(a);
                    m_selection_position = a;
                }
                m_select = 0;
                m_tower_selected = -1;
            }
        }
        /*
        else
        {
            //CURSEUR ROUGE
        }
        //*/
    }
}

void TowerManager::towersAnimation(sf::RenderWindow *screen)
{
    int i(0);
    for (auto &key : m_selection)
    {
        if (std::get<2>(key) > 0)
        {
            --std::get<2>(key);
            (std::get<0>(key))->move(std::cos(std::get<1>(key))*5, std::sin(std::get<1>(key))*5);
            m_cost_sprite[i].move(std::cos(std::get<1>(key))*5, std::sin(std::get<1>(key))*5);
        }
        else
        {
            m_select = 1;
            std::get<2>(key) = NB_ANIMATION;
        }
        screen->draw(*std::get<0>(key));
        screen->draw(m_cost_sprite[i]);
        ++i;
    }
    m_tower_selected = -1;
}

int TowerManager::selectTowers(sf::RenderWindow *screen, int money, bool clic_up)
{
    sf::Vector2f a;
    int i(0), diselect(0);
    a = sf::Vector2f(sf::Mouse::getPosition(*screen).x, sf::Mouse::getPosition(*screen).y);
    for (auto &key : m_selection)
    {
        screen->draw(*std::get<0>(key));
        screen->draw(m_cost_sprite[i]);
        if (a.x > 0 && a.x < screen->getSize().x && a.y > 0 && a.y < screen->getSize().y &&
            a.x > std::get<0>(key)->getPosition().x - 20 && a.x < std::get<0>(key)->getPosition().x + 20 &&
            a.y > std::get<0>(key)->getPosition().y - 20 && a.y < std::get<0>(key)->getPosition().y + 20 &&
            clic_up == true &&
            money >= std::get<0>(key)->getCost())
        {

            m_tower.push_back(new Tower(std::get<0>(key)->getType(), m_textload, m_selection_position));
            m_textload->setForbidPosition(m_tower.back()->getPosition(), "virtual_map.png", sf::Color(0, 128, 128));
            money -= std::get<0>(key)->getCost();
            m_select = -1;
            m_selection_position = sf::Vector2f(0, 0);
            return money;
        }
        else
        {
            if (clic_up == true)
                ++diselect;
        }
        ++i;
    }
    m_tower_selected = -1;
    if (diselect == 4)
        m_select = -1;
    return money;
}

void TowerManager::shortcuts(unsigned char shortcuts, int &money)
{
    int type(0);
    if (m_selection_position != sf::Vector2f(0.0, 0.0))
    {
        switch (shortcuts)
        {
            case 0b1:
                type = 1;
                break;
            case 0b10:
                type = 2;
                break;
            case 0b100:
                type = 3;
                break;
            case 0b1000:
                type = 4;
                break;
            default:
                break;
        }
        if (type != 0)
        {
            m_select = -1;
            m_tower.push_back(new Tower(type, m_textload, m_selection_position));
            money -= m_tower.back()->getCost();
        }
    }
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

void TowerManager::rotateTowards(int n, sf::Vector2f bloon)
{
    m_tower[n]->rotateTowards(bloon);
}

int TowerManager::shoot(int n, sf::Vector2f bloon)
{
    return m_tower[n]->shoot(bloon);
}

int TowerManager::getEffect(int n)
{
    return m_tower[n]->getEffect();
}

int TowerManager::getNbBall(int n)
{
    return m_tower[n]->getNbBall();
}

bool TowerManager::getStatus()
{
    if (m_select != -1)
        return true;
    else
        return false;
}

void TowerManager::clear()
{
    for (unsigned int i(0); i < m_tower.size(); ++i)
    {
        m_textload->setForbidPosition(m_tower[i]->getPosition(), "virtual_map.png", sf::Color::Black);
        delete m_tower[i];
    }
    m_tower.clear();
}
