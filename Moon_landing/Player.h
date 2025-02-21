#pragma once
#include "GameConstants.h" 

class Player
{
public:
    Player();
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    void drawCrash(sf::RenderWindow& window); 
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void resetVerticalThrust();

    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    sf::FloatRect getBounds() const;

    float getVelocityY() const { return velocity.y; }
    float getVelocityX() const { return velocity.x; }
    float getFuel() const { return fuel; }
    bool getIsLanded() const { return isLanded; }
    bool getIsCrashed() const { return isCrashed; }
    bool getIsMissed() const { return isMissed; }
    bool getIsOutOfFuel() const { return isOutOfFuel; }

    void landSafely();
    void landMissed();
    void crash();
    void outOfFuel();

private:
    sf::Texture mTexture;
    sf::Sprite mPlayerSprite;
    sf::Texture mEngineDownTexture;
    sf::Sprite mEngineDownSprite;
    sf::Texture mEngineLeftTexture;
    sf::Sprite mEngineLeftSprite;
    sf::Texture mEngineRightTexture;
    sf::Sprite mEngineRightSprite;
    sf::Texture mExplosionTexture;
    sf::Sprite mExplosionSprite;

    sf::Vector2f velocity = { 0.f, 0.f };
    float verticalThrust = 0.0f;
    float horizontalThrust = 0.0f;
    float fuel = INITIAL_FUEL;
    bool isEngineDownActive = false;
    bool isEngineLeftActive = false;
    bool isEngineRightActive = false;
    bool isLanded = false;
    bool isCrashed = false;
    bool isMissed = false;
    bool isOutOfFuel = false;

    void updateEngineSpritesPositions();
    void updateEngineSpritesVisibility();
    void applyVerticalThrust(bool isThrusting);
    void applyHorizontalThrust(bool isThrusting, int direction); 
    void resetHorizontalEngineState();
};
