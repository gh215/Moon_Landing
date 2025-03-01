#pragma once
#include "GameConstants.h"

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void loadMusic(const std::string& filePath);
    void loadEngineSound(const std::string& filePath);
    void loadExplosionSound(const std::string& filePath);

    void playMusic();
    void stopMusic();
    void playEngineSound();
    void stopEngineSound();
    void playExplosionSound();

private:
    sf::Music music;
    sf::Sound engineSound;
    sf::Sound explosionSound;
    sf::SoundBuffer engineSoundBuffer;    
    sf::SoundBuffer explosionSoundBuffer; 
    bool isEngineSoundPlaying;
};