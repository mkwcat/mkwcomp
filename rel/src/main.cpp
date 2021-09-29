#include "competition.h"
#include "ui.h"
#include <mkw/UI/LayoutUIControl.h>
#include <mkw/UI/Scene.h>
#include <rvl/cache.h>
#include <rvl/types.h>

namespace BranchType
{
enum E { B, BL };
}

template <int N> struct Instruction {
    void flush()
    {
        const u32 cacheLineAddr = reinterpret_cast<u32>(m_instr) & ~31;
        const u32 cacheLineEnd =
            (reinterpret_cast<u32>(m_instr + N) + 31) & ~31;
        DCFlushRange(reinterpret_cast<void*>(cacheLineAddr),
                     cacheLineEnd - cacheLineAddr);
    }

    template <class T> u32 makeBranch(int offset, T* dest, BranchType::E type)
    {
        const u32 destAddr = reinterpret_cast<u32>(dest);

        u32 patch =
            0x48000000 |
            ((destAddr - reinterpret_cast<u32>(&m_instr[offset])) & 0x03FFFFFC);
        if (type == BranchType::BL)
            patch |= 1;

        return patch;
    }

    template <class T> void setB(T dest, int offset = 0)
    {
        m_instr[offset] = makeBranch(offset, dest, BranchType::B);
        flush();
    }

    template <class T> void setBL(T dest, int offset = 0)
    {
        m_instr[offset] = makeBranch(offset, dest, BranchType::BL);
        flush();
    }

    void setBlr(int offset = 0)
    {
        m_instr[offset] = 0x4E800020;
        flush();
    }

    void setNop(int offset = 0)
    {
        m_instr[offset] = 0x60000000;
        flush();
    }

    u32 m_instr[N];
};

asm void buildPagesHook(UI::Scene* scene, UI::SceneID id)
{
    // clang-format off
    nofralloc

    /* original instruction */
    bgt-    buildPages_end

    stwu    r1, -0x10(r1)
    stw     r0, 0xC(r1)
    mflr    r0
    stw     r0, 0x14(r1)

    bl      buildPagesReplace
    cmpwi   r3, 0
    mr      r3, r31

    lwz     r0, 0x14(r1)
    mtlr    r0
    lwz     r0, 0xC(r1)
    addi    r1, r1, 0x10
    
    beqlr-

buildPages_end:
    lwz     r0, 0x14(r1)
    lwz     r31, 0xC(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}

asm void showBasePagesHook(UI::Scene* scene, UI::SceneID id)
{
    // clang-format off
    nofralloc

    /* original instruction */
    bgt-    showBasePages_end

    stwu    r1, -0x10(r1)
    stw     r0, 0xC(r1)
    mflr    r0
    stw     r0, 0x14(r1)

    bl      showBasePagesReplace
    cmpwi   r3, 0
    mr      r3, r31

    lwz     r0, 0x14(r1)
    mtlr    r0
    lwz     r0, 0xC(r1)
    addi    r1, r1, 0x10
    
    beqlr-

showBasePages_end:
    lwz     r0, 0x14(r1)
    lwz     r31, 0xC(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}

const char* titleResourceReplace()
{
    return "/Scene/UI/Menu";
}

#define NDEBUG

#ifndef NDEBUG
extern "C" {
void OSSleepThread(u32);
extern u32 gcndata;
}

void debugSleepThreadHook(u32 r3)
{
    // Press Y to run the game at max possible speed
    if (!(gcndata & 0x08000000))
        OSSleepThread(r3);
}
#endif

extern Instruction<1> Patch_SceneBuildPages;
extern Instruction<1> Patch_SceneShowBasePages;
extern Instruction<1> Patch_MainMenuKind;
extern Instruction<1> Patch_SceneGetBGM;
extern Instruction<1> Patch_SceneGetBGMGroup;
extern Instruction<1> Patch_LicenseSelect;

extern Instruction<6> Patch_EventExplanationPage_Events;
extern Instruction<25> Patch_EventExplanationPage_vtable;
extern Instruction<1> Patch_EventExplanationVolumeChange;

extern Instruction<24> Patch_ChangeMissionCase;
extern Instruction<1> Patch_HudWatchReplayCase;
extern Instruction<4> Patch_QuitReplayCase;

extern Instruction<11> Patch_WiiWheelOnlyPage;

extern Instruction<1> Patch_Nwc24DlManager_init;
extern Instruction<1> Patch_Nwc24DlManager_CheckForCompetition;
extern Instruction<1> Patch_Nwc24DlManager_GetCompetitionText;
extern Instruction<1> Patch_Nwc24DlManager_GetLdbTimeRank;
extern Instruction<1> Patch_Nwc24DlManager_InsertTimeInLdb;
extern Instruction<1> Patch_Nwc24DlManager_GetLdbEntry;
extern Instruction<1> Patch_SaveBestTime;

#ifndef NDEBUG
extern Instruction<1> DebugPatch_SleepThread;
#endif

void main()
{
    Patch_SceneBuildPages.setBL(buildPagesHook);
    Patch_SceneShowBasePages.setBL(showBasePagesHook);

    Patch_MainMenuKind.m_instr[0] = 0x38600000 | UI::SceneKind::Globe;
    Patch_MainMenuKind.flush();

    Patch_LicenseSelect.setBL(patchLicenseSelectGetNextScene);

    Patch_SceneGetBGM.setB(sceneGetBGMReplace);
    Patch_SceneGetBGMGroup.setB(sceneGetBGMGroupReplace);

    Patch_Nwc24DlManager_init.setBlr();
    Patch_Nwc24DlManager_CheckForCompetition.setB(checkForCompetitionReplace);
    Patch_Nwc24DlManager_GetCompetitionText.setB(getCompetitionTextReplace);
    Patch_Nwc24DlManager_GetLdbTimeRank.setB(getTimeLdbPosition);
    Patch_Nwc24DlManager_InsertTimeInLdb.setB(insertTimeInLdb);
    Patch_Nwc24DlManager_GetLdbEntry.setB(getLdbEntry);

    Patch_SaveBestTime.setB(&Patch_SaveBestTime.m_instr[0x74 >> 2]);

    Patch_EventExplanationPage_Events.m_instr[2] =
        reinterpret_cast<u32>(&eventExplanationSelectEvent);
    Patch_EventExplanationPage_Events.m_instr[5] =
        reinterpret_cast<u32>(&eventExplanationBackEvent);
    Patch_EventExplanationPage_vtable.m_instr[4] =
        reinterpret_cast<u32>(&eventExplanationGetNextPage);
    Patch_EventExplanationPage_Events.flush();
    Patch_EventExplanationPage_vtable.flush();

    Patch_EventExplanationVolumeChange.setNop();

    Patch_ChangeMissionCase.m_instr[8] = 0x38800000 | 0x85;
    Patch_ChangeMissionCase.m_instr[16] = 0x36800000 | 0x2D;
    Patch_ChangeMissionCase.flush();
    
    Patch_HudWatchReplayCase.setBL(hudWatchReplayHook);

    Patch_QuitReplayCase.setNop(0);
    Patch_QuitReplayCase.setBL(hudQuitReplayHook, 3);

    Patch_WiiWheelOnlyPage.setBL(wiiWheelPageRejectController);
    Patch_WiiWheelOnlyPage.setB(&Patch_WiiWheelOnlyPage.m_instr[11], 1);

#ifndef NDEBUG
    DebugPatch_SleepThread.setBL(debugSleepThreadHook);
#endif

    if (isRiivolution())
        RiivoFS::initialize();
}