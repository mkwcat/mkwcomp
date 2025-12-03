#pragma once
#include <rvl/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void OSSleepTicks(u64 ticks);
void OSReport(const char* format, ...);

#ifdef __cplusplus
}
#endif