#pragma once
#include "LayoutUIControl.h"
#include "UIPage.h"
#include <rvl/types.h>

namespace UI
{

class TitleScreenPage : public UIPage
{
public:
    TitleScreenPage();
    virtual ~TitleScreenPage();

    void hideBackground(bool value) { m_background.m_invisible = value; }

protected:
    PageEventBase m_events;
    LayoutUIControl m_pressStart; // actually CtrlMenuPressStart
    LayoutUIControl m_background;
    u8 fill[0x14]; // I forgot what this could be
};

static_assert(sizeof(TitleScreenPage) == 0x350, "sizeof(TitleScreenPage) != 0x350");

} // namespace UI