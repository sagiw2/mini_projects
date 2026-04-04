#include "SFMLClockApp.h"
#include <thread>

bool SFMLRenderer::isOpen() const
{
    return window.isOpen();
}

void SFMLRenderer::processEvents(bool &running)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            running = false;
            window.close();
        }
    }
}

void SFMLRenderer::display()
{
    window.clear(sf::Color::Black);
    clockDisplay.draw(window);
    window.display();
}

void SFMLRenderer::update(const std::array<DigitSegments, 6>& segmentsState)
{
    clockDisplay.setState(segmentsState);
}

void SFMLClockApp::run()
{
    bool running{true};
    while (running && renderSystem.isOpen())
    {
        currentTime = systemTime.getCurrentSystemTime();
        if (previousTime < currentTime)
        {
            renderSystem.update(SevenSegmentsEncoder::getEncodedSegments(currentTime));
            previousTime = currentTime;
        }

        renderSystem.processEvents(running);
        renderSystem.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}