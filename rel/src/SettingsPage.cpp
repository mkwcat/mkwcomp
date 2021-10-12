#include "SettingsPage.h"
#include "UI.h"
#include "patch.h"
#include <mkw/RKContext.h>
#include <mkw/UI/OptionMessageBoxManagerPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/SceneBGMController.h>
#include <mkw/UI/UIPage.h>

TYPEINFO_DERIVED(SettingsPage, UI::UIPage);

enum Button
{
    BUTTON_RUMBLE = 0,
    BUTTON_GHOSTDATA = 1,
    BUTTON_LICENSE = 2,
    BUTTON_BACK = -100
};

SettingsPage::SettingsPage()
    : m_fun_onButtonSelect(this, &SettingsPage::onButtonSelect),
      m_fun_onBackPress(this, &SettingsPage::onBackPress),
      m_fun_messageWindowEvent(this, &SettingsPage::messageWindowEvent)
{
    m_nextPage = -1;
}
SettingsPage::~SettingsPage()
{
}

void SettingsPage::onInit()
{
    m_inputs.init(1, 0);
    setInputManager(&m_inputs);
    m_inputs.setScreenWrapSetting(1);

    initControlGroup(5);

    // GCN Controller Rumble
    {
        insertControl(0, &m_rumbleButton, 0);
        m_rumbleButton.readLayout("button", "OptionTopButton", "Rumble", 1, 0,
                                  false);
        m_rumbleButton.setSelectFunction(&m_fun_onButtonSelect, 0);
        m_rumbleButton.m_id = BUTTON_RUMBLE;
    }

    // Normally Network Settings
    {
        insertControl(1, &m_ghostDataButton, 0);
        m_ghostDataButton.readLayout("button", "OptionTopButton", "Network", 1,
                                     0, false);
        m_ghostDataButton.setSelectFunction(&m_fun_onButtonSelect, 0);
        m_ghostDataButton.setMessage(0x2801, nullptr);
        m_ghostDataButton.m_id = BUTTON_GHOSTDATA;
    }

    // Normally Add Mario Kart Channel
    {
        insertControl(2, &m_licenseButton, 0);
        m_licenseButton.readLayout("button", "OptionTopButton",
                                   "ChannelInstall", 1, 0, false);
        m_licenseButton.setSelectFunction(&m_fun_onButtonSelect, 0);
        m_licenseButton.setMessage(0x7DF, nullptr);
        m_licenseButton.m_id = BUTTON_LICENSE;
    }

    insertControl(3, &m_backButton, 0);
    m_backButton.initLayout(1);
    m_backButton.setSelectFunction(&m_fun_onButtonSelect, 0);

    insertControl(4, &m_titleText, 0);
    m_titleText.initLayout(0);
    m_titleText.setMessage(MID_SETTINGS, 0);

    m_inputs.configureInput(UI::INPUT_BACK, &m_fun_onBackPress, 0, 0);

    // aka options from license settings
    if (RKContext::sInstance->m_scene->m_sceneId == UI::SCENE_INSTALL_CHANNEL) {
        m_licenseButton.setSelected(0);
    } else {
        m_rumbleButton.setSelected(0);
    }
}

void SettingsPage::onButtonSelect(UI::PushButton* button, int r5)
{
    m_nextPage = -1;

    switch (button->m_id) {
    case BUTTON_RUMBLE:
        selectRumble(button);
        break;

    case BUTTON_GHOSTDATA:
        selectGhostData(button);
        break;

    case BUTTON_LICENSE:
        selectLicenseSettings(button);
        break;

    case BUTTON_BACK:
        f32 delay = button->getSelectDelay();
        startSceneTransition(UI::SCENE_TOURNAMENT, SLIDE_BACK, delay);
        break;
    }
}

void SettingsPage::onBackPress(int r4, int r5)
{
    startSceneTransition(UI::SCENE_TOURNAMENT, SLIDE_BACK, 0);
}

void SettingsPage::selectRumble(UI::PushButton* button)
{
    UI::OptionMessageBoxManagerPage* page =
        RuntimeTypeInfo::cast<UI::OptionMessageBoxManagerPage*>(
            RKContext::sInstance->m_scene->getPage(0xC6));

    page->m_option = 0;

    m_nextPage = 0xC6;
    f32 delay = button->getSelectDelay();
    startTransitionOut(SLIDE_FORWARD, delay);
}

void SettingsPage::selectGhostData(UI::PushButton* button)
{
    UI::MessageWindowNoButtonPage* window =
        RuntimeTypeInfo::cast<UI::MessageWindowNoButtonPage*>(
            RKContext::sInstance->m_scene->getPage(0xC8));

    window->setTitleText(0x2801, nullptr);
    window->setWindowText(0x2802, nullptr);
    window->m_pressAEvent = &m_fun_messageWindowEvent;

    m_nextPage = 0xC8;
    f32 delay = button->getSelectDelay();
    startTransitionOut(SLIDE_FORWARD, delay);
}

void SettingsPage::selectLicenseSettings(UI::PushButton* button)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    f32 delay = button->getSelectDelay();
    startSceneTransition(UI::SCENE_LICENSE_SETTINGS, SLIDE_FORWARD, delay);
}

void SettingsPage::messageWindowEvent(UI::MessageWindowPage* page, int r5)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    page->startSceneTransition(UI::SCENE_OPTIONS, SLIDE_FORWARD, 0);
}

int SettingsPage::getNextPageID()
{
    return m_nextPage;
}

void LicenseSettings_onBackPress(UI::UIPage* page)
{
    UI::SceneBGMControllerInstance->enableBGMPersist();
    // aka Options from License Settings
    page->startSceneTransition(UI::SCENE_INSTALL_CHANNEL,
                               UI::UIPage::SLIDE_BACK, 0);
}

void LicenseSelect_optionsButton(UI::PushButton* button)
{
    button->m_hide = true;
    button->m_selectable = 0;
}

extern Instruction<1> Patch_LicenseSettingsBack;
extern Instruction<1> Patch_LicenseSelectOptions;
void SettingsPage::staticInit()
{
    Patch_LicenseSettingsBack.setB(LicenseSettings_onBackPress);
    Patch_LicenseSelectOptions.setBL(LicenseSelect_optionsButton);
}