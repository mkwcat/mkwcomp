#include "CompFile.h"
#include "UI.h"
#include "patch.h"
#include "replay.h"
#include "util.h"
#include <mkw/UI/LayoutUIControl.h>
#include <mkw/UI/Scene.h>

void main()
{
    initMenu();
    initReplayMode();
    initCompFilePatches();

    if (isRiivolution())
        RiivoFS::initialize();
}