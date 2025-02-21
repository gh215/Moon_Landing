#include "World.h"
#include "GameConstants.h"

World::World()
{
    mLunarSurface.setSize(sf::Vector2f(SCREEN_WIDTH * 2.0f, 300.f));
    mLunarSurface.setFillColor(sf::Color::White);
    mLunarSurface.setPosition(-SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 300.f);

    landingZone.setSize(sf::Vector2f(LANDING_ZONE_WIDTH, 20.f));
    landingZone.setFillColor(sf::Color(0, 255, 0, 100));
    landingZone.setPosition(SCREEN_WIDTH / 2.0f - LANDING_ZONE_WIDTH / 2.0f, SCREEN_HEIGHT - 320.f);
}

void World::draw(sf::RenderWindow& window)
{
    window.draw(mLunarSurface);
    window.draw(landingZone);
}

sf::FloatRect World::getLunarSurfaceBounds() const
{
    return mLunarSurface.getGlobalBounds();
}

sf::FloatRect World::getLandingZoneBounds() const
{
    return landingZone.getGlobalBounds();
}