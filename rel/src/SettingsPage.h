#pragma once
#include <mkw/UI/CtrlMenuBackButton.h>
#include <mkw/UI/CtrlMenuPageTitleText.h>
#include <mkw/UI/Function.h>
#include <mkw/UI/MessageWindowPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/UIInputManager.h>
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

    void messageWindowEvent(UI::MessageWindowPage* page, int r5);

protected:
    UI::PushButton m_rumbleButton;
    UI::PushButton m_ghostDataButton;
    UI::PushButton m_licenseButton;

    UI::CtrlMenuPageTitleText m_titleText;
    UI::CtrlMenuBackButton m_backButton;

    UI::UIInputManagerMenu m_inputs;

    UI::FunctionImp<SettingsPage, UI::PushButton*, int> m_fun_onButtonSelect;
    UI::FunctionImp<SettingsPage, int, int> m_fun_onBackPress;
    UI::FunctionImp<SettingsPage, UI::MessageWindowPage*, int>
        m_fun_messageWindowEvent;

    int m_nextPage;

public:
    INSTANTIATE_TYPEINFO;
};

class SettingsGhostDataPage : public UI::UIPage
{
public:
    static const int s_pageId = 0xCA;

    SettingsGhostDataPage();
    virtual ~SettingsGhostDataPage();
    virtual int getNextPageID();
    virtual void onInit();
    virtual void onIn();
    virtual void onChildPageOut();

    void windowOut(UI::MessageWindowPage* page, int r5);

    UI::UIInputManager m_inputs;
    UI::FunctionImp<SettingsGhostDataPage, UI::MessageWindowPage*, int> m_fun_windowOut;

    int m_nextPage;
};