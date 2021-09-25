#pragma once
#include "Event.h"
#include "LayoutUIControl.h"
#include "UIPage.h"
#include <rvl/types.h>

namespace UI
{

class MessageYesNoBoxPage : public UI::UIPage
{
private:
    MessageYesNoBoxPage(); // just don't create one of these lol
public:
    void configMessage(int msgId, UI::MesgRes::FormatParam* param);
    void configOption(int num, int msgId, UI::MesgRes::FormatParam* param,
                      int r7, EventBase* event);

    static const TypeInfo s_typeInfo;
};

} // namespace UI