#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float FREE_FALL_ACCELERATION = 30.f;
const float MAX_SAFE_LANDING_SPEED = 45.0f;
const int LANDING_ZONE_WIDTH = 100;
const float HORIZONTAL_THRUST_ACCELERATION = 30.0f;
const float VERTICAL_THRUST_ACCELERATION = 45.0f;


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
	sf::RectangleShape mLunarSurface;
	sf::RectangleShape landingZone;
	sf::Font font;
	sf::Text velocityText;
	sf::Text statusText;
	bool mIsLanded = false;
	bool mCrashed = false;
	bool mMissed = false;
	sf::Vector2f velocity = { 0.f, 0.f };
	float rotation = 0.f;
	float verticalThrust = 0.0f; 
	float horizontalThrust = 0.0f; 
};

Game::Game() : mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Lunar Landing")
{
	float startX = static_cast<float>(rand() % 1600);

	try 
	{
		if (!mTexture.loadFromFile("Rocket.png"))
		{
			throw std::runtime_error("Failed to load Rocket texture: Rocket.png");
		}
		mPlayer.setTexture(mTexture);
		mPlayer.setPosition(startX, 50.f);

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
		statusText.setPosition(SCREEN_WIDTH / 2.0f - 150.f, 50.f);

	}
	catch (const std::runtime_error& error) 
	{
		cerr << "Exception caught: " << error.what() << endl;
		exit(1);
	}

	mLunarSurface.setSize(sf::Vector2f(SCREEN_WIDTH * 2.0f, 300.f));
	mLunarSurface.setFillColor(sf::Color::White);
	mLunarSurface.setPosition(-SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 300.f);

	landingZone.setSize(sf::Vector2f(LANDING_ZONE_WIDTH, 20.f));
	landingZone.setFillColor(sf::Color(0, 255, 0, 100));
	landingZone.setPosition(SCREEN_WIDTH / 2.0f - LANDING_ZONE_WIDTH / 2.0f, SCREEN_HEIGHT - 320.f);
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
	if (key == sf::Keyboard::A) horizontalThrust = isPressed ? -HORIZONTAL_THRUST_ACCELERATION : 0.0f;
	if (key == sf::Keyboard::D) horizontalThrust = isPressed ? HORIZONTAL_THRUST_ACCELERATION : 0.0f;
	if (key == sf::Keyboard::W) verticalThrust = isPressed ? -VERTICAL_THRUST_ACCELERATION : 0.0f;
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
	if (mIsLanded || mCrashed || mMissed) return;

	// Вертикальное движение
	float verticalAcceleration = FREE_FALL_ACCELERATION + verticalThrust; 
	velocity.y += verticalAcceleration * deltaTime.asSeconds();

	// Горизонтальное движение
	velocity.x += horizontalThrust * deltaTime.asSeconds();

	mPlayer.move(velocity * deltaTime.asSeconds());
	velocityText.setString("Speed Y: " + to_string(velocity.y) + "\nSpeed X: " + to_string(velocity.x));

	checkLanding();
}

void Game::checkLanding()
{
	sf::FloatRect playerBounds = mPlayer.getGlobalBounds();
	sf::FloatRect moonBounds = mLunarSurface.getGlobalBounds();
	sf::FloatRect landingBounds = landingZone.getGlobalBounds();
	
	if (playerBounds.intersects(moonBounds))
	{
		mPlayer.setPosition(mPlayer.getPosition().x, mLunarSurface.getPosition().y - mTexture.getSize().y); 

		if (velocity.y > MAX_SAFE_LANDING_SPEED)
		{
			cerr << "Crash Landing!" << endl;
			mCrashed = true; 
		}
		else if (velocity.y < MAX_SAFE_LANDING_SPEED && !playerBounds.intersects(landingBounds))
		{
			cerr << "Landed outside landing zone, but safely!" << endl;
			mMissed = true;
		}
		else
		{
			cout << "Landed Successfully!" << endl;
			mIsLanded = true; 
		}
	}
	
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mLunarSurface);
	mWindow.draw(landingZone);
	mWindow.draw(mPlayer);
	mWindow.draw(velocityText);

	if (mIsLanded) 
	{
		statusText.setString("Landed Successfully!");
		mWindow.draw(statusText);
	}
	else if (mCrashed) 
	{
		statusText.setString("Crash Landing!");
		mWindow.draw(statusText);
	}
	else if (mMissed)
	{
		statusText.setString("Landed outside landing zone, but safely!");
		mWindow.draw(statusText);
	}
	mWindow.display();
}