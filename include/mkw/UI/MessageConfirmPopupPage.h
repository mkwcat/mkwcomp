#pragma once
#include "Function.h"
#include "LayoutUIControl.h"
#include "PushButton.h"
#include "UIPage.h"
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

class MessageConfirmPopupPage : public UI::UIPage
{
private:
    MessageConfirmPopupPage(); // just don't create one of these lol
public:
    void configMessage(int msgId, UI::MesgRes::FormatParam* param);
    void
    configOption(int num, int msgId, UI::MesgRes::FormatParam* param, int r7,
                 FunctionBase<MessageConfirmPopupPage*, PushButton*>* event);

    INSTANTIATE_TYPEINFO;
};

} // namespace UI