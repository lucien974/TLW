#include "Textureloader.h"

Textureloader::Textureloader(std::string image_folder, std::string buffer_folder, std::string font_folder) :
m_texture_folder(image_folder),
m_buffer_folder(buffer_folder),
m_font_folder(font_folder)
{
}

Textureloader::Textureloader(std::string image_folder) :
m_texture_folder(image_folder),
m_buffer_folder(""),
m_font_folder("")
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

sf::Texture& Textureloader::getTexture(std::string filename)
{
    std::string a;
    a = m_texture_folder + filename;
    m_texture_it = m_texture.find(filename);
    if (m_texture_it != m_texture.end())
    {
        return m_texture_it->second;
    }
    else
    {
        m_texture[filename].loadFromFile(a);
        return m_texture[filename];
    }
}

sf::SoundBuffer& Textureloader::getBuffer(std::string filename)
{
    std::string b;
    b = m_buffer_folder + filename;
    m_buffer_it = m_buffer.find(filename);
    if (m_buffer_it != m_buffer.end())
    {
        return m_buffer_it->second;
    }
    else
    {
        m_buffer[filename].loadFromFile(b);
        return m_buffer[filename];
    }
}

sf::Font& Textureloader::getFont(std::string filename)
{
    std::string c;
    c = m_font_folder + filename;
    m_font_it = m_font.find(filename);
    if (m_font_it != m_font.end())
    {
        return m_font_it->second;
    }
    else
    {
        m_font[filename].loadFromFile(c);
        return m_font[filename];
    }
}

sf::Image& Textureloader::getMap(std::string filename)
{
    std::string r;
    r = m_texture_folder + filename;
    m_map_it = m_map.find(filename);
    if (m_map_it != m_map.end())
    {
        return m_map_it->second;
    }
    else
    {
        m_map[filename].loadFromFile(r);
        return m_map[filename];
    }
}

sf::Vector2f Textureloader::getPxlPos(std::string filename, sf::Color color_search, string type)
{
    m_map_pos_it = m_map_pos.find(type);
    if (m_map_pos_it != m_map_pos.end())
    {
        return m_map_pos_it->second;
    }
    else
    {
        sf::Color color;
        sf::Vector2f vect;
        for (unsigned int za(0); za < getMap(filename).getSize().x; za++)
        {
            for (unsigned int j(0); j < getMap(filename).getSize().y; j++)
            {
                color = getMap(filename).getPixel(za, j);
                if (color == color_search)
                {
                    vect.x = za;
                    vect.y = j;
                    m_map_pos[type] = vect;
                    return vect;
                }
            }
        }
        cout << "Error pxl of reference not found" << endl;
        return sf::Vector2f(0, 0);
    }
}
