#include "UserInterface.h"

UserInterface::UserInterface()
{
    if (!font.loadFromFile("Arial.ttf"))
    {
        throw std::runtime_error("Failed to load font: Arial.ttf");
    }

    velocityText.setFont(font);
    velocityText.setCharacterSize(24);
    velocityText.setFillColor(sf::Color::White);
    velocityText.setPosition(10.f, 10.f);

    statusText.setFont(font);
    statusText.setCharacterSize(30);
    statusText.setFillColor(sf::Color::Yellow);
    statusText.setPosition(1920 / 2.0f - 150.f, 50.f);
    statusText.setString(""); 

    fuelText.setFont(font);
    fuelText.setCharacterSize(24);
    fuelText.setFillColor(sf::Color::White);
    fuelText.setPosition(10.f, 60.f);
}

void UserInterface::draw(sf::RenderWindow& window)
{
    window.draw(velocityText);
    window.draw(statusText);
    window.draw(fuelText);
}

void UserInterface::updateVelocityText(float velocityY, float velocityX) 
{ 
    velocityText.setString("Speed Y: "  + std::to_string(velocityY) + "\nSpeed X: " + std::to_string(velocityX)); 
}
void UserInterface::updateFuelText(int fuel) { fuelText.setString("Fuel: " + std::to_string(fuel)); }
void UserInterface::updateStatusText(const std::string& status) { statusText.setString(status); }
void UserInterface::resetStatusText() { statusText.setString(""); }