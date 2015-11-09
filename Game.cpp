#include "Game.h"

Game::Game()
{
    m_background.setTexture(m_textload->getTexture("fond.png"));

    m_level = new Level(m_textload , &m_screen);
    m_start = new Menu(m_textload , "abaddon.ttf" , 100 , Color::Green , Color::Black);
    m_start->setTitle("BALLONS\n  WAR" , Vector2i(450 , 50));
    m_start->newButton(PLAY , Vector2i(0,100));
    m_start->newButton(EXIT , Vector2i(0,100));
}
