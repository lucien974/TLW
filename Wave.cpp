#include "Wave.h"

Wave::Wave(int nb_bloons, int type, int gap, int next_wave, std::string carte) :
m_gap(gap),
m_nb_bloons(nb_bloons),
m_cursor(gap),
m_type(type),
m_way(next_wave),
m_carte(carte)
{
}

int Wave::update(sf::RenderWindow* ecran, Textureloader* textload)
{
    int damages = 0;
    if (m_nb_bloons > 0 && m_gap >= m_cursor)
    {
        m_bloon.push_back(new Bloon(m_type, textload, textload->getPxlPos(m_carte, sf::Color(255, 0, 0), BLOON)));
        m_bloon.back()->setMap(m_carte);
        m_gap = 0;
        m_nb_bloons--;
    }
    if (m_way > 0)
        m_way--;
    m_gap++;
    unsigned int k(0);
    while (k < m_bloon.size())
    {
        if (m_bloon[k]->isWentOut() == true)
        {
            delete m_bloon.at(k);
            m_bloon.erase(m_bloon.begin() + k);
        }
        else
        {
            if (m_bloon[k]->getHealth() > 0)
            {
                m_bloon[k]->update(textload);
                    ecran->draw(*m_bloon[k]);
                damages += m_bloon[k]->getDamages();
            }
            k++;
        }
    }
    return damages;
}

bool Wave::next()
{
    if (m_way == 0)
    {
        m_way = -1;
        return true;
    }
    else
        return false;
}

bool Wave::isEmpty()
{
    if (m_bloon.size() == 0 && m_nb_bloons <= 0)
        return true;
    else
        return false;
}

Wave::~Wave()
{
    for (unsigned int n(0); n < m_bloon.size(); ++n)
    {
        delete m_bloon.front();
        m_bloon.pop_front();
    }
}

sf::Vector2f Wave::getBloonPosition(int num)
{
    return m_bloon[num]->getPosition();
}

bool Wave::isNearOf(int bloon_num, sf::Vector2f tower_pos, float radius)
{
    return m_bloon[bloon_num]->isInRange(tower_pos, radius);
}

int Wave::isWentOut(int n)
{
    return m_bloon[n]->isWentOut();
}

void Wave::isTouch(int n, sf::Vector2f pos_ball, int damages, Textureloader* textload, int effect, int ice_limit)
{
    m_bloon[n]->isTouch(pos_ball, damages, textload, effect, ice_limit);
}

int Wave::getMoney(int n)
{
    return m_bloon[n]->getMoney();
}

int Wave::size()
{
    return m_bloon.size();
}

int Wave::getAdvance(int n)
{
    return m_bloon[n]->getAdvance();
}

int Wave::getBloonSpeed(unsigned int num_bloon)
{
    return m_bloon[num_bloon]->getSpeed();
}

void Wave::destroyBloon(unsigned int num)
{
    if (num < m_bloon.size())
    {
        delete m_bloon[num];
        m_bloon.erase(m_bloon.begin() + num);
    }
}
