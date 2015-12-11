#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Textureloader
{
    public:
        Textureloader(std::string image_folder, std::string buffer_folder, std::string font_folder);
        Textureloader(std::string image_folder);
        ~Textureloader();
        const sf::Texture& getTexture(std::string filename);
        const sf::SoundBuffer& getBuffer(std::string filename);
        const sf::Font& getFont(std::string filename);
        const sf::Image& getMap(std::string filename);
        const sf::Vector2f getPxlPos(std::string filename, sf::Color color_search, std::string type);
        void setTextureFolder(std::string folder);
        void setBufferFolder(std::string folder);
        void setFontFolder(std::string folder);
        void setForbidPosition(sf::Vector2f origin, std::string file_name, sf::Color color);
        void clearLevel();

    private:
        std::map<std::string, sf::Texture> m_texture;
        std::map<std::string, sf::SoundBuffer> m_buffer;
        std::map<std::string, sf::Font> m_font;
        std::string m_texture_folder, m_buffer_folder, m_font_folder;
        std::map<std::string, sf::Image> m_map;
        std::map<std::string, sf::Vector2f> m_map_pos;
};

#endif // TEXTURELOADER_H_INCLUDED
