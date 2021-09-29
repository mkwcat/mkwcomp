#include "ui.h"
#include "competition.h"
#include <mkw/MenuSet.h>
#include <mkw/Random.h>
#include <mkw/UI/CtrlMenuBackButton.h>
#include <mkw/UI/CtrlMenuPageTitleText.h>
#include <mkw/UI/Event.h>
#include <mkw/UI/LayoutUIControl.h>
#include <mkw/UI/MesgRes.h>
#include <mkw/UI/MessageYesNoBoxPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/RaceHudPage.h>
#include <mkw/UI/RaceMenuPage.h>
#include <mkw/UI/Scene.h>
#include <mkw/UI/SceneBGMController.h>
#include <mkw/UI/SheetSelectControl.h>
#include <mkw/UI/TitleScreenPage.h>
#include <mkw/UI/UIPage.h>
#include <mkw/common.h>
#include <rvl/os.h>
#include <stdio.h>

#define BACKGROUND_PAGE_ID 0x5C
#define REPLAY_SCENE_ID 0x2D

namespace CompMode
{
enum E
{
    TimeTrial,
    VSRace,
    SpecialTimeTrial,
    EnemyScore,
    BossBattle,
    BossRace,
    Coins,
    Gates
};
} // namespace CompMode

struct CompNameData {
    Course::E course;
    CompMode::E mode;
};

static const CompNameData compNameData[49] = {
    /* c01 - c09 */
    {Course::Mario_Circuit, CompMode::VSRace},
    {Course::GBA_Battle_Course_3, CompMode::Gates},
    {Course::Galaxy_Colosseum, CompMode::BossBattle},
    {Course::Mushroom_Gorge, CompMode::TimeTrial},
    {Course::Coconut_Mall, CompMode::Coins},
    {Course::DS_Twilight_House, CompMode::VSRace},
    {Course::N64_DKs_Jungle_Parkway, CompMode::BossRace},
    {Course::Koopa_Cape, CompMode::Gates},
    {Course::N64_Skyscraper, CompMode::SpecialTimeTrial},

    /* c10 - c19 */
    {Course::SNES_Mario_Circuit_3, CompMode::Coins},
    {Course::Thwomp_Desert, CompMode::BossBattle},
    {Course::Luigi_Circuit, CompMode::VSRace},
    {Course::Maple_Treeway, CompMode::Coins},
    {Course::N64_Mario_Raceway, CompMode::SpecialTimeTrial},
    {Course::Warios_Gold_Mine, CompMode::BossRace},
    {Course::DK_Summit, CompMode::Gates},
    {Course::Toads_Factory, CompMode::TimeTrial},
    {Course::Funky_Stadium, CompMode::Coins},
    {Course::Block_Plaza, CompMode::TimeTrial},

    /* c20 - c29 */
    {Course::GBA_Bowser_Castle_3, CompMode::Gates},
    {Course::SNES_Battle_Course_4, CompMode::Coins},
    {Course::N64_Bowsers_Castle, CompMode::BossRace},
    {Course::GCN_Waluigi_Stadium, CompMode::Gates},
    {Course::DS_Peach_Gardens, CompMode::SpecialTimeTrial},
    {Course::Sunset_Luigi_Circuit, CompMode::VSRace},
    {Course::Chain_Chomp_Roulette, CompMode::Coins},
    {Course::Grumble_Volcano, CompMode::TimeTrial},
    {Course::Galaxy_Colosseum, CompMode::BossBattle},
    {Course::GCN_Peach_Beach, CompMode::Coins},

    /* c30 - c39 */
    {Course::DS_Yoshi_Falls, CompMode::VSRace},
    {Course::GBA_Shy_Guy_Beach, CompMode::EnemyScore},
    {Course::Bowsers_Castle, CompMode::TimeTrial},
    {Course::GCN_Cookie_Land, CompMode::VSRace},
    {Course::GCN_Mario_Circuit, CompMode::SpecialTimeTrial},
    {Course::Daisy_Circuit, CompMode::Gates},
    {Course::Dry_Dry_Ruins, CompMode::VSRace},
    {Course::Rainbow_Road, CompMode::SpecialTimeTrial},
    {Course::DS_Desert_Hills, CompMode::EnemyScore},
    {Course::Delfino_Pier, CompMode::SpecialTimeTrial},

    /* c40 - c49 */
    {Course::GCN_DK_Mountain, CompMode::Gates},
    {Course::N64_Sherbet_Land, CompMode::VSRace},
    {Course::Mario_Circuit, CompMode::EnemyScore},
    {Course::Luigi_Circuit, CompMode::VSRace},
    {Course::GCN_Peach_Beach, CompMode::SpecialTimeTrial},
    {Course::Moonview_Highway, CompMode::TimeTrial},
    {Course::DS_Delfino_Square, CompMode::TimeTrial},
    {Course::Mario_Circuit, CompMode::VSRace},
    {Course::N64_Bowsers_Castle, CompMode::BossRace},
    {Course::Galaxy_Colosseum, CompMode::BossBattle},
};

static inline int compTitleMid(int compId)
{
    return 10000 + compId - 1;
}
static inline int compExplanationMid(int compId)
{
    return 10100 + compId - 1;
}

class PageSelection : public UI::UIPage
{
public:
    PageSelection()
        : m_ptr_selectEvent(this, &PageSelection::selectEvent),
          m_ptr_highlightEvent(this, &PageSelection::highlightEvent),
          m_ptr_backEvent(this, &PageSelection::backEvent),
          m_ptr_arrowRightEvent(this, &PageSelection::arrowRightEvent),
          m_ptr_arrowLeftEvent(this, &PageSelection::arrowLeftEvent),
          m_nextPage(-1)
    {
    }
    virtual ~PageSelection()
    {
    }

    void updatePageNumText()
    {
        UI::MesgRes::FormatParam param;
        param.intParam = m_pageNum + 1;
        param.intParam2 = 5;
        m_pageNumControl.setAllText(0x7D9, &param);
    }

    void updateButtonTexture()
    {
        for (int i = 0; i < 10; i++) {
            char texture[16];
            snprintf(texture, 16, "comp%02d", buttonCompId(i));
            m_buttons[i].setTexture("chara", texture);
            UI::MesgRes::FormatParam param;
            param.intParam = buttonCompId(i);

            // The smaller digit one inserts a space at the end to push the text
            // a little to the left lol
            if (buttonCompId(i) == 0)
                m_buttons[i].setAllText(0, nullptr);
            else if (buttonCompId(i) < 10)
                m_buttons[i].setAllText(0x27E9, &param);
            else
                m_buttons[i].setAllText(0x27E8, &param);
        }
    }

    void updateCompetitionName()
    {
        if (m_highlightCompId == 0) {
            m_compName.setPaneText("text", 0x27F1, 0);
            m_compName.setPaneText("text_shadow", 0x27F1, 0);

            m_compName.setPaneText("mode_text", 0x27F2, 0);
            m_compName.setPaneText("mode_text_shadow", 0x27F2, 0);
            return;
        }
        if (m_highlightCompId == -100)
            return;

        const CompNameData* data = &compNameData[m_highlightCompId - 1];

        int courseMid = msgIdForCourse(data->course);
        m_compName.setPaneText("text", courseMid, 0);
        m_compName.setPaneText("text_shadow", courseMid, 0);

        m_compName.setPaneText("mode_text", 0x27D8 + data->mode, 0);
        m_compName.setPaneText("mode_text_shadow", 0x27D8 + data->mode, 0);

        char texture[16];
        snprintf(texture, 16, "id%02d", data->course);
        m_compName.setTexture("course_bg", texture);
    }

    int buttonCompId(int buttonId)
    {
        return m_pageNum * 10 + buttonId;
    }
    int compIdButton(int compId)
    {
        return compId % 10;
    }

    void initInternal()
    {
        m_events.init(1, 0);

        setEventController(&m_events);
        initControlGroup(15);

        for (int i = 0; i < 10; i++) {
            registerControl(i, &m_buttons[i], 0);

            char name[16];
            snprintf(name, 16, "Button%d", i);

            m_buttons[i].readLayout("button", "CompetitionButton", name, 1, 0,
                                    false);
            m_buttons[i].setSelectEvent(&m_ptr_selectEvent, 0);
            m_buttons[i].setHighlightEvent(&m_ptr_highlightEvent);
            m_buttons[i].m_id = i;
        }

        m_highlightCompId = s_lastCompId;
        m_pageNum = m_highlightCompId / 10;
        m_highlightButtonId = compIdButton(m_highlightCompId);
        m_buttons[m_highlightButtonId].setHighlighted(0);

        registerControl(10, &m_arrows, 0);
        m_arrows.readLayout("button", "FriendListArrowRight",
                            "ButtonArrowRight", "FriendListArrowLeft",
                            "ButtonArrowLeft", 1, 0, false);
        m_arrows.m_rightEvent = &m_ptr_arrowRightEvent;
        m_arrows.m_leftEvent = &m_ptr_arrowLeftEvent;

        {
            registerControl(11, &m_pageNumControl, 0);
            UI::CtrlRes ctrl(&m_pageNumControl);
            ctrl.readFile("control", "TimeAttackGhostListPageNum",
                          "TimeAttackGhostListPageNum", nullptr);
        }
        {
            registerControl(12, &m_compName, 0);
            UI::CtrlRes ctrl(&m_compName);
            ctrl.readFile("control", "CompetitionName", "CompetitionName",
                          nullptr);
        }

        registerControl(13, &m_backButton, 0);
        m_backButton.initLayout(1);
        m_backButton.setSelectEvent(&m_ptr_selectEvent, 0);
        m_backButton.setHighlightEvent(&m_ptr_highlightEvent);

        registerControl(14, &m_titleText, 0);
        m_titleText.initLayout(0);
        m_titleText.setAllText(0x27F0, 0);

        m_events.setScreenWrapSetting(2);
        m_events.configureEvent(UI::INPUT_BACK, &m_ptr_backEvent, 0, 0);

        updatePageNumText();
        updateCompetitionName();
        updateButtonTexture();
    }

    void selectEvent(UI::PushButton* button, int r5)
    {
        // -100 represents the on-screen back button
        if (button->m_id == -100) {
            f32 delay = button->getSelectDelay();
            startSceneTransition(delay, 0x42, UI::UIPage::SLIDE_BACK);
            return;
        }

        int compId = buttonCompId(button->m_id);
        s_lastCompId = compId; // save random
        if (compId == 0) {
            Random random;
            compId = random.nextLimited(49) + 1;
        }

        // Search for the competition messages. The text on the event
        // explanation screen isn't fetched from BMG files because it's
        // meant to be stored in the save file. This is a little hacky
        // because it hijacks the BMG used by the button that was just
        // selected.
        int titleMid = compTitleMid(compId);
        int explanationMid = compExplanationMid(compId);

        const UI::MesgRes* bmg = &button->m_bmg;
        int titleIndex = bmg->getIndexFromMid(titleMid);
        int explanationIndex = bmg->getIndexFromMid(explanationMid);

        const wchar_t* titleText = L"---";
        const wchar_t* explanationText = L"---";
        if (titleIndex != -1)
            titleText = bmg->getTextFromIndex(titleIndex);
        if (explanationIndex != -1)
            explanationText = bmg->getTextFromIndex(explanationIndex);

        CompFile::sInstance->setText(titleText, explanationText);
        CompFile::sInstance->switchCompetition(compId);
        m_nextPage = 0xB8;

        f32 delay = button->getSelectDelay();
        startTransitionOut(SLIDE_FORWARD, delay);
    }

    void highlightEvent(UI::PushButton* button, int r5)
    {
        m_highlightButtonId = button->m_id;
        m_highlightCompId = buttonCompId(button->m_id);
        updateCompetitionName();
    }

    void backEvent(int r4, int r5)
    {
        startSceneTransition(0, 0x42, UI::UIPage::SLIDE_BACK);
    }

    void arrowRightEvent(UI::SheetSelectControl* arrow, int r5)
    {
        m_pageNum++;
        if (m_pageNum > 4)
            m_pageNum = 0;
        updatePageNumText();
        updateButtonTexture();

        // Deselect arrows and select main button
        if (m_highlightButtonId < 5) {
            m_buttons[0].somethingHighlightRelated(0);
            return;
        }
        m_buttons[5].somethingHighlightRelated(0);
    }

    void arrowLeftEvent(UI::SheetSelectControl* arrow, int r5)
    {
        m_pageNum--;
        if (m_pageNum < 0)
            m_pageNum = 4;
        updatePageNumText();
        updateButtonTexture();

        // Deselect arrows and select main button
        if (m_highlightButtonId < 5) {
            m_buttons[4].somethingHighlightRelated(0);
            return;
        }
        m_buttons[9].somethingHighlightRelated(0);
    }

    int getNextPageID()
    {
        return m_nextPage;
    }

    UI::PushButton m_buttons[10];
    UI::SheetSelectControl m_arrows;
    UI::LayoutUIControl m_pageNumControl;
    UI::LayoutUIControl m_compName;

    UI::CtrlMenuPageTitleText m_titleText;
    UI::CtrlMenuBackButton m_backButton;

    UI::PageEventSelection m_events;

    int m_nextPage;

    UI::Event<PageSelection, UI::PushButton*, int> m_ptr_selectEvent;
    UI::Event<PageSelection, UI::PushButton*, int> m_ptr_highlightEvent;
    UI::Event<PageSelection, int, int> m_ptr_backEvent;
    UI::Event<PageSelection, UI::SheetSelectControl*, int> m_ptr_arrowLeftEvent;
    UI::Event<PageSelection, UI::SheetSelectControl*, int>
        m_ptr_arrowRightEvent;

    int m_pageNum;
    int m_highlightButtonId;
    int m_highlightCompId;

    static int s_lastCompId;

public:
    static UI::AutoTypeInfo<UI::UIPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};
UI::AutoTypeInfo<UI::UIPage> PageSelection::sTypeInfo;

int PageSelection::s_lastCompId = 0;

const int sEndScreenButtons[5] = {
    UI::RaceMenu::ButtonRestart, UI::RaceMenu::ButtonChangeCharacter,
    UI::RaceMenu::ButtonChangeMission, UI::RaceMenu::ButtonQuit,
    UI::RaceMenu::ButtonReplay};

class EventAfterMenuPage : public UI::RaceMenuPage
{
public:
    EventAfterMenuPage() : m_340(0)
    {
    }

    int _68()
    {
        return m_340;
    }

    int getButtonCount() const
    {
        return 5;
    }

    const int* getButtonList() const
    {
        return sEndScreenButtons;
    }

    bool isPauseMenu() const
    {
        return false;
    }

    const char* getButtonCtrlName() const
    {
        return "AfterMenuOfflineEvent";
    }

    int m_33C;
    int m_340;

public:
    static UI::AutoTypeInfo<UI::RaceMenuPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};
UI::AutoTypeInfo<UI::RaceMenuPage> EventAfterMenuPage::sTypeInfo;

const int sPauseScreenButtons[5] = {
    UI::RaceMenu::ButtonContinue,
    UI::RaceMenu::ButtonRestart,
    UI::RaceMenu::ButtonChangeCharacter,
    UI::RaceMenu::ButtonChangeMission,
    UI::RaceMenu::ButtonQuit,
};

class EventPauseMenuPage : public UI::RaceMenuPage
{
public:
    EventPauseMenuPage() : m_340(0)
    {
    }

    int _68()
    {
        return m_340;
    }

    int getButtonCount() const
    {
        return 5;
    }

    const int* getButtonList() const
    {
        return sPauseScreenButtons;
    }

    bool isPauseMenu() const
    {
        return true;
    }

    const char* getButtonCtrlName() const
    {
        return "PauseMenuOfflineEvent";
    }

    int m_33C;
    int m_340;

public:
    static UI::AutoTypeInfo<UI::RaceMenuPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};
UI::AutoTypeInfo<UI::RaceMenuPage> EventPauseMenuPage::sTypeInfo;

const int sReplayPauseScreenButtons[3] = {
    UI::RaceMenu::ButtonContinueReplay,
    UI::RaceMenu::ButtonRestartReplay,
    UI::RaceMenu::ButtonQuitReplay,
};

#if 0
class EventReplayPauseMenuPage : public UI::RaceMenuPage
{
public:
    EventReplayPauseMenuPage() : m_340(0)
    {
    }

    int _68()
    {
        return m_340;
    }

    int getButtonCount() const
    {
        return 3;
    }

    const int* getButtonList() const
    {
        return sReplayPauseScreenButtons;
    }

    bool isPauseMenu() const
    {
        return false;
    }

    const char* getButtonCtrlName() const
    {
        return "PauseMenuReplayTA";
    }

    int m_33C;
    int m_340;

public:
    static UI::AutoTypeInfo<UI::RaceMenuPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};
UI::AutoTypeInfo<UI::RaceMenuPage> EventReplayPauseMenuPage::sTypeInfo;
#endif

class ReplayHud : public UI::RaceHudPage
{
public:
    ReplayHud()
    {
        m_nextPage = -1;
    }

    s32 getPausePageID()
    {
        return 0x39;
    }

    // Decompilation of the function at 0x8085896C.
    // I don't know what all the mask bits are.
    virtual u32 getHudLayoutMask()
    {
        MenuSet::RaceSetting* set = &MenuSet::sInstance->currentRace;

        if (set->modeFlags & MenuSet::RaceSetting::FLAG_TOURNAMENT) {
            switch (set->gameMode) {
            case MenuSet::RaceSetting::MODE_VS_RACE:
                return 0x87E;
            case MenuSet::RaceSetting::MODE_TIME_TRIAL:
                return 0x86E;
            }

            switch (set->mission.gameMode) {
            case MissionSetting::MODE_LapRun01:
                return 0x86E;
            case MissionSetting::MODE_LapRun02:
                return 0x87E;

            case MissionSetting::MODE_EnemyDown01:
            case MissionSetting::MODE_EnemyDown02:
            case MissionSetting::MODE_EnemyDown03:
                return 0x2C4E;
            }
        } else {
            switch (set->mission.gameMode) {
            // Apparently these are both the same for non-tournament mission
            // mode
            case MissionSetting::MODE_LapRun01:
            case MissionSetting::MODE_LapRun02:
                return 0x87E;
            }
        }

        return 0xC4E;
    }

    bool _7C()
    {
        if (isRaceEnded(0))
            return true;
        return false;
    }

public:
    static UI::AutoTypeInfo<UI::RaceHudPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};
UI::AutoTypeInfo<UI::RaceHudPage> ReplayHud::sTypeInfo;

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

// The page that manages the popup choice that appears when you try to use a
// wrong controller on a Wii Wheel only tournament.
class ForcedHandleBypassPage : public UI::UIPage
{
public:
    ForcedHandleBypassPage()
        : m_ptr_selectYes(this, &ForcedHandleBypassPage::selectYes)
    {
        m_noResume = false;
        m_wiiWheelPageDisabled = false;
    }

    void initInternal()
    {
        CompFile::sInstance->m_forceHandleDisabled = false;
        setEventController(&m_events);
    }

    void onShow()
    {
        UI::MessageYesNoBoxPage* msgPage =
            UI::UIPage::cast<UI::MessageYesNoBoxPage>(
                UI::MenuDataInstance->m_scene->getPage(0x4E));

        msgPage->configMessage(0x2800, nullptr);
        msgPage->configOption(0, 0xFAC, nullptr, 1, &m_ptr_selectYes);
        msgPage->configOption(1, 0xFAD, nullptr, -1, nullptr);
        m_noResume = false;
        showNextPage(0x4E, 0);
    }

    void selectYes(UI::MessageYesNoBoxPage* page, UI::PushButton* button)
    {
        CompFile::sInstance->m_forceHandleDisabled = true;

        const int sceneId = UI::MenuDataInstance->m_scene->m_sceneId;
        if (sceneId == 0x88) {
            // Normal tournament intro
            UI::MenuDataInstance->setNextScene(0x2D, 0);
        } else if (sceneId == 0x89) {
            // For bosses specifically
            UI::MenuDataInstance->setNextScene(0x1D, 0);
        }

        f32 delay = button->getSelectDelay();
        UI::MenuDataInstance->startSceneTransition((int)delay, 0x000000FF);

        UI::UIPage* lastPage = UI::MenuDataInstance->m_scene->getPage(0xBA);
        lastPage->startTransitionOut(UI::UIPage::SLIDE_FORWARD, delay);

        m_noResume = true;
    }

    void resume()
    {
        UI::UIPage* lastPage = UI::MenuDataInstance->m_scene->getPage(0xBA);
        if (!m_noResume) {
            // These calls emulate two functions required to dereference the
            // current controller
            lastPage->onShow();
            lastPage->_3C();
            m_wiiWheelPageDisabled = false;
        }
        startTransitionOut(UI::UIPage::SLIDE_FORWARD, 0);
    }

    static int isWiiWheelPageDisabled()
    {
        ForcedHandleBypassPage* page = UI::UIPage::cast<ForcedHandleBypassPage>(
            UI::MenuDataInstance->m_scene->getPage(0x87));
        return page->m_wiiWheelPageDisabled;
    }
    static void setWiiWheelPageDisabled(bool set)
    {
        ForcedHandleBypassPage* page = UI::UIPage::cast<ForcedHandleBypassPage>(
            UI::MenuDataInstance->m_scene->getPage(0x87));
        page->m_wiiWheelPageDisabled = set;
    }

protected:
    bool m_noResume;
    bool m_wiiWheelPageDisabled;

    UI::Event<ForcedHandleBypassPage, UI::MessageYesNoBoxPage*, UI::PushButton*>
        m_ptr_selectYes;
    UI::PageEventBase m_events;

public:
    static UI::AutoTypeInfo<UI::UIPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};
UI::AutoTypeInfo<UI::UIPage> ForcedHandleBypassPage::sTypeInfo;

void wiiWheelPageRejectController(UI::UIPage* page)
{
    if (ForcedHandleBypassPage::isWiiWheelPageDisabled())
        return;

    ForcedHandleBypassPage::setWiiWheelPageDisabled(true);
    page->showNextPage(0x87, 0);
}

asm void hudWatchReplayHook()
{
    // clang-format off
    nofralloc

    li      r4, -1

    cmpwi   r0, 0x2D
    bnelr

    li      r4, REPLAY_SCENE_ID
    blr
    // clang-format on
}

asm void hudQuitReplayHook()
{
    // clang-format off
    nofralloc

    // case 0x2F
    li      r4, 0x21
    beqlr-

    cmpwi   r0, REPLAY_SCENE_ID
    li      r4, 0x26
    beqlr-

    li      r4, -1
    blr
}

bool buildPagesReplace(UI::Scene* scene, UI::SceneID id)
{
    OSReport("load pages for scene: 0x%X\n", id);

    switch (id) {
    case 0x2D:
        if (MenuSet::sInstance->currentRace.controlKind != 1) {
            scene->buildPage(0x16);
            {
                EventPauseMenuPage* page = new EventPauseMenuPage();
                scene->registerPage(0x1B, page);
                page->init(0x1B);
            }
        } else {
            scene->buildPage(0x39);
            {
                ReplayHud* page = new ReplayHud();
                scene->registerPage(0x16, page);
                page->init(0x16);
            }
        }
        scene->buildPage(0x2A);
        scene->buildPage(0x35);
        scene->buildPage(0x3A);
        {
            EventAfterMenuPage* page = new EventAfterMenuPage();
            scene->registerPage(0x26, page);
            page->init(0x26);
        }
        return true;

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
            PageSelection* page = new PageSelection();
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

    default:
        return false;
    }
}

s32 patchLicenseSelectGetNextScene()
{
    // UI::SceneBGMControllerInstance->enableBGMPersist();
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
        return 3;
    case 0x45 ... 0x47:
    case 0x8C:
        return 12;
    default:
        return -1;
    }
}