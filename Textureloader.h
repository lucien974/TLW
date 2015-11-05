#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED

#include "Entity.h"

class Textureloader
{
    public:
        Textureloader(std::string image_folder , std::string buffer_folder , std::string font_folder);
        Textureloader(std::string image_folder);
        ~Textureloader();
        sf::Texture& getTexture(std::string filename);
        sf::SoundBuffer& getBuffer(std::string filename);
        sf::Font& getFont(std::string filename);
        sf::Image& getMap(std::string filename);
        sf::Vector2f getRedPxl(std::string filename);
        void setTextureFolder(std::string folder);
        void setBufferFolder(std::string folder);
        void setFontFolder(std::string folder);
    private:
        std::map< std::string , sf::Texture > m_texture;
        std::map< std::string , sf::Texture >::iterator m_texture_it;
        std::map< std::string , sf::SoundBuffer > m_buffer;
        std::map< std::string , sf::SoundBuffer >::iterator m_buffer_it;
        std::map< std::string , sf::Font > m_font;
        std::map< std::string , sf::Font >::iterator m_font_it;
        std::string m_texture_folder , m_buffer_folder , m_font_folder;
        std::map< std::string , sf::Image > m_map;
        std::map< std::string , sf::Image >::iterator m_map_it;
        bool m_seek;
        sf::Vector2f m_vect;
};

#endif // TEXTURELOADER_H_INCLUDED
