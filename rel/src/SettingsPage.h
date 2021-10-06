#pragma once
#include <mkw/UI/CtrlMenuBackButton.h>
#include <mkw/UI/CtrlMenuPageTitleText.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/UIPage.h>

class SettingsPage : public UI::UIPage
{
public:
    SettingsPage();
    virtual ~SettingsPage();

    virtual void onInit();
    virtual void onShow();
    virtual int getNextPageID();

protected:
    void onButtonSelect(UI::PushButton* button, int r5);
    void onBackPress(int r4, int r5);

protected:
    UI::PushButton m_rumbleButton;
    UI::PushButton m_seedButton;
    UI::PushButton m_licenseButton;

    UI::CtrlMenuPageTitleText m_titleText;
    UI::CtrlMenuBackButton m_backButton;

    UI::PageEventSelection m_events;

    UI::Event<SettingsPage, UI::PushButton*, int> m_ptr_onButtonSelect;
    UI::Event<SettingsPage, int, int> m_ptr_onBackPress;

    int m_nextPage;

public:
    static UI::AutoTypeInfo<UI::UIPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};