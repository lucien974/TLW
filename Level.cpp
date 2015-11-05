#include "Level.h"

Level::Level(Textureloader* textload , sf::RenderWindow *screen)
{
    m_done = false;
    m_screen = screen;
    m_textload = textload;

    m_map.setTexture(textload->getTexture("grass_1.png"));
    m_map.scale(1.5f , 1.5f);

    m_money = 500;

    m_pause = new Menu(textload , "abaddon" , 50 , Color::Green , Color(0,128,0));
    m_pause->setTitle("PAUSE" , Vector2i(450 , 50));
    m_pause->newButton(RESUME , Vector2i(0,150));
    m_pause->newButton(EXIT , Vector2i(0,75));
    m_pause->setBackground(Color(0,0,0,128));
    m_pause->onMouseClick(true , RESUME);

    m_loose = new Menu(textload , "abaddon" , 50 , Color::Green , Color(0,128,0));
    m_loose->setTitle("YOU LOOSE" , Vector2i(450 , 150));
    m_loose->newButton(RESTART , Vector2i(0,150));
    m_loose->newButton(EXIT , Vector2i(0,75));

    m_win = new Menu(textload , "abaddon" , 50 , Color::Green , Color(0,128,0));
    m_win->setTitle("YOU LOOSE" , Vector2i(450 , 150));
    m_win->newButton(RESTART , Vector2i(0,150));
    m_win->newButton(EXIT , Vector2i(0,75));


    m_text_life = new Button(textload , "" , "nb",
                        Color::Red , Color::Red ,
                        20 , Vector2i(750 , 550));

    m_text_life->setShadows(Vector2i(-3 , -3));
    /**/
    m_interface.setTexture(textload->getTexture("tower_bar_1.png"));
    m_interface.setPosition(0,0);

    m_button_play.setTexture(textload->getTexture("play.png"));
    m_button_play.setOrigin(25 , 25);
    m_button_play.setPosition(25 , 330);

    m_towers = new Multitower(textload);
    /**/
    m_thread = new sf::Thread(&Level::physicsMotor , this);
    m_thread->launch();
    //*/
    m_interface.setTexture(textload->getTexture("tower_bar_1.png"));
    m_interface.setPosition(0,0);

    m_file.open("levels/lvl_1.txt" , ios::in);
    if(!m_file)
        cout << "Impossible d'ouvrir le fichier" << endl;
    m_play_save = 1;
    m_clic = 0;
    m_delete = false;
}

void Level::physicsMotor()
{
    /**/
    Vector2f position;
    while(!m_done)
    {
        int indice[2] , oldest = 0;
        indice[0] = 0;
        for(int p(0) ; p < m_play_save ; ++p)
        {
            if(m_bloons[p]->isEmpty())
            {
                m_play_save--;
                delete m_bloons[p];
                m_bloons.erase(m_bloons.begin() + p);
            }
        }
        for( int v(m_towers->getSize() - 1) ; v >= 0  ; --v )
        {
            int n(m_bloons.size() - 1);
            while(n >= 0)
            {
                m_mutex.lock();
                for( int g(0) ; g < m_bloons[n]->getSize() ; ++g )
                {
                    position = m_bloons[n]->getBloonPosition(g);//->getPosition().y;
                    //position.y = m_bloons[n]->getBloon(g)->getPosition().x;
                    if(position.x >= 0 && position.x <= 900 &&
                       position.y >= 0 && position.y <= 600)
                    {
                        if(m_bloons[n]->isNearOf(g , m_towers->getPosition(v) , m_towers->getRange(v)) == true)
                        {
                            if(m_bloons[n]->isWentOut(g) > oldest)
                            {
                                cout << "BLOON FIND!!!" << endl;
                                oldest = m_bloons[n]->isWentOut(g);
                                indice[1] = g;
                                indice[0] = n;
                            }
                        }
                    }
                }
                n--;
                m_mutex.unlock();
            }
            m_mutex.lock();
            if(oldest != 0)
            {
                m_towers->rotateTowards(v , m_bloons[indice[0]]->getBloonPosition(indice[1]));
                m_bloons[indice[0]]->isTouch(indice[1] ,
                                            m_bloons[indice[0]]->getBloonPosition(indice[1]) ,
                                            m_towers->shoot(v , m_bloons[indice[0]]->getBloonPosition(indice[1])) ,
                                            m_textload ,
                                            m_towers->getEffect(v) ,
                                            m_towers->getNbBall(v));

                m_money += m_bloons[indice[0]]->getMoney(indice[1]);
                indice[0] = 0;
                indice[1] = 0;
                oldest = 0;
            }
            m_mutex.unlock();
        }
    }
    //*/
}

Level::~Level()
{
    m_file.close();
    while(m_bloons.size() != 0)
    {
        delete m_bloons[0];
        m_bloons.pop_front();
    }
    delete m_towers;
    delete m_text_life;
}

void Level::load()
{
    m_mutex.lock();
    if(m_file)
    {
        int nb_bloons , type_of_bloon , gap , next_wave;
        while(next_wave != -1)
        {
            m_file >> nb_bloons >> gap >> type_of_bloon >> next_wave;
            m_bloons.push_back(new Wave(nb_bloons , type_of_bloon , gap , next_wave , "virtual_grass_1.png"));
            cout << nb_bloons << " , " << type_of_bloon << " , " << gap << ", " << next_wave << endl;
        }
        m_play_save = 1;
    }
    m_mutex.unlock();
}

void Level::update(sf::RenderWindow *screen , Textureloader* textload)
{
    if(m_bloons.size() == 0)
        load();
    m_mutex.lock();
    for(int i(0) ; i < m_play_save ; ++i)
    {
        //cout << i << " , " << m_bloons[i]->isEmpty() << endl;
        if(!m_bloons[i]->isEmpty())
        {
            m_bloons[i]->update(screen , textload);
            if(m_bloons[i]->next())
                m_play_save++;
        }
    }
    screen->draw(m_interface);
    m_money = m_towers->update(textload->getMap("virtual_grass_1.png") , screen , textload , m_money , m_delete , m_clic==2);
    if(m_clic == 2)
        m_clic = 0;
    m_mutex.unlock();
}

void Level::event(sf::RenderWindow *screen ,  Textureloader* textload)
{
    while(m_done == false)
    {
        while(screen->pollEvent(m_event))
        {
            switch(m_event.type)
            {
                case sf::Event::KeyPressed:
                    switch(m_event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            m_done = true;
                            break;
                        case sf::Keyboard::Delete:
                            if(!m_delete)
                            {
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
                            m_delete = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::LostFocus:
                    m_pause_avaible = true;
                    break;
                case sf::Event::GainedFocus:
                    break;
                default:
                    break;
            }
        }
        if(Mouse::isButtonPressed(Mouse::Button::Left) == true && m_clic == 0)
        {
            m_clic = 1;
        }
        if(Mouse::isButtonPressed(Mouse::Button::Left) == 0 && m_clic == 1)
        {
            m_clic = 2;
        }
        screen->draw(m_map);
        if(m_pause_avaible)
        {
            string a = m_pause->update(screen);
            if(a == RESUME)
                m_pause_avaible = false;
            if(a == EXIT)
                m_done = true;
        }
        else
        {
            update(screen , textload);
        }
        screen->display();
        screen->clear();
    }
}
