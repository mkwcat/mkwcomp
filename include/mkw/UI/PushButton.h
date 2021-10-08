#pragma once
#include "Event.h"
#include "LayoutUIControl.h"
#include <rvl/types.h>

namespace UI
{

class ButtonEventBase
{
    u32 fill[2]; // some struct, has its own constructor
public:
    ButtonEventBase();
    virtual ~ButtonEventBase();

    u8 fill2[0x78];
};

class PushButton : public LayoutUIControl
{
public:
    PushButton();
    virtual ~PushButton();
    virtual void _3C();
    virtual void onFreeToSelect();
    virtual void onSelectToFree();
    virtual void onSelect();

    void setSelectEvent(EventBase* event, int);
    void setFreeToSelectEvent(EventBase* event);

    void readLayout(const char* lytSection, const char* ctrlName,
                    const char* positionEntry, int playerCount, int,
                    bool pointerExclusive);

    void setSelected(int player);
    void freeToSelect(int player);

    f32 getSelectDelay();

    /* 0x174 */ ButtonEventBase m_events;

protected:
    Event<PushButton, int, int> m_defaultFreeToSelectEvent;
    Event<PushButton, int, int> m_defaultSelectToFreeEvent;
    Event<PushButton, int, int> m_defaultSelectEvent;

public:
    /* 0x234 */ EventBase* m_freeToSelectEvent;
    /* 0x238 */ EventBase* m_selectToFreeEvent;
    /* 0x23C */ EventBase* m_selectEvent;

    /* 0x240 */ u32 m_id;
    /* 0x244 */ int m_selectable;

    /* 0x248 */ void* m_somePane;
    /* 0x24C */ void* m_somePane2;

    /* 0x250 */ s32 m_selectSoundId;
};

static_assert(sizeof(PushButton) == 0x254, "sizeof(PushButton) != 0x254");

} // namespace UI