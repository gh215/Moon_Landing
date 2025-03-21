#pragma once
#include "Player.h"
#include "World.h"
#include "UserInterface.h"
#include "GameConstants.h"
#include "SoundManager.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void checkLanding();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::RenderWindow mWindow;
    Player mPlayer;
    World mWorld;
    UserInterface mUI;
    SoundManager mSoundManager; 
    bool explosionSoundPlayed = false; 
};