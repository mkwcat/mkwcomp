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

    /* 0x80635EC4 */
    SheetSelectControl();
    /* 0x8063607C */
    virtual ~SheetSelectControl();

    /* 0x80636120 */
    void readLayout(const char* lytSection, const char* ctrlName1,
                    const char* positionEntry1, const char* ctrlName2,
                    const char* positionEntry2, int playerCount, int,
                    bool pointerExclusive);

    /* 0x80636264 */
    void setEnabledArrows(bool leftEnabled, bool rightEnabled);

    /* 0x098 */ EventBase* m_rightEvent;
    /* 0x09C */ EventBase* m_leftEvent;
    /* 0x0A0 */ u32 m_A0;
    /* 0x0A4 */ u32 m_A4;
    /* 0x0A8 */ SheetSelectButton m_buttonRight;
    /* 0x2F0 */ SheetSelectButton m_buttonLeft;
};
static_assert(sizeof(SheetSelectControl) == 0x538,
              "sizeof(SheetSelectControl) != 0x538");

} // namespace UI