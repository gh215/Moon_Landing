#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdexcept>

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float FREE_FALL_ACCELERATION = 30.f;
const float MAX_SAFE_LANDING_SPEED = 45.0f;
const int LANDING_ZONE_WIDTH = 100;
const float HORIZONTAL_THRUST_ACCELERATION = 30.0f;
const float VERTICAL_THRUST_ACCELERATION = 45.0f;
const float INITIAL_FUEL = 300.0f;
const float FUEL_CONSUMPTION_RATE_HORIZONTAL = 10.0f;
const float FUEL_CONSUMPTION_RATE_VERTICAL = 15.0f;