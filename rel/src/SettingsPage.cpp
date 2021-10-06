#include "SettingsPage.h"
#include "UI.h"
#include "patch.h"
#include <mkw/UI/PushButton.h>
#include <mkw/UI/Scene.h>
#include <mkw/UI/SceneBGMController.h>
#include <mkw/UI/UIPage.h>

UI::AutoTypeInfo<UI::UIPage> SettingsPage::sTypeInfo;

enum Button
{
    BUTTON_RUMBLE = 0,
    BUTTON_SEED = 1,
    BUTTON_LICENSE = 2
};

SettingsPage::SettingsPage()
    : m_ptr_onButtonSelect(this, &SettingsPage::onButtonSelect),
      m_ptr_onBackPress(this, &SettingsPage::onBackPress)
{
    m_nextPage = -1;
}
SettingsPage::~SettingsPage()
{
}

void SettingsPage::onInit()
{
    m_events.init(1, 0);
    setEventController(&m_events);
    m_events.setScreenWrapSetting(1);

    initControlGroup(5);

    // GCN Controller Rumble
    {
        insertControl(0, &m_rumbleButton, 0);
        m_rumbleButton.readLayout("button", "OptionTopButton", "Rumble", 1, 0,
                                  false);
        m_rumbleButton.setSelectEvent(&m_ptr_onButtonSelect, 0);
        m_rumbleButton.m_id = BUTTON_RUMBLE;
    }

    // Normally Network Settings
    {
        insertControl(1, &m_seedButton, 0);
        m_seedButton.readLayout("button", "OptionTopButton", "Network", 1, 0,
                                false);
        m_seedButton.setSelectEvent(&m_ptr_onButtonSelect, 0);
        m_seedButton.m_id = BUTTON_SEED;
    }

    // Normally Add Mario Kart Channel
    {
        insertControl(2, &m_licenseButton, 0);
        m_licenseButton.readLayout("button", "OptionTopButton",
                                   "ChannelInstall", 1, 0, false);
        m_licenseButton.setSelectEvent(&m_ptr_onButtonSelect, 0);
        m_licenseButton.setAllText(0x7DF, nullptr);
        m_licenseButton.m_id = BUTTON_LICENSE;
    }

    insertControl(3, &m_backButton, 0);
    m_backButton.initLayout(1);
    m_backButton.setSelectEvent(&m_ptr_onButtonSelect, 0);

    insertControl(4, &m_titleText, 0);
    m_titleText.initLayout(0);
    m_titleText.setAllText(MID_SETTINGS, 0);

    m_events.configureEvent(UI::INPUT_BACK, &m_ptr_onBackPress, 0, 0);

    // aka options from license settings
    if (UI::MenuDataInstance->m_scene->m_sceneId == UI::SCENE_INSTALL_CHANNEL) {
        m_licenseButton.setSelected(0);
    } else {
        m_rumbleButton.setSelected(0);
    }
}

void SettingsPage::onButtonSelect(UI::PushButton* button, int r5)
{
    int sceneId = -1;
    m_nextPage = -1;

    switch (button->m_id) {
    case BUTTON_RUMBLE:
        sceneId = 0x8D;
        break;
    case BUTTON_LICENSE: {
        UI::SceneBGMControllerInstance->enableBGMPersist();
        sceneId = LICENSE_SETTINGS_SCENE_ID;
        break;
    }

    default:
        return;
    }

    f32 delay = button->getSelectDelay();
    m_nextPage = -1;
    startSceneTransition(LICENSE_SETTINGS_SCENE_ID, SLIDE_FORWARD, delay);
}

void SettingsPage::onBackPress(int r4, int r5)
{
    startSceneTransition(TOURNAMENT_SELECT_SCENE_ID, SLIDE_BACK, 0);
}

int SettingsPage::getNextPageID()
{
    return m_nextPage;
}

void LicenseSettings_onBackPress(UI::UIPage* page)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    // aka options from license settings
    page->startSceneTransition(UI::SCENE_INSTALL_CHANNEL,
                               UI::UIPage::SLIDE_BACK, 0);
}

extern Instruction<1> Patch_LicenseSettingsBack;
void SettingsPage::staticInit()
{
    Patch_LicenseSettingsBack.setB(LicenseSettings_onBackPress);
}