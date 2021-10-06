#include "ui.h"
#include "ForcedHandleBypassPage.h"
#include "RaceMenu.h"
#include "SelectionPage.h"
#include "SettingsPage.h"
#include "patch.h"
#include "replay.h"
#include "util.h"
#include <mkw/MenuSet.h>
#include <mkw/UI/CtrlMenuBackButton.h>
#include <mkw/UI/CtrlMenuPageTitleText.h>
#include <mkw/UI/Event.h>
#include <mkw/UI/LayoutUIControl.h>
#include <mkw/UI/MesgRes.h>
#include <mkw/UI/MessageYesNoBoxPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/Scene.h>
#include <mkw/UI/TitleScreenPage.h>
#include <mkw/UI/UIPage.h>
#include <mkw/common.h>
#include <rvl/os.h>
#include <stdio.h>

// use a static variable for this I guess
s32 s_eventExplanation_nextPage = -1;

void eventExplanationSelectEvent(UI::UIPage* page, UI::PushButton* button,
                                 int r5)
{
    float delay = button->getSelectDelay();

    if (button->m_id == 2) {
        // Start/Next button
        s_eventExplanation_nextPage = 0xB7;
        page->startTransitionOut(UI::UIPage::SLIDE_FORWARD, delay);
        return;
    }
    if (button->m_id == 3) {
        // Back button
        s_eventExplanation_nextPage = 0x8C;
        page->startTransitionOut(UI::UIPage::SLIDE_BACK, delay);
        return;
    }
}

void eventExplanationBackEvent(UI::UIPage* page, int r4, int r5)
{
    s_eventExplanation_nextPage = 0x8C;
    page->startTransitionOut(UI::UIPage::SLIDE_BACK, 0);
}

s32 eventExplanationGetNextPage(UI::UIPage* page)
{
    return s_eventExplanation_nextPage;
}

bool buildPagesReplace(UI::Scene* scene, UI::SceneID id)
{
    OSReport("load pages for scene: 0x%X\n", id);

    switch (id) {
    case 0x2D:
        if (isTournamentReplay())
            return buildTournamentReplayPages(scene);
        return buildTournamentPages(scene);

    case 0x3F ... 0x43:
        scene->buildPage(0x52);
        scene->buildPage(0x5E);
        scene->buildPage(0x65);
        {
            UI::TitleScreenPage* page = new UI::TitleScreenPage();
            page->hideBackground(true);
            scene->registerPage(0x57, page);
            page->init(0x57);
        }
        return true;

    case 0x85:
    case 0x86:
    case 0x83:
        scene->buildPage(0x4B);
        scene->buildPage(0x4D);
        scene->buildPage(0x51);
        // scene->buildPage(0x5E);
        scene->buildPage(0x6B);
        scene->buildPage(0x6C);
        scene->buildPage(0x6D);
        scene->buildPage(0x7F);
        scene->buildPage(0xB7);
        scene->buildPage(0xB8);
        scene->buildPage(0xBB);
        {
            SelectionPage* page = new SelectionPage();
            scene->registerPage(0x8C, page);
            page->init(0x8C);
        }
        return true;

    case 0x88:
    case 0x89:
        scene->buildPage(0x5B);
        scene->buildPage(0xBA);
        scene->buildPage(0x4E);
        {
            ForcedHandleBypassPage* page = new ForcedHandleBypassPage();
            scene->registerPage(0x87, page);
            page->init(0x87);
        }
        return true;

    case SETTINGS_SCENE_ID:
        scene->buildPage(0x4D);
        scene->buildPage(0x4E);
        scene->buildPage(0x5D);
        scene->buildPage(0xC1);
        scene->buildPage(0xC2);
        scene->buildPage(0xC3);
        scene->buildPage(0xC4);
        scene->buildPage(0xC5);
        scene->buildPage(0xC6);
        scene->buildPage(0xC7);
        scene->buildPage(0xC8);
        scene->buildPage(0xC9);
        scene->buildPage(0xCA);
        scene->buildPage(0xCB);
        scene->buildPage(0xCC);
        {
            SettingsPage* page = new SettingsPage();
            scene->registerPage(0xC0, page);
            page->init(0xC0);
        }
        return true;

    default:
        return false;
    }
}

bool showBasePagesReplace(UI::Scene* scene, UI::SceneID id)
{
    switch (id) {
    case 0x3F ... 0x41:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x57);
        return true;
    case 0x42:
    case 0x43:
        scene->showPageOnTop(0x5E);
        scene->showPageOnTop(0x65);
        return true;
    case 0x85:
        scene->showPageOnTop(0xBB);
        scene->showPageOnTop(0x7F);
        // scene->showPageOnTop(0x69);
        scene->showPageOnTop(0x8C);
        return true;
    case 0x86:
        scene->showPageOnTop(0xBB);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0xB7);
        return true;
    case 0x83:
        scene->showPageOnTop(0xBB);
        scene->showPageOnTop(0x7F);
        scene->showPageOnTop(0xC0);
        return true;

    default:
        return false;
    }
}

s32 patchLicenseSelectGetNextScene()
{
    return 0x85;
}

bool sceneHasBackModelReplace(UI::SceneID id)
{
    return false;
}

s32 sceneGetBGMReplace(UI::SceneID id)
{
    switch (id) {
    case 0x19:
        return 0x59;
    case 0x1B:
    case 0x1C:
    case 0x1D:
        return 0x57;
    case 0x1E:
        return 0x59;
    case 0x1F:
        return 0x5A;
    case 0x20 ... 0x27:
        return 0x59;
    case 0x28 ... 0x2D:
        return 0x5A;
    case 0x3F ... 0x43:
        return 2;
    case 0x85:
    case 0x86:
    case 0x83:
        return 1;
    case 0x45 ... 0x47:
    case 0x8C:
        return 0x53;
    default:
        return -1;
    }
}
s32 sceneGetBGMGroupReplace(UI::SceneID id)
{
    switch (id) {
    case 0x3F ... 0x43:
        return 2;
    case 0x85:
    case 0x86:
    case 0x83:
        return 3;
    case 0x45 ... 0x47:
    case 0x8C:
        return 12;
    default:
        return -1;
    }
}

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

extern Instruction<1> Patch_SceneBuildPages;
extern Instruction<1> Patch_SceneShowBasePages;
extern Instruction<1> Patch_MainMenuKind;
extern Instruction<1> Patch_SceneGetBGM;
extern Instruction<1> Patch_SceneGetBGMGroup;
extern Instruction<1> Patch_LicenseSelect;
extern Instruction<1> Patch_LicenseSettingsBack;

extern Instruction<6> Patch_EventExplanationPage_Events;
extern Instruction<25> Patch_EventExplanationPage_vtable;
extern Instruction<1> Patch_EventExplanationVolumeChange;

void initMenu()
{
    if (getRegionChar() == 'E') {
        // Skip ESRB screen patch for NTSC-U
        Instruction<1>* esrbPatch =
            reinterpret_cast<Instruction<1>*>(0x8060409C);
        esrbPatch->m_instr[0] = 0x38600001;
        esrbPatch->flush();
    }

    ForcedHandleBypassPage::staticInit();
    initRaceMenu();

    Patch_SceneBuildPages.setBL(buildPagesHook);
    Patch_SceneShowBasePages.setBL(showBasePagesHook);

    Patch_MainMenuKind.m_instr[0] = 0x38600000 | UI::SceneKind::Globe;
    Patch_MainMenuKind.flush();

    Patch_LicenseSelect.setBL(patchLicenseSelectGetNextScene);
    Patch_LicenseSettingsBack.m_instr[0] = 0x38800000 | SETTINGS_SCENE_ID;

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
}