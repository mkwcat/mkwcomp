#pragma once
#include "MesgRes.h"
#include "UIControl.h"
#include <rvl/types.h>

namespace UI
{

class SomeAnimation
{
public:
    void doSomething(int, f32);
    u8 fill[0x44];
};

class SomeAnimationContainer
{
public:
    SomeAnimation* getIndex(int);
    u8 fill[0x10];
};

class LayoutUIControl : public UIControl
{
public:
    LayoutUIControl();
    virtual ~LayoutUIControl();

    virtual void _38()
    {
    }

    void setAllText(int msgId, UI::MesgRes::FormatParam* param);
    void setPaneText(const char* pane, int msgId,
                     UI::MesgRes::FormatParam* param);
    void setTexture(const char* pane, const char* texture);

    SomeAnimationContainer m_anim;
    char fill[0x9C];
    MesgRes m_bmg;
    MesgRes m_commonBmg;
    void* m_iconPane;
    void* m_mainPane;
};
static_assert(sizeof(LayoutUIControl) == 0x174,
              "sizeof(LayoutUIControl) != 0x174");

class CtrlRes
{
public:
    CtrlRes(LayoutUIControl* parent);

    void readFile(const char* lytSection, const char* ctrlName,
                  const char* positionEntry, const char** animations);

    LayoutUIControl* m_parent;
    char fill[0x20];
};

}; // namespace UI