#pragma once
#include "Time.h"

using DigitSegments = std::array<bool, 7>;
enum class Segments {A, B, C, D, E, F, G};

class SevenSegmentsEncoder
{
public:
    static std::array<DigitSegments, 6> getEncodedSegments(const TimeValue& currentTime);

private:
    static DigitSegments sevenSegmentEncoder(int digitToEncode);
};