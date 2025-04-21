#include "Player.h"
#include "GameConstants.h"
#include "ResourceManager.h" 

Player::Player()
{
    mTexture = ResourceManager::loadTexture("Resources/Pictures/Rocket.png");
    mPlayerSprite.setTexture(mTexture);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    float randomX = static_cast<float>(std::rand() % static_cast<int>(Screen::WIDTH * 0.6f) + Screen::WIDTH * 0.2f);
    mPlayerSprite.setPosition(randomX, 50.f);

    mEngineDownTexture = ResourceManager::loadTexture("Resources/Pictures/rocket_fire(up).png");
    mEngineDownSprite.setTexture(mEngineDownTexture);
    mEngineDownSprite.setColor(sf::Color(255, 255, 255, 0));

    mEngineLeftTexture = ResourceManager::loadTexture("Resources/Pictures/rocket_fire(left).png");
    mEngineLeftSprite.setTexture(mEngineLeftTexture);
    mEngineLeftSprite.setColor(sf::Color(255, 255, 255, 0));

    mEngineRightTexture = ResourceManager::loadTexture("Resources/Pictures/rocket_fire(right).png");
    mEngineRightSprite.setTexture(mEngineRightTexture);
    mEngineRightSprite.setColor(sf::Color(255, 255, 255, 0));

    mExplosionTexture = ResourceManager::loadTexture("Resources/Pictures/Crash.png");
    mExplosionSprite.setTexture(mExplosionTexture);
    mExplosionSprite.setColor(sf::Color(255, 255, 255, 0));
    mExplosionSprite.setOrigin(mExplosionSprite.getGlobalBounds().width / 2.0f, mExplosionSprite.getGlobalBounds().height / 2.0f);
}

void Player::update(sf::Time deltaTime)
{
    if (isLanded || isCrashed || isMissed) 
    {
        resetHorizontalEngineState();
        resetVerticalThrust();
        updateEngineSpritesVisibility();
        return;
    }

    if (fuel <= 0 && !isOutOfFuel)
    {
        fuel = 0;
        isOutOfFuel = true;
        horizontalThrust = 0.0f;
        verticalThrust = 0.0f;
        outOfFuel(); 
    }

    if (!isOutOfFuel)
    {
        if (horizontalThrust != 0) fuel -= Fuel::CONSUMPTION_RATE_HORIZONTAL * deltaTime.asSeconds();
        if (verticalThrust != 0)  fuel -= Fuel::CONSUMPTION_RATE_VERTICAL * deltaTime.asSeconds();
        if (fuel < 0) fuel = 0;
    }

    float verticalAcceleration = Physics::FREE_FALL_ACCELERATION + verticalThrust;
    velocity.y += verticalAcceleration * deltaTime.asSeconds();
    velocity.x += horizontalThrust * deltaTime.asSeconds();

    mPlayerSprite.move(velocity * deltaTime.asSeconds());
    updateEngineSpritesPositions();
    updateEngineSpritesVisibility();
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(mEngineDownSprite);
    window.draw(mEngineLeftSprite);
    window.draw(mEngineRightSprite);
    window.draw(mPlayerSprite);
}

void Player::drawCrash(sf::RenderWindow& window)
{
    mExplosionSprite.setPosition(mPlayerSprite.getPosition()); 
    mExplosionSprite.setColor(sf::Color::White); 
    window.draw(mExplosionSprite);
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (isLanded || isCrashed || isMissed || isOutOfFuel) return;

    if (key == sf::Keyboard::A)
    {
        applyHorizontalThrust(isPressed, -1);
    }
    if (key == sf::Keyboard::D)
    {
        applyHorizontalThrust(isPressed, 1); 
    }
    if (key == sf::Keyboard::W)
    {
        applyVerticalThrust(isPressed);
    }

    if (!isPressed)
    {
        if (key == sf::Keyboard::A && horizontalThrust < 0) resetHorizontalEngineState();
        if (key == sf::Keyboard::D && horizontalThrust > 0) resetHorizontalEngineState();
        if (key == sf::Keyboard::W && verticalThrust < 0) resetVerticalThrust();
    }
}

void Player::applyVerticalThrust(bool isThrusting)
{
    if (fuel > 0 && isThrusting)
    {
        verticalThrust = -Thrust::VERTICAL_ACCELERATION;
        isEngineDownActive = true;
    }
    else
    {
        verticalThrust = 0.0f;
        isEngineDownActive = false;
    }
}

void Player::applyHorizontalThrust(bool isThrusting, int direction)
{
    if (fuel > 0 && isThrusting)
    {
        horizontalThrust = direction * Thrust::HORIZONTAL_ACCELERATION;
        isEngineLeftActive = (direction == 1);
        isEngineRightActive = (direction == -1);
    }
    else
    {
        resetHorizontalEngineState();
    }
}

void Player::resetHorizontalEngineState()
{
    horizontalThrust = 0.0f;
    isEngineLeftActive = false;
    isEngineRightActive = false;
}

void Player::resetVerticalThrust()
{
    verticalThrust = 0.0f;
    isEngineDownActive = false;
}


void Player::updateEngineSpritesPositions()
{
    sf::FloatRect playerBounds = mPlayerSprite.getGlobalBounds();
    sf::FloatRect downEngineBounds = mEngineDownSprite.getGlobalBounds();
    sf::FloatRect leftEngineBounds = mEngineLeftSprite.getGlobalBounds();
    sf::FloatRect rightEngineBounds = mEngineRightSprite.getGlobalBounds();

    float horizontalCenterOffset = playerBounds.width / 2.0f;
    float verticalBottomOffset = playerBounds.height;
    float verticalCenterEngineOffset = playerBounds.height / 2.0f - leftEngineBounds.height / 2.0f;
    float horizontalEngineWidthOffset = leftEngineBounds.width; 

    mEngineDownSprite.setPosition({ mPlayerSprite.getPosition().x + horizontalCenterOffset - downEngineBounds.width / 2.0f, mPlayerSprite.getPosition().y + verticalBottomOffset });
    mEngineLeftSprite.setPosition({ mPlayerSprite.getPosition().x - horizontalEngineWidthOffset, mPlayerSprite.getPosition().y + verticalCenterEngineOffset });
    mEngineRightSprite.setPosition({ mPlayerSprite.getPosition().x + playerBounds.width, mPlayerSprite.getPosition().y + verticalCenterEngineOffset });
}

void Player::updateEngineSpritesVisibility()
{
    mEngineDownSprite.setColor(isEngineDownActive ? sf::Color::White : sf::Color(255, 255, 255, 0));
    mEngineLeftSprite.setColor(isEngineLeftActive ? sf::Color::White : sf::Color(255, 255, 255, 0));
    mEngineRightSprite.setColor(isEngineRightActive ? sf::Color::White : sf::Color(255, 255, 255, 0));
}

sf::Sprite& Player::getSprite() { return mPlayerSprite; }
sf::Vector2f Player::getPosition() const { return mPlayerSprite.getPosition(); }

void Player::setPosition(const sf::Vector2f& position)
{
    mPlayerSprite.setPosition(position);
    updateEngineSpritesPositions(); 
}

sf::FloatRect Player::getBounds() const { return mPlayerSprite.getGlobalBounds(); }
void Player::landSafely() 
{ 
    isLanded = true; 
}
void Player::landMissed()
{ 
    isMissed = true; 
}
void Player::crash() 
{ 
    isCrashed = true; 
}
void Player::outOfFuel()
{
    isOutOfFuel = true;
    isEngineDownActive = false;  
    isEngineLeftActive = false;
    isEngineRightActive = false;
}