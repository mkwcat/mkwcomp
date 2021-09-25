#pragma once
#include <rvl/types.h>

class RaceTime
{
public:
    virtual ~RaceTime();
    RaceTime();

    u16 minutes;
    u8 seconds;
    u16 milliseconds;
    bool enabled;
    u8 fill;
};