#include "CompFile.h"
#include "UI.h"
#include "patch.h"
#include "replay.h"
#include "util.h"
#include <mkw/UI/LayoutUIControl.h>
#include <mkw/UI/Scene.h>

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

const char* scene87ResourceName()
{
    return "/Scene/UI/Event";
}

extern Instruction<1> Patch_SceneBuildPages;
extern Instruction<1> Patch_SceneShowBasePages;
extern Instruction<1> Patch_MainMenuKind;
extern Instruction<1> Patch_SceneGetBGM;
extern Instruction<1> Patch_SceneGetBGMGroup;
extern Instruction<1> Patch_LicenseSelect;
extern Instruction<1> Patch_LicenseSettingsBack;
extern Instruction<1> Patch_Scene87ResourceName;

extern Instruction<6> Patch_EventExplanationPage_Events;
extern Instruction<25> Patch_EventExplanationPage_vtable;
extern Instruction<1> Patch_EventExplanationVolumeChange;

extern Instruction<24> Patch_ChangeMissionCase;
extern Instruction<1> Patch_HudWatchReplayCase;
extern Instruction<4> Patch_QuitReplayCase;

extern Instruction<1> Patch_ResultMusic;

extern Instruction<11> Patch_WiiWheelOnlyPage;

void main()
{
    Patch_SceneBuildPages.setBL(buildPagesHook);
    Patch_SceneShowBasePages.setBL(showBasePagesHook);

    Patch_MainMenuKind.m_instr[0] = 0x38600000 | UI::SceneKind::Globe;
    Patch_MainMenuKind.flush();

    Patch_LicenseSelect.setBL(patchLicenseSelectGetNextScene);
    Patch_LicenseSettingsBack.m_instr[0] = 0x38800000 | SETTINGS_SCENE_ID;
    Patch_Scene87ResourceName.setB(scene87ResourceName);

    Patch_SceneGetBGM.setB(sceneGetBGMReplace);
    Patch_SceneGetBGMGroup.setB(sceneGetBGMGroupReplace);

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

    Patch_ResultMusic.setB(resultMusicHook);

    Patch_QuitReplayCase.setNop(0);
    Patch_QuitReplayCase.setBL(hudQuitReplayHook, 3);

    Patch_WiiWheelOnlyPage.setBL(wiiWheelPageRejectController);
    Patch_WiiWheelOnlyPage.setB(&Patch_WiiWheelOnlyPage.m_instr[11], 1);

    if (getRegionChar() == 'E') {
        // Skip ESRB screen patch for NTSC-U
        Instruction<1>* esrbPatch =
            reinterpret_cast<Instruction<1>*>(0x8060409C);
        esrbPatch->m_instr[0] = 0x38600001;
        esrbPatch->flush();
    }

    initReplayMode();
    initCompFilePatches();

    if (isRiivolution())
        RiivoFS::initialize();
}