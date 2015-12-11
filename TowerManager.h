#ifndef TOWER_MANAGER_H_INCLUDED
#define TOWER_MANAGER_H_INCLUDED

#include <deque>
#include <stdexcept>

#include "Tower.h"
#include "Button.h"

#define NB_UPGRADES 2
#define NB_TOWERS 4
#define NB_ANIMATION 10
#define MONEY_GAP 25

class TowerManager
{
    public:
        TowerManager(Textureloader* textload);
        ~TowerManager();
        int update(const sf::Image &virtual_map, sf::RenderWindow* screen, int money, bool sup, char *clic);
        int getSize();
        bool getStatus();
        sf::Vector2f getPosition(int num);
        float getRange(int n);
        void rotateTowards(int n, sf::Vector2f bloon);
        int shoot(int n, sf::Vector2f bloon);
        int getEffect(int n);
        int getNbBall(int n);
        void drawMoney(sf::RenderWindow *screen, int money);
        void clear();
        void shortcuts(unsigned char shortcuts, int &money);
        void save(std::ofstream *save);

    private:
        int selectTowersManager(sf::RenderWindow *screen, int money, const sf::Image &virtual_map, bool clic_up);
        void towersAnimation(sf::RenderWindow *screen, int money);
        int selectTowers(sf::RenderWindow *screen, int money, bool clic_up);
        void initialPosition(sf::RenderWindow *screen, const sf::Image &virtual_map, bool clic_up);

        int selectUpgradeManager(sf::RenderWindow *screen, int money, bool clic_up);
        void initialUpgradePosition(sf::RenderWindow *screen, int money);
        void towersUpgradeAnimation(sf::RenderWindow *screen, int money);
        int selectUpgrade(sf::RenderWindow *screen, int money, bool clic_up);

        std::deque<Tower*> m_tower;
        std::deque<std::tuple<Tower*, float, unsigned char>> m_selection;
        std::deque<Button> m_cost_sprite;
        int m_select, m_select_upgrade, m_tower_selected;
        std::tuple<sf::Sprite, float, unsigned char> m_up[NB_UPGRADES];
        sf::Vector2f m_selection_position;
        Button *m_up_price[NB_UPGRADES], *m_money;
        Textureloader *m_textload;
};

#endif // TOWER_MANAGER_H_INCLUDED
