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
    void setHighlightEvent(EventBase* event);

    void readLayout(const char* lytSection, const char* ctrlName,
                    const char* positionEntry, int playerCount, int,
                    bool pointerExclusive);
    
    void setHighlighted(int player);
    void somethingHighlightRelated(int player);

    f32 getSelectDelay();

    ButtonEventBase m_events;

protected:
    Event<PushButton, int, int> m_defaultHighlightEvent;
    Event<PushButton, int, int> m_defaultUnhighlightEvent;
    Event<PushButton, int, int> m_defaultSelectEvent;

public:
    EventBase* m_highlightEvent;
    EventBase* m_unhighlightEvent;
    EventBase* m_selectEvent;

    u32 m_id;
    u32 m_playerCount;

    void* m_somePane;
    void* m_somePane2;

    s32 m_selectSoundId;
};

static_assert(sizeof(PushButton) == 0x254, "sizeof(PushButton) != 0x254");

} // namespace UI