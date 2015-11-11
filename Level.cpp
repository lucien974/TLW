#include "Level.h"

Level::Level(Textureloader* textload , sf::RenderWindow *screen)
{
    m_done = false;
    m_screen = screen;
    m_textload = textload;

    m_map.setTexture(m_textload->getTexture("grass_1.png"));
    m_map.scale(1.5f , 1.5f);

    if(!m_file)
        cout << "Impossible d'ouvrir le fichier" << endl;
    m_clic = 0;
    m_delete = false;

    m_button_play.setTexture(m_textload->getTexture("play.png"));
    m_button_play.setPosition(m_textload->getPxlPos("virtual_grass_1.png" , sf::Color(255 , 0 , 128) , BUTTON));

    m_sprite_life.setTexture(m_textload->getTexture("heart.png"));
    m_sprite_life.setPosition(820 , 552);
    m_sprite_life.scale(0.4,0.4);

    m_win = new Menu(m_textload , "abaddon" , 50 , sf::Color::Green , sf::Color(0,128,0));
    m_win->setTitle("YOU LOOSE" , sf::Vector2i(450 , 150));
    m_win->newButton(RESTART , sf::Vector2i(0,150));
    m_win->newButton(EXIT , sf::Vector2i(0,75));


    m_text_life = new Button(m_textload , "" , "nb",
                        sf::Color::Red , sf::Color::Red ,
                        20 , sf::Vector2i(750 , 550));
    m_text_life->setShadows(sf::Vector2i(-3 , -3));

    m_interface.setTexture(m_textload->getTexture("tower_bar_1.png"));
    m_interface.setPosition(0,0);

    m_button_play.setTexture(m_textload->getTexture("play.png"));
    m_button_play.setOrigin(25 , 25);
    m_button_play.setPosition(25 , 330);

    m_pause = new Menu(m_textload , "abaddon" , 50 , sf::Color::Green , sf::Color(0,128,0));
    m_pause->setTitle("PAUSE" , sf::Vector2i(450 , 50));
    m_pause->newButton(RESUME , sf::Vector2i(0,150));
    m_pause->newButton(EXIT , sf::Vector2i(0,75));
    m_pause->setBackground(sf::Color(0,0,0,128));
    m_pause->onMouseClick(true , RESUME);

    m_loose = new Menu(m_textload , "abaddon" , 50 , sf::Color::Green , sf::Color(0,128,0));
    m_loose->setTitle("YOU LOOSE" , sf::Vector2i(450 , 150));
    m_loose->newButton(RESTART , sf::Vector2i(0,150));
    m_loose->newButton(EXIT , sf::Vector2i(0,75));

    initialize();
}

void Level::initialize()
{
    m_file.open("levels/lvl_1.txt" , ios::in);
    m_animation = 0;

    m_money = 500;
    m_lives = 200;
    m_towers = new TowerManager(m_textload);
    m_status = game_status::wait;
    m_play_save = 0;
    m_thread = new thread(&Level::physicsMotor , this);
    m_thread->detach();
}

void Level::physicsMotor()
{
    sf::Vector2f position;
    cout << "!!!!! thread launch !!!!!" << endl;
    while(m_status != game_status::loose && m_status != game_status::win && m_done == false)
    {
        int indice[2] , oldest = 0;
        indice[0] = 0;
        m_mutex.lock();
        for(int p(0) ; p < m_play_save ; ++p)
        {
            if(m_bloons[p] != NULL)
            {
                if(m_bloons[p]->isEmpty())
                {
                    m_play_save--;
                    delete m_bloons[p];
                    m_bloons.erase(m_bloons.begin() + p);
                }
            }
        }
        m_mutex.unlock();
        for( int v(m_towers->getSize() - 1) ; v >= 0  ; --v )
        {
            int n(m_bloons.size() - 1);
            while(n >= 0)
            {
                m_mutex.lock();
                for( int g(0) ; g < m_bloons[n]->size() ; ++g )
                {
                    position = m_bloons[n]->getBloonPosition(g);
                    if(position.x >= 0 && position.x <= 900 &&
                       position.y >= 0 && position.y <= 600 &&
                       v < m_towers->getSize())
                    {
                        if(m_bloons[n]->isNearOf(g , m_towers->getPosition(v) , m_towers->getRange(v)) == true)
                        {
                            if(m_bloons[n]->getAdvance(g) > oldest)
                            {
                                oldest = m_bloons[n]->getAdvance(g);
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
        this_thread::sleep_for(chrono::milliseconds(60));
    }
    cout << "!!!!! thread exit !!!!!" << endl;
    //*/
}

Level::~Level()
{
    m_status = game_status::loose;
    destroy();
    m_done = true;
    delete m_pause;
    delete m_win;
    delete m_loose;
    delete m_text_life;
}

void Level::destroy()
{
    m_file.close();
    m_play_save = 0;
    m_mutex.lock();
    while(m_bloons.size() > 0)
    {
        delete m_bloons[0];
        m_bloons.pop_front();
    }
    m_mutex.unlock();
    delete m_thread;
    delete m_towers;
    m_thread = NULL;
}

void Level::load()
{
    if(m_file)
    {
        int nb_bloons , type_of_bloon , gap , next_wave=0;
        while(next_wave != -1)
        {
            m_file >> nb_bloons >> gap >> type_of_bloon >> next_wave;
            m_bloons.push_back(new Wave(nb_bloons , type_of_bloon , gap , next_wave , "virtual_grass_1.png"));
            //wcout << L"\u2654";// << endl;
            //cout << nb_bloons << " , " << gap << " , " << type_of_bloon << " , " << next_wave << endl;
        }
        m_play_save = 1;
        m_status = game_status::wait;
        m_animation = 0;
    }
    else
        cout << "unable to load level (please contact the developpers)" << endl;
}

void Level::update(sf::RenderWindow *screen , Textureloader* textload)
{
    m_mutex.lock();
    if(m_bloons.size() == 0)
        load();
    if(m_status < game_status::wait)
    {
        //cout << m_play_save << endl;
        for(int i(0) ; i < m_play_save ; ++i)
        {
            if(!m_bloons[i]->isEmpty())
            {
                m_lives -= m_bloons[i]->update(screen , textload);
                if(m_bloons[i]->next())
                    m_play_save++;
            }
        }
    }
    else
    {
        if(m_button_play.getGlobalBounds().contains(sf::Mouse::getPosition(*screen).x , sf::Mouse::getPosition(*screen).y))
        {
            if(m_clic)
            {
                m_status = game_status::play_animation;
            }
        }
    }
    if(m_lives < 0)
        m_status = game_status::loose;
    screen->draw(m_interface);
    stringstream a;
    a << m_lives;
    m_text_life->setSentence(a.str());
    screen->draw(*m_text_life);
    screen->draw(m_sprite_life);
    if(m_status >= game_status::wait)
        screen->draw(m_button_play);
    m_money = m_towers->update(textload->getMap("virtual_grass_1.png") , screen , textload , m_money , m_delete , m_clic==2);
    if(m_clic == 2)
        m_clic = 0;
    m_mutex.unlock();
}

void Level::event(sf::RenderWindow *screen ,  Textureloader* textload)
{
    char status=0;
    while(m_done == false)
    {
        if(m_status != game_status::paused)
            status = m_status;
        while(screen->pollEvent(m_event))
        {
            switch(m_event.type)
            {
                /**/
                case sf::Event::Closed:
                    m_done = true;
                    break;
                    //*/
                case sf::Event::KeyPressed:
                    switch(m_event.key.code)
                    {
                        /*
                        case sf::Keyboard::Escape:
                            m_done = true;
                            break;
                            //*/
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
                    m_status = game_status::paused;
                    break;
                case sf::Event::GainedFocus:
                    break;
                default:
                    screen->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - 450 , sf::VideoMode::getDesktopMode().height/2 - 300));
                    break;
            }
        }
        if(m_done == true)
            cout << "End of game" << endl;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_clic == 1)
        {
            m_clic = 2;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true && m_clic == 0)
        {
            m_clic = 1;
        }
        screen->draw(m_map);
        string a;
        switch(m_status)
        {
            case game_status::play_animation:
                buttonAnimation();
                update(screen , textload);
                break;
            case game_status::wait:
            case game_status::normal:
                if(m_button_play.getScale() != sf::Vector2f(1,1))
                    m_button_play.scale(1/m_button_play.getScale().x , 1/m_button_play.getScale().y);
                update(screen , textload);
                m_delete = false;
                break;
            case game_status::paused:
                a = m_pause->update(screen , m_clic);
                if(a == RESUME)
                {
                    m_status = status;
                    m_clic = 0;
                }
                else if(a == EXIT)
                    m_done = true;
                else if(m_clic == 2)
                    m_clic = 0;
                break;
            case game_status::loose:
                a = m_loose->update(screen , m_clic);
                if(a == RESTART)
                {
                    destroy();
                    initialize();
                    cout << "game restarted" << endl;
                }
                else if(a == EXIT)
                    m_done = true;
                else if(m_clic == 2)
                    m_clic = 0;
                break;
            case game_status::win:
                a = m_win->update(screen , m_clic);
                if(a == RESTART)
                {
                    destroy();
                    initialize();
                }
                else if(a == EXIT)
                    m_done = true;
                else if(m_clic == 2)
                    m_clic = 0;
                break;
            default:
                cout << "Error game status undeclared" << endl;
                break;
        }
        screen->display();
        screen->clear();
    }
}

void Level::buttonAnimation()
{
    if(m_button_play.getScale().x >= 1.33 ||
       m_animation == 1)
    {
         m_animation = 1;
         m_button_play.scale(0.95,0.95);
    }
    if(m_button_play.getScale().x <= 0.33)
    {
        m_status = game_status::normal;
    }
    if(m_animation != 1)
    {
        m_button_play.scale(1.05 , 1.05);
    }
}
