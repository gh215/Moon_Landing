#include "SoundManager.h"
#include "ResourceManager.h"

SoundManager::SoundManager() : isEngineSoundPlaying(false) {}

SoundManager::~SoundManager()
{
    stopMusic();
    stopEngineSound();
}

void SoundManager::loadMusic(const std::string& filePath)
{
    if (!music.openFromFile(filePath))
    {
        throw std::runtime_error("Failed to load music file: " + filePath);
    }
    music.setLoop(true);
}

void SoundManager::loadEngineSound(const std::string& filePath)
{
    if (!engineSoundBuffer.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load engine sound file: " + filePath);
    }
    engineSound.setBuffer(engineSoundBuffer);
    engineSound.setLoop(true);
}

void SoundManager::loadExplosionSound(const std::string& filePath)
{
    if (!explosionSoundBuffer.loadFromFile(filePath))
    {
        throw std::runtime_error("Failed to load explosion sound file: " + filePath);
    }
    explosionSound.setBuffer(explosionSoundBuffer);
}

void SoundManager::playMusic()
{
    music.play();
}

void SoundManager::stopMusic()
{
    music.stop();
}

void SoundManager::playEngineSound()
{
    if (!isEngineSoundPlaying)
    {
        engineSound.play();
        isEngineSoundPlaying = true;
    }
}

void SoundManager::stopEngineSound()
{
    engineSound.stop();
    isEngineSoundPlaying = false;
}

void SoundManager::playExplosionSound()
{
    explosionSound.play();
}