#pragma once
#include "GameConstants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager
{
public:
    static sf::Texture loadTexture(const std::string& filePath);
    static sf::SoundBuffer loadSoundBuffer(const std::string& filePath);
    static sf::Font loadFont(const std::string& filePath);
};