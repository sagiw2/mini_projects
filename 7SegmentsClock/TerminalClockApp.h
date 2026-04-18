#pragma once

#include "ClockApp.h"
#include <string>
#include "Encoding.h"


class TerminalRenderer
{
private:
    std::array<std::string, 5> renderDigit(const DigitSegments& segmentState);
    std::array<std::string, 5> renderColon();

public:
    void clockRenderer(const std::array<DigitSegments, 6>& encodedTimeVlaue);
};

class TerminalClockApp: public ClockApp
{
private:
    TerminalRenderer renderSystem;

public:
    void run() override;
};