#pragma once
#include "GameConstants.h"

class World
{
public:
    World();

    void draw(sf::RenderWindow& window);
    sf::FloatRect getLunarSurfaceBounds() const;
    sf::FloatRect getLandingZoneBounds() const;

    bool checkCollisionWithSurface(const sf::FloatRect& objectBounds, sf::Vector2f& collisionPoint) const;
    const std::vector<sf::Vector2f>& getSurfacePoints() const;
    void drawDebug(sf::RenderWindow& window);

private:
    void generateLunarSurface();
    void generateLandingZone();

    sf::VertexArray mLunarSurface;      
    std::vector<sf::Vector2f> mSurfacePoints;  
    sf::RectangleShape landingZone;   
};