#include "Textureloader.h"

Textureloader::Textureloader(std::string image_folder , std::string buffer_folder , std::string font_folder)
{
    m_texture_folder = image_folder;
    m_buffer_folder = buffer_folder;
    m_font_folder = font_folder;
    m_seek = false;
    m_vect.x = 450;
    m_vect.y = 300;
}

Textureloader::Textureloader(std::string image_folder)
{
    m_texture_folder = image_folder;
    m_buffer_folder = "";
    m_font_folder = "";
    m_seek = false;
    m_vect.x = 0;
    m_vect.y = 0;
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

sf::Texture& Textureloader::Gettexture(std::string filename)
{
    std::string a;
    a = m_texture_folder + filename;
    m_texture_it = m_texture.find(filename);
    if(m_texture_it != m_texture.end())
    {
        return m_texture_it->second;
    }
    else
    {
        m_texture[filename].loadFromFile(a);
        return m_texture[filename];
    }
}

sf::SoundBuffer& Textureloader::Getbuffer(std::string filename)
{
    std::string b;
    b = m_buffer_folder + filename;
    m_buffer_it = m_buffer.find(filename);
    if(m_buffer_it != m_buffer.end())
    {
        return m_buffer_it->second;
    }
    else
    {
        m_buffer[filename].loadFromFile(b);
        return m_buffer[filename];
    }
}

sf::Font& Textureloader::Getfont(std::string filename)
{
    std::string c;
    c = m_font_folder + filename;
    m_font_it = m_font.find(filename);
    if(m_font_it != m_font.end())
    {
        return m_font_it->second;
    }
    else
    {
        m_font[filename].loadFromFile(c);
        return m_font[filename];
    }
}

sf::Image& Textureloader::Getmap(std::string filename)
{
    std::string r;
    r = m_texture_folder + filename;
    m_map_it = m_map.find(filename);
    if(m_map_it != m_map.end())
    {
        return m_map_it->second;
    }
    else
    {
        m_map[filename].loadFromFile(r);
        return m_map[filename];
    }
}

sf::Vector2f Textureloader::getRedPxl(std::string filename)
{
    if(m_seek == false)
    {
        sf::Color color;
        for( unsigned int za(0) ; za < Getmap(filename).getSize().x ; za++ )
        {
            for( unsigned int j(0) ; j < Getmap(filename).getSize().y ; j++ )
            {
                color = Getmap(filename).getPixel(za,j);
                if(color.b <= 5 && color.g <= 5 && color.r >= 250)
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
