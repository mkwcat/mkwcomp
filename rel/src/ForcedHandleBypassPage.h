#pragma once
#include <mkw/UI/Function.h>
#include <mkw/UI/MessagePopupTwoOptionPage.h>
#include <mkw/UI/PushButton.h>
#include <mkw/UI/UIInputManager.h>
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

    void selectYes(UI::MessagePopupTwoOptionPage* page, UI::PushButton* button);

    static int isWiiWheelPageDisabled();
    static void setWiiWheelPageDisabled(bool set);

protected:
    bool m_noResume;
    bool m_wiiWheelPageDisabled;

    UI::FunctionImp<ForcedHandleBypassPage, UI::MessagePopupTwoOptionPage*,
                    UI::PushButton*>
        mf_imp_selectYes;
    UI::UIInputManagerMenu m_inputs;

public:
    INSTANTIATE_TYPEINFO;
};