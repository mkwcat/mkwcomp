#pragma once
#include <rvl/types.h>
#include "GhostData.h"

class SaveDataManager
{
public:
    static SaveDataManager* sInstance;
    SaveDataManager();
    ~SaveDataManager();

    u8 fill[0x14];
    void* m_rksys;
    RKG::File* m_rkgFile;
    u8 fill2[0x28008 - 0x1C];
};