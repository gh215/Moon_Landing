#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float GRAVITY = 1.62f;
const float MAX_SAFE_LANDING_SPEED = 12.0f;
const int LANDING_ZONE_WIDTH = 100;
const float THRUST_POWER = 5.0f;
const float ROTATION_SPEED = 50.f;
const float MOVE_SPEED = 200.f;


class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key, bool isPressed);
	void checkLanding();

private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::CircleShape mMoon;
	sf::RectangleShape landingZone;
	sf::Font font;
	sf::Text velocityText;
	bool mIsLanded = false;
	sf::Vector2f velocity = { 0.f, 0.f };
	float rotation = 0.f;
};

Game::Game() : mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Lunar Landing")
{
	float startX = static_cast<float>(rand() % 1600);

	if (!mTexture.loadFromFile("Rocket.png"))
	{
		cerr << "Failed to load Rocket texture" << endl;
		exit(1);
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(startX, 50.f);

	mMoon.setRadius(3000.f);
	mMoon.setPosition(-2000.f, 800.f); 
	mMoon.setFillColor(sf::Color::White);

	landingZone.setSize(sf::Vector2f(LANDING_ZONE_WIDTH, 10));
	landingZone.setFillColor(sf::Color(0, 255, 0, 100));
	landingZone.setPosition(950.f, 790.f);

	if (!font.loadFromFile("Arial.ttf"))
	{
		cerr << "Failed to load font" << endl;
		exit(1);
	}
	velocityText.setFont(font);
	velocityText.setCharacterSize(24);
	velocityText.setFillColor(sf::Color::White);
	velocityText.setPosition(10.f, 10.f);
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

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::A) velocity.x = isPressed ? -MOVE_SPEED : 0.f;
	if (key == sf::Keyboard::D) velocity.x = isPressed ? MOVE_SPEED : 0.f;
	if (key == sf::Keyboard::W && isPressed) velocity.y -= THRUST_POWER;
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

void Game::update(sf::Time deltaTime)
{
	if (mIsLanded) return;

	velocity.y += GRAVITY * deltaTime.asSeconds();
	mPlayer.move(velocity * deltaTime.asSeconds());
	velocityText.setString("Speed: " + to_string(velocity.y));

	checkLanding();
}

void Game::checkLanding()
{
	sf::FloatRect playerBounds = mPlayer.getGlobalBounds();
	sf::FloatRect moonBounds = mMoon.getGlobalBounds();
	sf::FloatRect landingBounds = landingZone.getGlobalBounds();
	
	if (playerBounds.intersects(moonBounds))
	{
		if (velocity.y > MAX_SAFE_LANDING_SPEED || !playerBounds.intersects(landingBounds))
		{
			cerr << "Crash Landing!" << endl;
			exit(1);
		}
		mIsLanded = true;
		velocity = { 0.f, 0.f };
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mMoon);
	mWindow.draw(landingZone);
	mWindow.draw(mPlayer);
	mWindow.draw(velocityText);
	mWindow.display();
}