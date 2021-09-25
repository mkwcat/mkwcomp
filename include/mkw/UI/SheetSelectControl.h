#pragma once
#include "Event.h"
#include "LayoutUIControl.h"
#include "UIControl.h"
#include "UIPage.h"
#include <rvl/types.h>

namespace UI
{

class SheetSelectControl : public UIControl
{
public:
    class SheetSelectButton : public LayoutUIControl
    {
    public:
        /* Like PushButton with some differences */
        SheetSelectButton(); // fake! this is always inlined actually

        ButtonEventBase m_events;

        Event<SheetSelectControl, int, int> m_event_1F8;
        Event<SheetSelectControl, int, int> m_event_20C;
        Event<SheetSelectControl, int, int> m_event_220;

        int m_id;
        int m_playerCount;

        bool m_23C;
        void* m_somePane;
        void* m_somePane2;
    };
    static_assert(sizeof(SheetSelectButton) == 0x248,
                  "sizeof(SheetSelectButton) != 0x248");

    SheetSelectControl();
    virtual ~SheetSelectControl();

    void readLayout(const char* lytSection, const char* ctrlName1,
                    const char* positionEntry1, const char* ctrlName2,
                    const char* positionEntry2, int playerCount, int,
                    bool pointerExclusive);
    
    void setEnabledArrows(bool leftEnabled, bool rightEnabled);

    EventBase* m_rightEvent;
    EventBase* m_leftEvent;
    u32 m_A0;
    u32 m_A4;
    SheetSelectButton m_buttonRight;
    SheetSelectButton m_buttonLeft;
};
static_assert(sizeof(SheetSelectControl) == 0x538,
              "sizeof(SheetSelectControl) != 0x538");

} // namespace UI