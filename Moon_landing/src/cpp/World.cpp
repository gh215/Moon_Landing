#include "World.h"
#include "GameConstants.h"

World::World()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    generateLunarSurface();
    generateLandingZone();
}

void World::drawDebug(sf::RenderWindow& window)
{
    // Рисуем точки поверхности для отладки
    sf::CircleShape point;
    point.setRadius(3.0f);
    point.setFillColor(sf::Color::Red);

    for (const auto& surfacePoint : mSurfacePoints)
    {
        point.setPosition(surfacePoint.x - point.getRadius(), surfacePoint.y - point.getRadius());
        window.draw(point);
    }
}

void World::generateLunarSurface()
{
    // Создаем генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    // Определим количество точек для создания поверхности
    const int pointCount = 20; // Больше точек - больше деталей
    mSurfacePoints.resize(pointCount);

    // Распределение для генерации высоты точек поверхности
    std::uniform_real_distribution<float> heightDist(Screen::HEIGHT - WorldConst::LUNAR_SURFACE_HEIGHT - 50,
        Screen::HEIGHT - WorldConst::LUNAR_SURFACE_HEIGHT + 50);

    // Создаем точки поверхности по всей ширине экрана
    float stepX = static_cast<float>(Screen::WIDTH) / (pointCount - 1);

    for (int i = 0; i < pointCount; ++i)
    {
        float x = i * stepX;
        float y = heightDist(gen);

        // Делаем некоторые участки более плоскими (для потенциальных зон посадки)
        if (i > 0 && i % 5 == 0)
        {
            // Каждую 5-ю точку делаем близкой по высоте к предыдущей
            y = mSurfacePoints[i - 1].y + std::uniform_real_distribution<float>(-10, 10)(gen);
        }

        mSurfacePoints[i] = sf::Vector2f(x, y);
    }

    // Создаем форму для рисования поверхности
    mLunarSurface.setPrimitiveType(sf::TriangleStrip);
    mLunarSurface.resize(pointCount * 2);

    for (int i = 0; i < pointCount; ++i)
    {
        // Верхняя точка (на поверхности)
        mLunarSurface[i * 2].position = mSurfacePoints[i];
        mLunarSurface[i * 2].color = sf::Color::White;

        // Нижняя точка (ниже поверхности для заполнения)
        mLunarSurface[i * 2 + 1].position = sf::Vector2f(mSurfacePoints[i].x, Screen::HEIGHT + 100);
        mLunarSurface[i * 2 + 1].color = sf::Color::White;
    }
}

void World::generateLandingZone()
{
    // Находим самый плоский участок поверхности
    int bestStartIndex = 0;
    float minSlope = std::numeric_limits<float>::max();

    for (size_t i = 0; i < mSurfacePoints.size() - 2; ++i)
    {
        // Рассчитываем "плоскость" участка, смотря на разницу высот между точками
        float slope1 = std::abs(mSurfacePoints[i + 1].y - mSurfacePoints[i].y);
        float slope2 = std::abs(mSurfacePoints[i + 2].y - mSurfacePoints[i + 1].y);
        float totalSlope = slope1 + slope2;

        if (totalSlope < minSlope)
        {
            minSlope = totalSlope;
            bestStartIndex = i;
        }
    }

    // Индекс для начала посадочной зоны
    int landingStartIndex = bestStartIndex;

    // Получаем координаты посадочной зоны
    float landingX = mSurfacePoints[landingStartIndex].x;
    float landingY = mSurfacePoints[landingStartIndex].y;

    // Создаем посадочную зону
    landingZone.setSize(sf::Vector2f(Landing::ZONE_WIDTH, WorldConst::LANDING_ZONE_VERTICAL_OFFSET));
    landingZone.setFillColor(sf::Color(0, 255, 0, 100));
    landingZone.setPosition(landingX, landingY - WorldConst::LANDING_ZONE_VERTICAL_OFFSET);
}

void World::draw(sf::RenderWindow& window)
{
    window.draw(mLunarSurface);
    window.draw(landingZone);
}

sf::FloatRect World::getLunarSurfaceBounds() const
{
    // Для простоты проверки столкновений создаем прямоугольную область, 
    // охватывающую всю поверхность
    return sf::FloatRect(0, mSurfacePoints[0].y - 10, Screen::WIDTH, Screen::HEIGHT);
}

sf::FloatRect World::getLandingZoneBounds() const
{
    return landingZone.getGlobalBounds();
}

// Новый метод для проверки коллизии с неровной поверхностью
bool World::checkCollisionWithSurface(const sf::FloatRect& objectBounds, sf::Vector2f& collisionPoint) const
{
    float objectBottom = objectBounds.top + objectBounds.height;
    float objectCenter = objectBounds.left + objectBounds.width / 2.0f;

    // Находим, между какими точками находится центр объекта
    for (size_t i = 0; i < mSurfacePoints.size() - 1; ++i)
    {
        if (objectCenter >= mSurfacePoints[i].x && objectCenter <= mSurfacePoints[i + 1].x)
        {
            // Интерполируем высоту поверхности в точке центра объекта
            float t = (objectCenter - mSurfacePoints[i].x) / (mSurfacePoints[i + 1].x - mSurfacePoints[i].x);
            float surfaceHeight = mSurfacePoints[i].y * (1 - t) + mSurfacePoints[i + 1].y * t;

            // Проверяем, пересек ли объект поверхность
            if (objectBottom >= surfaceHeight)
            {
                collisionPoint = sf::Vector2f(objectCenter, surfaceHeight);
                return true;
            }
        }
    }

    return false;
}

// Получить массив точек поверхности
const std::vector<sf::Vector2f>& World::getSurfacePoints() const
{
    return mSurfacePoints;
}