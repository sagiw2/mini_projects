#pragma once

#include <SFML/Graphics.hpp>
#include "Encoding.h"


inline sf::Color ON_COLOR{255,38,38};
inline sf::Color OFF_COLOR{255,38,38,15};
inline sf::Vector2f SEGMENT_SIZE{75.f, 7.5f};
inline sf::Vector2f COLON_SIZE{15.f, 15.f};

class DigitDisplay
{
private:
    std::array<sf::RectangleShape, 7> segments;

public:
    DigitDisplay();

    void setPosition(sf::Vector2f digitCenter);
    void setState(const DigitSegments& encodedTimeVlaue);
    void draw(sf::RenderTarget& target) const;
};

class ColonDispaly
{
private:
    std::array<sf::RectangleShape, 2> colon;
public:
    ColonDispaly();

    void setPosition(sf::Vector2f newPosition);
    void draw(sf::RenderTarget& target) const;
};

class ClockDisplay
{
private:
    std::array<DigitDisplay, 6> digits;
    std::array<ColonDispaly, 2> colons;
public:
    ClockDisplay(sf::Vector2u windowSize);

    void calculateElementsPosition(sf::Vector2u windowSize);

    void setState(const std::array<DigitSegments, 6>& encodedTimeVlaue);

    void draw(sf::RenderTarget& target) const;
};
