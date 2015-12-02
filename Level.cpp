#include "Level.h"

Level::Level(Textureloader* textload, sf::RenderWindow *screen, std::string file) :
m_money(0),
m_lives(0),
m_status(game_status::wait),
m_play_save(0),
m_clic(0),
m_animation(0),
m_done(false),
m_delete(false),
m_end(false),
m_file_name(file),
m_thread(nullptr),
m_screen(screen),
m_textload(textload)
{
    m_map.setTexture(m_textload->getTexture("map.png"));

    if (!m_file)
        std::cout << "Impossible d'ouvrir le fichier" << std::endl;

    m_button_play.setTexture(m_textload->getTexture("play.png"));
    m_button_play.setPosition(m_textload->getPxlPos("virtual_map.png", sf::Color(255, 0, 128), BUTTON).x - 15,
                              m_textload->getPxlPos("virtual_map.png", sf::Color(255, 0, 128), BUTTON).y - 15);

    m_sprite_life.setTexture(m_textload->getTexture("heart.png"));
    m_sprite_life.setPosition(820, 552);
    m_sprite_life.scale(0.4, 0.4);

    m_win = new Menu(m_textload, "abaddon", 50, sf::Color::Green, sf::Color(0, 128, 0));
    m_win->setTitle("YOU WIN", sf::Vector2i(450, 150));
    m_win->newButton(RESTART, sf::Vector2i(0, 150));
    m_win->newButton(EXIT, sf::Vector2i(0, 75));

    m_text_life = new Button(m_textload, "", "nb",
                        sf::Color::Red, sf::Color::Red,
                        20, sf::Vector2i(750, 550));
    m_text_life->setShadows(sf::Vector2i(-3, -3));

    m_interface.setTexture(m_textload->getTexture("tower_manager.png"));
    m_interface.setPosition(0, 0);
    /*
    m_button_play.setTexture(m_textload->getTexture("play.png"));
    m_button_play.setOrigin(25, 25);
    m_button_play.setPosition(25, 330);
    //*/
    m_pause = new Menu(m_textload, "abaddon", 50, sf::Color::Green, sf::Color(0, 128, 0));
    m_pause->setTitle("PAUSE", sf::Vector2i(450, 50));
    m_pause->newButton(RESUME, sf::Vector2i(0, 150));
    m_pause->newButton(EXIT, sf::Vector2i(0, 75));
    m_pause->setBackground(sf::Color(0, 0, 0, 128));
    m_pause->onMouseClick(true, RESUME);

    m_loose = new Menu(m_textload, "abaddon", 50, sf::Color::Green, sf::Color(0, 128, 0));
    m_loose->setTitle("YOU LOOSE", sf::Vector2i(450, 150));
    m_loose->newButton(RESTART, sf::Vector2i(0, 150));
    m_loose->newButton(EXIT, sf::Vector2i(0, 75));

    initialize();

    m_music.setVolume(50.0);
    m_music.openFromFile("sons/sound_1.ogg");
    m_music.setLoop(1);
    m_music.play();
}

void Level::initialize()
{
    m_file.open(m_file_name, std::ios::in);
    m_animation = 0;

    m_money = 500;
    m_lives = 200;
    m_towers = new TowerManager(m_textload);
    m_status = game_status::wait;
    m_play_save = 0;
    m_thread = new std::thread(&Level::physicsMotor, this);
    //m_thread->detach();
}

void Level::physicsMotor()
{
    sf::Vector2f position;
    std::cout << "!!!!! thread launch !!!!!" << std::endl;
    while (m_status != game_status::loose && m_status != game_status::end && m_done == false)
    {
        int indice[2], oldest = 0;
        indice[0] = 0;
        m_mutex.lock();
        for (unsigned int i(0); i < m_play_save && i < m_waves.size(); ++i)
        {
            if (m_waves[i] != nullptr)
            {
                if (m_waves[i]->isEmpty())
                {
                    --m_play_save;
                    if (!m_waves[i]->next() && m_play_save == 0 && m_waves.size() != 0)
                        ++m_play_save;
                    delete m_waves[i];
                    m_waves.erase(m_waves.begin() + i);
                }
            }
        }
        m_mutex.unlock();
        for (int i(m_towers->getSize() - 1); i >= 0; --i)
        {
            int k(m_waves.size() - 1);
            while (k >= 0)
            {
                m_mutex.lock();
                for (int j(0); j < m_waves[k]->size(); ++j)
                {
                    position = m_waves[k]->getBloonPosition(j);
                    if (position.x >= 0 && position.x <= 900 &&
                       position.y >= 0 && position.y <= 600 &&
                       i < m_towers->getSize())
                    {
                        if (m_waves[k]->isNearOf(j, m_towers->getPosition(i), m_towers->getRange(i)) == true)
                        {
                            if (m_waves[k]->getAdvance(j) > oldest)
                            {
                                oldest = m_waves[k]->getAdvance(j);
                                indice[1] = j;
                                indice[0] = k;
                            }
                        }
                    }
                }
                --k;
                m_mutex.unlock();
            }
            m_mutex.lock();
            if (oldest != 0)
            {
                m_towers->rotateTowards(i, m_waves[indice[0]]->getBloonPosition(indice[1]));
                if (m_waves[indice[0]]->isTouch(indice[1],
                                            m_waves[indice[0]]->getBloonPosition(indice[1]),
                                            m_towers->shoot(i, m_waves[indice[0]]->getBloonPosition(indice[1])),
                                            m_textload,
                                            m_towers->getEffect(i),
                                            m_towers->getNbBall(i)) == true)
                {
                    m_sound.push_back(sf::Sound(m_textload->getBuffer("pop.ogg")));
                    m_sound.back().play();
                }

                m_money += m_waves[indice[0]]->getMoney(indice[1]);
                indice[0] = 0;
                indice[1] = 0;
                oldest = 0;
            }
            m_mutex.unlock();
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }
    std::cout << "!!!!! thread exit !!!!!" << std::endl;
}

Level::~Level()
{
    m_status = game_status::loose;
    m_music.stop();
    destroy();
    m_done = true;
    delete m_pause;
    delete m_win;
    delete m_loose;
    delete m_text_life;
    for (unsigned int i(0); i < m_sound.size(); ++i)
    {
        while (m_sound[i].getStatus() == sf::Sound::Playing)
        {
        }
        m_sound.erase(m_sound.begin() + i);
    }
}

void Level::destroy()
{
    m_file.close();
    m_play_save = 0;
    m_mutex.lock();
    while (m_waves.size() > 0)
    {
        delete m_waves[0];
        m_waves.pop_front();
    }
    m_mutex.unlock();
    m_done = true;
    m_thread->join();
    delete m_thread;
    m_done = false;
    delete m_towers;
    m_thread = nullptr;
}

void Level::load()
{
    if (m_file)
    {
        if (m_file.eof() != true)
        {
            int nb_bloons, type_of_bloon, gap, next_wave=0;
            while (next_wave != -1)
            {
                m_file >> nb_bloons >> gap >> type_of_bloon >> next_wave;
                m_waves.push_back(new Wave(nb_bloons, type_of_bloon, gap, next_wave, "virtual_map.png"));
            }
            m_play_save = 1;
            m_status = game_status::wait;
            m_animation = 0;
        }
        else
        {
            m_status = game_status::win;
        }
    }
    else
        std::cout << "unable to load level ! " << m_file_name << " ! (please contact the developpers)" << std::endl;
}

void Level::changeLevel(std::string file)
{
    m_file_name = file;
    m_file.close();
    m_file.open(m_file_name, std::ios::in);
    m_end = false;
    m_status = game_status::wait;
    m_animation = 0;
}

bool Level::isDone()
{
    return m_done;
}

void Level::close()
{
    m_done = true;
}

void Level::update(sf::RenderWindow *screen, Textureloader* textload)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    int dmg(0);
    unsigned int snd(0);
    if (m_waves.size() == 0)
        load();
    while (snd < m_sound.size())
    {
        if (m_sound[snd].getStatus() == sf::Sound::Stopped)
            m_sound.erase(m_sound.begin() + snd);
        else
            ++snd;
    }
    if (m_status < game_status::wait)
    {
        //std::cout << m_play_save << endl;
        for (unsigned int i(0); i < m_play_save; ++i)
        {
            if (!m_waves[i]->isEmpty())
            {
                dmg = m_waves[i]->update(screen, textload);
                if (dmg > 0)
                {
                    m_sound.push_back(sf::Sound(textload->getBuffer("pop.ogg")));
                    m_sound.back().play();
                }
                m_lives -= dmg;
                if (m_waves[i]->next())
                    m_play_save++;
            }
        }
    }
    else
    {
        if (m_button_play.getGlobalBounds().contains(sf::Mouse::getPosition(*screen).x, sf::Mouse::getPosition(*screen).y))
        {
            if (m_clic)
            {
                m_status = game_status::play_animation;
            }
        }
    }
    if (m_lives < 0)
        m_status = game_status::loose;
    screen->draw(m_interface);
    m_text_life->setSentence(std::to_string(m_lives));
    screen->draw(*m_text_life);
    screen->draw(m_sprite_life);
    if (m_status >= game_status::wait)
        screen->draw(m_button_play);
    m_money = m_towers->update(textload->getMap("virtual_map.png"), screen, textload, m_money, m_delete, m_clic==2);
    if (m_clic == 2)
        m_clic = 0;
}

void Level::forceRunning(sf::RenderWindow *screen, Textureloader* textload)
{
    m_end = false;
    m_status = game_status::end;
    run(screen, textload);
}

void Level::run(sf::RenderWindow *screen, Textureloader* textload)
{
    char status=0;
    while (m_done == false && m_end == false)
    {
        if (m_status != game_status::paused)
            status = m_status;
        while (screen->pollEvent(m_event))
        {
            switch (m_event.type)
            {
                /**/
                case sf::Event::Closed:
                    m_done = true;
                    break;
                    //*/
                case sf::Event::KeyPressed:
                    switch (m_event.key.code)
                    {
                        /*
                        case sf::Keyboard::Escape:
                            m_done = true;
                            break;
                            //*/
                        case sf::Keyboard::Delete:
                            if (!m_delete)
                            {
                                m_delete = true;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch (m_event.key.code)
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
                    break;
            }
        }
        if (m_done == true)
            std::cout << "End of game" << std::endl;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_clic == 1)
        {
            m_clic = 2;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true && m_clic == 0)
        {
            m_clic = 1;
        }
        screen->draw(m_map);
        std::string a;
        switch (m_status)
        {
            case game_status::play_animation:
                buttonAnimation();
                update(screen, textload);
                break;
            case game_status::wait:
            case game_status::normal:
                if (m_button_play.getScale() != sf::Vector2f(1, 1))
                    m_button_play.scale(1/m_button_play.getScale().x, 1/m_button_play.getScale().y);
                update(screen, textload);
                m_delete = false;
                break;
            case game_status::paused:
                a = m_pause->update(screen, m_clic);
                if (a == RESUME)
                {
                    m_status = status;
                    m_clic = 0;
                }
                else if (a == EXIT)
                    m_done = true;
                else if (m_clic == 2)
                    m_clic = 0;
                break;
            case game_status::loose:
                a = m_loose->update(screen, m_clic);
                if (a == RESTART)
                {
                    destroy();
                    initialize();
                    std::cout << "game restarted" << std::endl;
                }
                else if (a == EXIT)
                    m_done = true;
                else if (m_clic == 2)
                    m_clic = 0;
                break;
            case game_status::win:
                m_end = true;
                break;
            case game_status::end:
                a = m_win->update(screen, m_clic);
                if (a == RESTART)
                {
                    destroy();
                    initialize();
                }
                else if (a == EXIT)
                    m_done = true;
                else if (m_clic == 2)
                    m_clic = 0;
                break;
            default:
                std::cout << "Error game status undeclared" << std::endl;
                break;
        }
        screen->display();
        screen->clear();
    }
}

void Level::buttonAnimation()
{
    if (m_button_play.getScale().x >= 1.33f ||
       m_animation == 1)
    {
         m_animation = 1;
         m_button_play.scale(0.95, 0.95);
    }
    if (m_button_play.getScale().x <= 0.33f)
    {
        m_status = game_status::normal;
    }
    if (m_animation != 1)
    {
        m_button_play.scale(1.05, 1.05);
    }
}
