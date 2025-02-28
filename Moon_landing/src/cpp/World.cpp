#include "World.h"
#include "GameConstants.h"

World::World()
{
    mLunarSurface.setSize(sf::Vector2f(Screen::WIDTH * 2.0f, WorldConst::LUNAR_SURFACE_HEIGHT)); // Используем WorldConst::LUNAR_SURFACE_HEIGHT
    mLunarSurface.setFillColor(sf::Color::White);
    mLunarSurface.setPosition(-Screen::WIDTH / 2.0f, Screen::HEIGHT - WorldConst::LUNAR_SURFACE_HEIGHT); // Используем WorldConst::LUNAR_SURFACE_HEIGHT

    landingZone.setSize(sf::Vector2f(Landing::ZONE_WIDTH, WorldConst::LANDING_ZONE_VERTICAL_OFFSET)); // Используем WorldConst::LANDING_ZONE_VERTICAL_OFFSET
    landingZone.setFillColor(sf::Color(0, 255, 0, 100));
    landingZone.setPosition(Screen::WIDTH / 2.0f - Landing::ZONE_WIDTH / 2.0f, Screen::HEIGHT - WorldConst::LUNAR_SURFACE_HEIGHT - WorldConst::LANDING_ZONE_VERTICAL_OFFSET); // Используем WorldConst::LUNAR_SURFACE_HEIGHT и WorldConst::LANDING_ZONE_VERTICAL_OFFSET
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