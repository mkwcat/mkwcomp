#include "CompFile.h"
#include "UI.h"
#include "file.h"
#include "replay.h"
#include "util.h"

void main()
{
    initMenu();
    initReplayMode();
    initCompFilePatches();

    if (isRiivolution())
        RiivoFS::initialize();
}