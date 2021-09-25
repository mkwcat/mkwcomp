#pragma once
#include "PushButton.h"
#include <rvl/types.h>

namespace UI
{

class CtrlMenuBackButton : public PushButton
{
public:
    CtrlMenuBackButton() : msgId(0x7D1), m_258(0), m_25C(0) {}

    virtual void initInternal();
    virtual void calcInternal();
    virtual void _20();
    virtual void _28();
    virtual const char* getKindString();

    void initLayout(int playerCount)
    {
        readLayout("button", "Back", "ButtonBack", playerCount, 1, true);
        m_id = -100;
        m_7C = 400;
    }

    int msgId;
    int m_258;
    f32 m_25C;
    int m_260;
};

static_assert(sizeof(CtrlMenuBackButton) == 0x264,
              "sizeof(CtrlMenuBackButton) != 0x264");

} // namespace UI