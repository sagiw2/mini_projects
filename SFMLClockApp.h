#pragma once

#include "ClockApp.h"
#include "Display.h"


class SFMLRenderer
{
private:
    sf::RenderWindow window;
    ClockDisplay clockDisplay;

public:
    SFMLRenderer() : window(sf::VideoMode(800, 600), "ClockApp"), clockDisplay(window.getSize())
    {
        window.setFramerateLimit(60);
    }

    bool isOpen() const;

    void processEvents(bool &running);

    void display();

    void update(const std::array<DigitSegments, 6>& segmentsState);

};

class SFMLClockApp: public ClockApp
{
private:
    SFMLRenderer renderSystem;

public:
    void run() override;
};