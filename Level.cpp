#include "Level.h"

Level::Level(Textureloader* textload, sf::RenderWindow *screen, std::string file) :
m_money(0),
m_status(game_status::wait),
m_last_status(0),
m_lives(0),
m_play_save(0),
m_clic(0),
m_animation(0),
m_shortcuts(0),
m_done(false),
m_delete(false),
m_end(false),
m_file_name(file),
m_cheat_code(""),
m_thread(nullptr),
m_screen(screen),
m_textload(textload)
{
    m_map.setTexture(m_textload->getTexture("map.png"));

    m_button_play.setTexture(m_textload->getTexture("play.png"));
    m_button_play.setOrigin(m_button_play.getLocalBounds().width/2, m_button_play.getLocalBounds().height/2);
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

    m_pause = new Menu(m_textload, "abaddon", 50, sf::Color::Green, sf::Color(0, 128, 0));
    m_pause->setTitle("PAUSE", sf::Vector2i(450, 50));
    m_pause->newButton(RESUME, sf::Vector2i(0, 150));
    m_pause->newButton(RETURN_TO_MAIN_MENU, sf::Vector2i(0, 75));
    m_pause->newButton(SAVE, sf::Vector2i(0, 75));
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
    m_file.open(m_file_name);
    if (!m_file.is_open())
    {
        throw std::runtime_error("Unable to load level");
    }
    m_animation = 0;

    m_money = 10;
    m_lives = 200;
    m_towers = new TowerManager(m_textload);
    m_status = game_status::wait;
    m_play_save = 0;
    m_thread = new std::thread(&Level::physicsMotor, this);
    //m_thread->detach();
}

void Level::physicsMotor()
{
    /**/
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
        /**/
        for (int i(m_towers->getSize() - 1); i >= 0; --i)
        {
            int k(m_waves.size() - 1);
            while (k >= 0)
            {
                m_mutex.lock();
                for (int j(0); j < m_waves[k]->size(); ++j)
                {
                    position = m_waves[k]->getBloonPosition(j);
                    if (position.x >= 0 && position.x <= 775 &&
                       position.y >= 74 && position.y <= 530 &&
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
        //*/
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
    if (m_file.is_open())
    {
        int nb_bloons, type_of_bloon, gap, next_wave=0;
        char firstChar;

        while (next_wave != -1 && !m_file.eof())
        {
            // Checking if the first character of the line is really a digit
            firstChar = m_file.peek();
            if (std::isdigit(firstChar))
            {
                m_file >> nb_bloons >> gap >> type_of_bloon >> next_wave;
                m_waves.push_back(new Wave(nb_bloons, type_of_bloon, gap, next_wave, "virtual_map.png"));
            }

            // Seeks the next line
            m_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        m_play_save = 1;
        m_status = game_status::wait;
        m_animation = 0;
    }
    else
    {
        std::stringstream error;
        error << "Unable to load level " << m_file_name << " ! (please contact the developpers)";
        throw std::runtime_error(error.str());
    }
    if (m_file.eof() == true && m_waves.size() == 0)
    {
        m_status = game_status::win;
    }
}

void Level::changeLevel(std::string file)
{
    m_file_name = file;
    m_file.close();
    m_file.open(m_file_name, std::ios::in);
    m_end = false;
    m_status = game_status::wait;
    m_animation = 0;
    m_textload->clearLevel();
    m_towers->clear();
    m_button_play.setPosition(m_textload->getPxlPos("virtual_map.png", sf::Color(255, 0, 128), BUTTON).x - 15,
                              m_textload->getPxlPos("virtual_map.png", sf::Color(255, 0, 128), BUTTON).y - 15);
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
    m_mutex.lock();
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
    if (m_status >= game_status::wait)
        screen->draw(m_button_play);
    m_money = m_towers->update(textload->getMap("virtual_map.png"), screen, m_money, m_delete, &m_clic);
    m_towers->shortcuts(m_shortcuts, m_money);
    m_shortcuts = 0b0;
    /*
    if (m_clic == 2)
        m_clic = 0;
        //*/
    if (m_status < game_status::wait)
    {
        //std::cout << m_play_save << endl;
        for (unsigned int i(0); i < m_play_save && i < m_waves.size(); ++i)
        {
            if (!m_waves[i]->isEmpty())
            {
                dmg = m_waves[i]->update(screen, textload);
                if (dmg > 0)
                {
                    m_sound.push_back(sf::Sound(textload->getBuffer("pop.ogg")));
                    m_sound.back().play();
                }
                if (static_cast<unsigned int>(dmg) < m_lives)
                    m_lives -= dmg;
                else
                    m_status = game_status::loose;
                if (m_waves[i]->next())
                    m_play_save++;
            }
        }
        //std::cout << m_waves.size() << std::endl;
    }
    else
    {
        if (m_button_play.getGlobalBounds().contains(sf::Mouse::getPosition(*screen).x, sf::Mouse::getPosition(*screen).y))
        {
            if (m_clic == 2)
            {
                m_status = game_status::play_animation;
            }
        }
    }
    screen->draw(m_interface);
    m_towers->drawMoney(screen, m_money);
    m_text_life->setSentence(std::to_string(m_lives));
    screen->draw(*m_text_life);
    screen->draw(m_sprite_life);
    if (m_clic == 2)
        m_clic = 0;
    m_mutex.unlock();
}

void Level::forceRunning(sf::RenderWindow *screen, Textureloader* textload)
{
    m_end = false;
    m_status = game_status::end;
    run(screen, textload);
}

bool Level::run(sf::RenderWindow *screen, Textureloader* textload)
{
    while (m_done == false && m_end == false)
    {
        if (m_status != game_status::paused)
            m_last_status = m_status;
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
                        case sf::Keyboard::Numpad6:
                            m_shortcuts = 0b1;
                            break;
                        case sf::Keyboard::Numpad2:
                            m_shortcuts = 0b10;
                            break;
                        case sf::Keyboard::Numpad4:
                            m_shortcuts = 0b100;
                            break;
                        case sf::Keyboard::Numpad8:
                            m_shortcuts = 0b1000;
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
                case sf::Event::TextEntered:
                    if (m_event.text.unicode < 128)
                    {
                        if (static_cast<int>(m_event.text.unicode) == 13)
                        {
                            if (m_cheat_code == "money.upgrade")
                                m_money += MONEY_UP;
                            else if (m_cheat_code == "lives.upgrade")
                                m_lives += LIFE_UP;
                            m_cheat_code.clear();
                        }
                        else
                            m_cheat_code.push_back(m_event.text.unicode);
                    }
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
                    m_status = m_last_status;
                    m_clic = 0;
                }
                else if (a == EXIT)
                    m_done = true;
                else if (a == RETURN_TO_MAIN_MENU)
                {
                    return true;
                }
                else if (a == SAVE)
                    save();
                else if (m_clic == 2)
                    m_clic = 0;
                break;
            case game_status::loose:
                a = m_loose->update(screen, m_clic);
                if (a == RESTART)
                {
                    m_towers->clear();
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
                    m_towers->clear();
                    destroy();
                    initialize();
                }
                else if (a == EXIT)
                    m_done = true;
                else if (m_clic == 2)
                    m_clic = 0;
                break;
            default:
                throw std::runtime_error("Error game status undefined");
                break;
        }
        screen->display();
        screen->clear();
    }
    return false;
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

void Level::save()
{
    std::ifstream save;
    save.open("save/save.txt", std::ios::out);

}
