#pragma once
#include "MiiData.h"
#include "RaceTime.h"
#include <rvl/types.h>

struct LeaderboardEntry {
    MiiData mii; // size 0x4A
    u16 miiChecksum; // crc16

    RaceTime time; // at 0x4C

    int characterId;
    int vehicleId;
    int controllerId;
};