#include "Display.h"
#include "Encoding.h"


DigitDisplay::DigitDisplay()
{
    for (auto& rec : segments)
    {
        rec.setOrigin({0.5f, 0.5f});
        rec.setSize(SEGMENT_SIZE);
        rec.setFillColor(OFF_COLOR);
    }
    segments[static_cast<int>(Segments::B)].setRotation(90.f);
    segments[static_cast<int>(Segments::C)].setRotation(90.f);
    segments[static_cast<int>(Segments::E)].setRotation(90.f);
    segments[static_cast<int>(Segments::F)].setRotation(90.f);
}

void DigitDisplay::setPosition(sf::Vector2f digitCenter)
{
    float L = SEGMENT_SIZE.x; // length
    float T = SEGMENT_SIZE.y; // thickness

    segments[static_cast<int>(Segments::A)].setPosition(digitCenter.x, digitCenter.y - 1.2*L);
    segments[static_cast<int>(Segments::G)].setPosition(digitCenter.x, digitCenter.y);
    segments[static_cast<int>(Segments::D)].setPosition(digitCenter.x, digitCenter.y + 1.2*L);

    segments[static_cast<int>(Segments::F)].setPosition(digitCenter.x - T*0.5, digitCenter.y - L*1.05);
    segments[static_cast<int>(Segments::B)].setPosition(digitCenter.x + L + T*1.2, digitCenter.y - L*1.05);

    segments[static_cast<int>(Segments::C)].setPosition(digitCenter.x + L + T*1.2, digitCenter.y + T*1.5);
    segments[static_cast<int>(Segments::E)].setPosition(digitCenter.x - T*0.5, digitCenter.y + T*1.5);
}

void DigitDisplay::setState(const DigitSegments& encodedTimeVlaue)
{
    for (int i{0}; i < encodedTimeVlaue.size(); ++i)
    {
        if (encodedTimeVlaue[i] == true)
            segments[i].setFillColor(ON_COLOR);
        else
            segments[i].setFillColor(OFF_COLOR);
    }
}

void DigitDisplay::draw(sf::RenderTarget& target) const
{
    for (const auto& segment : segments)
        target.draw(segment);
}

ColonDispaly::ColonDispaly()
{
    for (auto& rec : colon)
    {
        rec.setOrigin({0.5f, 0.5f});
        rec.setSize(COLON_SIZE);
        rec.setFillColor(ON_COLOR);
    }
}

void ColonDispaly::setPosition(sf::Vector2f newPosition)
{
    colon[0].setPosition({newPosition.x, newPosition.y - COLON_SIZE.y*2});
    colon[1].setPosition({newPosition.x, newPosition.y + COLON_SIZE.y*2});
}

void ColonDispaly::draw(sf::RenderTarget& target) const
{
    for (const auto& rec : colon)
        target.draw(rec);
}

ClockDisplay::ClockDisplay(sf::Vector2u windowSize)
{
    calculateElementsPosition(windowSize);
}

void ClockDisplay::calculateElementsPosition(sf::Vector2u windowSize)
{
    // will calcualte and set each digit position, size and initial state
    unsigned int windowCenterX = windowSize.y/2;
    float digitSize{SEGMENT_SIZE.x + 2*SEGMENT_SIZE.y};
    float halfDigitSize{digitSize/2};
    float gapW{(windowSize.x - 6*digitSize)/9};

    digits[0].setPosition({0.7f*halfDigitSize, static_cast<float>(windowCenterX)});
    digits[1].setPosition({0.7f*gapW + digitSize + halfDigitSize, static_cast<float>(windowCenterX)});

    colons[0].setPosition({2.7f*gapW + 2*digitSize, static_cast<float>(windowCenterX)});

    digits[2].setPosition({2.7f*gapW + 2*digitSize + halfDigitSize, static_cast<float>(windowCenterX)});
    digits[3].setPosition({3.7f*gapW + 3*digitSize + halfDigitSize, static_cast<float>(windowCenterX)});

    colons[1].setPosition({5.7f*gapW + 4*digitSize, static_cast<float>(windowCenterX)});

    digits[4].setPosition({5.7f*gapW + 4*digitSize + halfDigitSize, static_cast<float>(windowCenterX)});
    digits[5].setPosition({6.7f*gapW + 5*digitSize + halfDigitSize, static_cast<float>(windowCenterX)});
}

void ClockDisplay::setState(const std::array<DigitSegments, 6>& encodedTimeVlaue)
{
    for (int i{0}; i < encodedTimeVlaue.size(); ++i)
    {
        digits[i].setState(encodedTimeVlaue[i]);
    }
}

void ClockDisplay::draw(sf::RenderTarget& target) const
{
    // call display for each digit and colon
    for (const auto& colon : colons)
        colon.draw(target);
    for (const auto& digit : digits)
        digit.draw(target);

}
