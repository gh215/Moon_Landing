#pragma once
#include "GameConstants.h"

class World
{
public:
    World();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getLunarSurfaceBounds() const;
    sf::FloatRect getLandingZoneBounds() const;

private:
    sf::RectangleShape mLunarSurface;
    sf::RectangleShape landingZone;
};