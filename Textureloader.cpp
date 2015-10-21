#include "Textureloader.h"

Textureloader::Textureloader(std::string image_folder, std::string buffer_folder, std::string font_folder) :
m_texture_folder(image_folder),
m_buffer_folder(buffer_folder),
m_font_folder(font_folder),
m_seek(false),
m_vect({450, 300})
{
}



Textureloader::Textureloader(std::string image_folder) :
m_texture_folder(image_folder),
m_buffer_folder(""),
m_font_folder(""),
m_seek(false),
m_vect({0, 0})
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
    std::string path;
    path = m_texture_folder + filename;
    m_texture_it = m_texture.find(filename);
    if (m_texture_it != m_texture.end())
    {
        return m_texture_it->second;
    }
    else
    {
        m_texture[filename].loadFromFile(path);
        return m_texture[filename];
    }
}



sf::SoundBuffer& Textureloader::getBuffer(std::string filename)
{
    std::string path;
    path = m_buffer_folder + filename;
    m_buffer_it = m_buffer.find(filename);
    if (m_buffer_it != m_buffer.end())
    {
        return m_buffer_it->second;
    }
    else
    {
        m_buffer[filename].loadFromFile(path);
        return m_buffer[filename];
    }
}



sf::Font& Textureloader::getFont(std::string filename)
{
    std::string path;
    path = m_font_folder + filename;
    m_font_it = m_font.find(filename);
    if (m_font_it != m_font.end())
    {
        return m_font_it->second;
    }
    else
    {
        m_font[filename].loadFromFile(path);
        return m_font[filename];
    }
}



sf::Image& Textureloader::getMap(std::string filename)
{
    std::string path;
    path = m_texture_folder + filename;
    m_map_it = m_map.find(filename);
    if (m_map_it != m_map.end())
    {
        return m_map_it->second;
    }
    else
    {
        m_map[filename].loadFromFile(path);
        return m_map[filename];
    }
}



sf::Vector2f Textureloader::getRedPxl(std::string filename)
{
    if (m_seek == false)
    {
        sf::Color color;
        for (unsigned int za(0); za < getMap(filename).getSize().x; za++)
        {
            for (unsigned int j(0); j < getMap(filename).getSize().y; j++)
            {
                color = getMap(filename).getPixel(za, j);
                if (color.b <= 5 && color.g <= 5 && color.r >= 250)
                {
                    m_vect.x = za;
                    m_vect.y = j;
                    m_seek = true;
                    return m_vect;
                }
            }
        }
    }
    return m_vect;
}
