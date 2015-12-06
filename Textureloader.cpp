#include "Textureloader.h"

Textureloader::Textureloader(std::string image_folder, std::string buffer_folder, std::string font_folder) :
m_texture_folder(image_folder),
m_buffer_folder(buffer_folder),
m_font_folder(font_folder)
{
}

Textureloader::Textureloader(std::string image_folder) :
Textureloader(image_folder, {}, {})
{
}

Textureloader::~Textureloader()
{
}

void Textureloader::setTextureFolder(std::string folder)
{
    m_texture_folder = folder;
}

void Textureloader::setBufferFolder(std::string folder)
{
    m_buffer_folder = folder;
}

void Textureloader::setFontFolder(std::string folder)
{
    m_font_folder = folder;
}

const sf::Texture& Textureloader::getTexture(std::string filename)
{
    if (m_texture.find(filename) != m_texture.end())
    {
        return m_texture[filename];
    }
    else
    {
        m_texture[filename].loadFromFile(m_texture_folder + filename);
        return m_texture[filename];
    }
}

const sf::SoundBuffer& Textureloader::getBuffer(std::string filename)
{
    if (m_buffer.find(filename) != m_buffer.end())
    {
        return m_buffer[filename];
    }
    else
    {
        m_buffer[filename].loadFromFile(m_buffer_folder + filename);
        return m_buffer[filename];
    }
}

const sf::Font& Textureloader::getFont(std::string filename)
{
    if (m_font.find(filename) != m_font.end())
    {
        return m_font[filename];
    }
    else
    {
        m_font[filename].loadFromFile(m_font_folder + filename);
        return m_font[filename];
    }
}

const sf::Image& Textureloader::getMap(std::string filename)
{
    if (m_map.find(filename) != m_map.end())
    {
        return m_map[filename];
    }
    else
    {
        m_map[filename].loadFromFile(m_texture_folder + filename);
        return m_map[filename];
    }
}

const sf::Vector2f Textureloader::getPxlPos(std::string filename, sf::Color color_search, std::string type)
{
    if (m_map_pos.find(type) != m_map_pos.end())
    {
        return m_map_pos[type];
    }
    else
    {
        for (unsigned int i(0); i < getMap(filename).getSize().x; i++)
        {
            for (unsigned int j(0); j < getMap(filename).getSize().y; j++)
            {
                if (getMap(filename).getPixel(i, j) == color_search)
                {
                    m_map_pos[type].x = i;
                    m_map_pos[type].y = j;
                    return m_map_pos[type];
                }
            }
        }
        std::cout << "Error pxl of reference not found" << std::endl;
        return sf::Vector2f(0, 0);
    }
}

void Textureloader::setForbidPosition(sf::Vector2f origin, std::string file_name, sf::Color color)
{
    float gap(15);
    if (m_map.find(file_name) == m_map.end())
        std::cout << "map doesn't exist" << std::endl;
    else
    {
        for (auto i(origin.x - 40 - gap); i < origin.x + 40 - gap; ++i)
        {
            for (int j(origin.y - 40 - gap); j < origin.y + 40 - gap; ++j)
            {
                if (i > 0 && i < 900 && j > 0 && j < 600)
                {
                    if (m_map[file_name].getPixel(i, j) == sf::Color(0, 0, 0) || m_map[file_name].getPixel(i, j) == sf::Color(0, 128, 128))
                        m_map[file_name].setPixel(i, j, color);
                }
            }
        }
    }
}

void Textureloader::clearLevel()
{
    for (auto &key : m_texture)
    {
        switch (key.first[0])
        {
            case 't':
                m_texture[key.first].loadFromFile(m_texture_folder + "/" + key.first);
                break;
            case 'm':
                m_texture[key.first].loadFromFile(m_texture_folder + key.first);
                break;
            case 'p':
                m_texture[key.first].loadFromFile(m_texture_folder + "/" + key.first);
                break;
            default:
                break;
        }
    }
    if (m_map.find("virtual_map.png") != m_map.end())
    {
        m_map.erase(m_map.find("virtual_map.png"));
        if (m_map["virtual_map.png"].loadFromFile(m_texture_folder + "virtual_map.png"))
        {
            m_map_pos.clear();
        }
        else
            std::cout << "map not found" << std::endl;
    }
    else
        std::cout << "virtual_map " << m_texture_folder + "virtual_map.png not found" << std::endl;
}
