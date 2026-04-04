#include "TerminalClockApp.h"
#include <array>
#include <iostream>
#include <thread>


std::array<std::string, 5> TerminalRenderer::renderDigit(const DigitSegments& segmentState)
{
    std::array<std::string, 5> digit{};
    digit[0] = segmentState[static_cast<int>(Segments::A)] ?  " — " : "   ";
    auto f = segmentState[static_cast<int>(Segments::F)] ?  "|" : " ";
    auto b = segmentState[static_cast<int>(Segments::B)] ?  "|" : " ";
    digit[1] = f + std::string(" ") + b;
    digit[2] = segmentState[static_cast<int>(Segments::G)] ?  " — " : "   ";
    auto e = segmentState[static_cast<int>(Segments::E)] ?  "|" : " ";
    auto c = segmentState[static_cast<int>(Segments::C)] ?  "|" : " ";
    digit[3] = e + std::string(" ") + c;
    digit[4] = segmentState[static_cast<int>(Segments::D)] ?  " — " : "   ";

    return digit;
}

std::array<std::string, 5> TerminalRenderer::renderColon()
{
    return std::array<std::string, 5>{" ", ".", " ", ".", " "};
}

void TerminalRenderer::clockRenderer(const std::array<DigitSegments, 6>& encodedTimeVlaue)
{
    std::array<std::string, 5> clockRows{};
    std::string renderedTime{};
    auto colon{renderColon()};
    for (uint8_t i{0}; i < encodedTimeVlaue.size(); ++i)
    {
        auto renderedDigit{renderDigit(encodedTimeVlaue[i])};
        clockRows[0]+= renderedDigit[0];
        clockRows[1]+= renderedDigit[1];
        clockRows[2]+= renderedDigit[2];
        clockRows[3]+= renderedDigit[3];
        clockRows[4]+= renderedDigit[4];
        if (i == 1 || i == 3)
        {
            clockRows[0]+= colon[0];
            clockRows[1]+= colon[1];
            clockRows[2]+= colon[2];
            clockRows[3]+= colon[3];
            clockRows[4]+= colon[4];
        }
    }
    for (int i{0}; i < clockRows.size(); ++i)
    {
        renderedTime += clockRows[i];
        renderedTime += "\n";
    }

    std::cout << renderedTime;
}

void TerminalClockApp::run()
{
    while (true)
    {
        currentTime = systemTime.getCurrentSystemTime();
        if (currentTime.getSeconds() != previousTime.getSeconds())
        {
            renderSystem.clockRenderer(SevenSegmentsEncoder::getEncodedSegments(currentTime));
            previousTime = currentTime;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
