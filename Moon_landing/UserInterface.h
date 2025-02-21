#pragma once
#include "GameConstants.h"

class UserInterface
{
public:
    UserInterface();
    void draw(sf::RenderWindow& window);
    void updateVelocityText(float velocityY, float velocityX);
    void updateFuelText(int fuel);
    void updateStatusText(const std::string& status);
    void resetStatusText(); 

private:
    sf::Font font;
    sf::Text velocityText;
    sf::Text statusText;
    sf::Text fuelText;
};

