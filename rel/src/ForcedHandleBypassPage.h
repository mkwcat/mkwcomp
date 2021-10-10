#pragma once
#include <mkw/UI/MessageYesNoBoxPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/UIPage.h>
#include <rvl/types.h>

// The page that manages the popup choice that appears when you try to use a
// wrong controller on a Wii Wheel only tournament.
class ForcedHandleBypassPage : public UI::UIPage
{
public:
    static void staticInit();

    ForcedHandleBypassPage();
    virtual ~ForcedHandleBypassPage();

    virtual void onInit();
    virtual void onShow();
    virtual void onReturn();

    void selectYes(UI::MessageYesNoBoxPage* page, UI::PushButton* button);

    static int isWiiWheelPageDisabled();
    static void setWiiWheelPageDisabled(bool set);

protected:
    bool m_noResume;
    bool m_wiiWheelPageDisabled;

    UI::Event<ForcedHandleBypassPage, UI::MessageYesNoBoxPage*, UI::PushButton*>
        m_ptr_selectYes;
    UI::PageEventBase m_events;

public:
    INSTANTIATE_TYPEINFO;
};