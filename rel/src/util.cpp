#include "util.h"
#include <string.h>

extern const char diResNameStr[];

bool isRiivolution()
{
    if (strcmp(diResNameStr, "/dev/do") == 0)
        return true;
    
    return false;
}