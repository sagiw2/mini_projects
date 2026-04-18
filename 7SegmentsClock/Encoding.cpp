#include "Encoding.h"


std::array<DigitSegments, 6> SevenSegmentsEncoder::getEncodedSegments(const TimeValue& currentTime)
{
    std::array<DigitSegments, 6> encodedTime;
    auto timeDigits{currentTime.toDigits()};
    for (uint8_t i{0}; i < timeDigits.size(); ++i)
    {
        encodedTime[i] = sevenSegmentEncoder(timeDigits[i]);
    }
    return encodedTime;
}

DigitSegments SevenSegmentsEncoder::sevenSegmentEncoder(int digitToEncode)
{
    std::array<bool, 7> segmentState{};
    switch (digitToEncode)
    {
        case 0:
            segmentState = std::array<bool, 7>{true, true, true, true, true, true, false};
            break;
        case 1:
            segmentState = std::array<bool, 7>{false, true, true, false, false, false, false};
            break;
        case 2:
            segmentState = std::array<bool, 7>{true, true, false, true, true, false, true};
            break;
        case 3:
            segmentState = std::array<bool, 7>{true, true, true, true, false, false, true};
            break;
        case 4:
            segmentState = std::array<bool, 7>{false, true, true, false, false, true, true};
            break;
        case 5:
            segmentState = std::array<bool, 7>{true, false, true, true, false, true, true};
            break;
        case 6:
            segmentState = std::array<bool, 7>{true, false, true, true, true, true, true};
            break;
        case 7:
            segmentState = std::array<bool, 7>{true, true, true, false, false, false, false};
            break;
        case 8:
            segmentState = std::array<bool, 7>{true, true, true, true, true, true, true};
            break;
        case 9:
            segmentState = std::array<bool, 7>{true, true, true, true, false, true, true};
            break;
    }
    return segmentState;
}