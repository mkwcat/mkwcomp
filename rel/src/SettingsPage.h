#pragma once
#include <mkw/UI/CtrlMenuBackButton.h>
#include <mkw/UI/CtrlMenuPageTitleText.h>
#include <mkw/UI/MessageWindowPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/UIPage.h>

class SettingsPage : public UI::UIPage
{
public:
    static void staticInit();

    SettingsPage();
    virtual ~SettingsPage();

    virtual void onInit();
    virtual int getNextPageID();

protected:
    void onButtonSelect(UI::PushButton* button, int r5);
    void onBackPress(int r4, int r5);

    void selectRumble(UI::PushButton* button);
    void selectGhostData(UI::PushButton* button);
    void selectLicenseSettings(UI::PushButton* button);

    void messageWindowEvent(UI::OptionMessageWindowPage* page, int r5);

protected:
    UI::PushButton m_rumbleButton;
    UI::PushButton m_ghostDataButton;
    UI::PushButton m_licenseButton;

    UI::CtrlMenuPageTitleText m_titleText;
    UI::CtrlMenuBackButton m_backButton;

    UI::PageEventSelection m_events;

    UI::Event<SettingsPage, UI::PushButton*, int> m_ptr_onButtonSelect;
    UI::Event<SettingsPage, int, int> m_ptr_onBackPress;
    UI::Event<SettingsPage, UI::OptionMessageWindowPage*, int>
        m_ptr_messageWindowEvent;

    int m_nextPage;

public:
    INSTANTIATE_TYPEINFO;
};