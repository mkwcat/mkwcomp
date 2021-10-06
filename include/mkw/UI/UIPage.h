#pragma once
#include "Event.h"
#include "Scene.h"
#include "TypeInfo.h"
#include "UIControl.h"
#include <rvl/types.h>

namespace UI
{

class PageEventBase
{
public:
    PageEventBase();
    virtual void _8();
    virtual ~PageEventBase();
    virtual void init(int, int);
    virtual void _14();
    virtual void _18();
    virtual void _1C();
    virtual void _20();
    virtual void _24();
    virtual void _28();
    virtual void _2C();
    virtual void _30();
    virtual void _34();

    u32 m_4;
    u32 m_8;
    u8 m_C;
    u8 m_D;
    u8 m_E;
    u8 m_F;
};
static_assert(sizeof(PageEventBase) == 0x10, "sizeof(PageEventBase) != 0x10");

enum InputIndex
{
    INPUT_BACK = 1,
    INPUT_START = 2
};

class PageEventSelection : public PageEventBase
{
public:
    PageEventSelection();
    virtual ~PageEventSelection();

    void configureEvent(InputIndex type, EventBase* event, u8 r6, u8 r7);

    u8 fill[0xC];
    EventBase* m_events[9];
    u8 m_40[9];
    u8 m_49[9];
    u8 m_52;
    u8 m_53;
    u8 fill2[0x1CC];
    u32 m_220;

    void setScreenWrapSetting(int type);
};

static_assert(sizeof(PageEventSelection) == 0x224,
              "sizeof(PageEventSelection) != 0x224");

class UIPage
{
public:
    UIPage();
    virtual ~UIPage();

    virtual void _C();
    virtual int getNextPageID();
    virtual void _14();
    virtual void _18();

    enum TransitionDir
    {
        SLIDE_FORWARD,
        SLIDE_BACK
    };
    virtual void startSceneTransition(int sceneId, TransitionDir direction,
                                      f32 delay);
    void startTransitionOut(TransitionDir direction, f32 delay);

    virtual void _20();
    virtual void showNextPage(int pageId, int r5);
    virtual void onInit(); // vt + 0x28
    virtual void onDeinit(); // vt + 0x2C
    virtual void onShow(); // vt + 0x30
    virtual void onHide(); // vt + 0x34
    virtual void _38();
    virtual void _3C();
    virtual void _40();
    virtual void _44();
    virtual void _48();
    virtual void _4C();
    virtual void calc();
    virtual void onReturn();
    virtual void _58();
    virtual void _5C();

    // Like C++ RTTI, used for a dynamic_cast like thing
    virtual const TypeInfo* getTypeInfo();
    static TypeInfo sTypeInfo;

    // The code this generates doesn't match!
    template <class T> static T* cast(UIPage* rhs)
    {
        for (const TypeInfo* info = rhs->getTypeInfo(); info != nullptr;
             info = info->parent) {
            if (info == &T::sTypeInfo)
                return reinterpret_cast<T*>(rhs);
        }
        return nullptr;
    }

    void init(s32 id);
    void initControlGroup(int count);
    void insertControl(int index, UIControl* control, int);

    void setEventController(PageEventBase*);

protected:
    s32 m_id;
    u32 m_8;
    bool m_C;

    TransitionDir m_slideDir;
    u32 m_14;
    u32 m_18;
    u32 m_1C;
    u32 m_20;

    UIControlCollection m_children;
    PageEventBase* m_eventController;

    u32 m_3C;
    u32 m_40;
};
static_assert(sizeof(UIPage) == 0x44, "sizeof(UIPage) != 0x44");

} // namespace UI