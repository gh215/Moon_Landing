#include "ResourceManager.h" 
#include "GameConstants.h"

sf::Texture ResourceManager::loadTexture(const std::string& filePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load texture file: " + filePath);
    }
    return texture;
}

sf::SoundBuffer ResourceManager::loadSoundBuffer(const std::string& filePath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load sound file: " + filePath);
    }
    return buffer;
}

sf::Font ResourceManager::loadFont(const std::string& filePath)
{
    sf::Font font;
    if (!font.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load font file: " + filePath);
    }
    return font;
}