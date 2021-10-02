#pragma once
#include <rvl/types.h>

bool isRiivolution();

template <class T> static inline u32 indexInArray(T* array, T* entry)
{
    return (reinterpret_cast<u32>(entry) - reinterpret_cast<u32>(array)) /
           sizeof(T);
}

bool isTournamentMode();