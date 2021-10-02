#include "util.h"
#include <string.h>
#include <mkw/MenuSet.h>
#include <mkw/UI/Scene.h>

extern const char diResNameStr[];

bool isRiivolution()
{
    if (strcmp(diResNameStr, "/dev/do") == 0)
        return true;
    
    return false;
}

bool isTournamentMode()
{
    return MenuSet::sInstance->currentRace.modeFlags &
           MenuSet::RaceSetting::FLAG_TOURNAMENT;
}

