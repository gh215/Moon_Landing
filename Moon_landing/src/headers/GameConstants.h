#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>

using namespace std;


enum class PlayerState
{
    Playing,
    LandedSafely,
    LandedMissed,
    Crashed,
    OutOfFuel
};

namespace WorldConst
{
    const float LUNAR_SURFACE_HEIGHT = 300.f;
    const float LANDING_ZONE_VERTICAL_OFFSET = 20.f; 
}

namespace Fonts
{
    const std::string DEFAULT_FONT_FILE = "Resources/Fonts/Arial.ttf";
}

namespace Screen
{
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
}

namespace Physics
{
    const float FREE_FALL_ACCELERATION = 30.f;
    const float MAX_SAFE_LANDING_SPEED = 45.0f;
}

namespace Landing
{
    const int ZONE_WIDTH = 100;
}

namespace Thrust
{
    const float HORIZONTAL_ACCELERATION = 30.0f;
    const float VERTICAL_ACCELERATION = 45.0f;
}

namespace Fuel
{
    const float INITIAL = 300.0f;
    const float CONSUMPTION_RATE_HORIZONTAL = 10.0f;
    const float CONSUMPTION_RATE_VERTICAL = 15.0f;
}