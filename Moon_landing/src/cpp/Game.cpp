#include "World.h"
#include "UserInterface.h"
#include "GameConstants.h"
#include "Game.h"
#include "Player.h"

Game::Game() : mWindow(sf::VideoMode(Screen::WIDTH, Screen::HEIGHT), "Lunar Landing"), mPlayer(), mWorld(), mUI(Fonts::DEFAULT_FONT_FILE)
{
    try 
    {
        mSoundManager.loadMusic("Resources/Sounds/BackMusic.mp3");
        mSoundManager.loadEngineSound("Resources/Sounds/Engine.mp3"); 
        mSoundManager.loadExplosionSound("Resources/Sounds/CrashSFX.mp3"); 
        mSoundManager.playMusic(); 
    }
    catch (const std::runtime_error& error) 
    {
        std::cerr << "Sound loading error: " << error.what() << std::endl;
    }
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > sf::seconds(1.f / 60.f))
        {
            timeSinceLastUpdate -= sf::seconds(1.f / 60.f);
            update(sf::seconds(1.f / 60.f));
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    mPlayer.handleInput(key, isPressed);
}

void Game::update(sf::Time deltaTime)
{
    mPlayer.update(deltaTime);
    mUI.updateVelocityText(mPlayer.getVelocityY(), mPlayer.getVelocityX());
    mUI.updateFuelText(static_cast<int>(mPlayer.getFuel()));

    if (!mPlayer.getIsLanded() && !mPlayer.getIsCrashed() && !mPlayer.getIsMissed() && mPlayer.isEngineActive())
    {
        mSoundManager.playEngineSound();
    }
    else
    {
        mSoundManager.stopEngineSound();
    }

    checkLanding();
}

void Game::checkLanding()
{
    sf::FloatRect playerBounds = mPlayer.getBounds();
    sf::FloatRect moonBounds = mWorld.getLunarSurfaceBounds();
    sf::FloatRect landingBounds = mWorld.getLandingZoneBounds();

    if (playerBounds.intersects(moonBounds))
    {
        mPlayer.setPosition({ mPlayer.getPosition().x, moonBounds.top - playerBounds.height });

        if (mPlayer.getVelocityY() > Physics::MAX_SAFE_LANDING_SPEED)
        {
            std::cerr << "Crash Landing!" << std::endl;
            mPlayer.crash();
            mUI.updateStatusText("Crash Landing!");
            if (!explosionSoundPlayed) 
            { 
                mSoundManager.playExplosionSound();
                explosionSoundPlayed = true;
            }
        }
        else if (mPlayer.getVelocityY() <= Physics::MAX_SAFE_LANDING_SPEED && !playerBounds.intersects(landingBounds))
        {
            std::cerr << "Landed outside landing zone, but safely!" << std::endl;
            mPlayer.landMissed();
            mUI.updateStatusText("Landed outside landing zone, but safely!");
        }
        else
        {
            std::cout << "Landed Successfully!" << std::endl;
            mPlayer.landSafely();
            mUI.updateStatusText("Landed Successfully!");
        }
    } 
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw(mWindow);

    if (mPlayer.getIsCrashed())  mPlayer.drawCrash(mWindow);
    else mPlayer.draw(mWindow);

    mUI.draw(mWindow);
    mWindow.display();
}