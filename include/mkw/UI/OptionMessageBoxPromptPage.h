#pragma once
#include "Function.h"
#include "UIInputManager.h"
#include "UIPage.h"

// A message box with two or three buttons, used on the options menu as page
// 0xC3 and 0xC4.
class OptionMessageBoxPromptPage : public UIPage
{
public:
    /* 0x805FE5F8 */
    OptionMessageBoxPromptPage();
    /* 0x805FE728 */
    virtual ~OptionMessageBoxPromptPage();

    /* 0x805FE7D4 */
    virtual void onInit();
    /* 0x805FEA58 */
    virtual void onShow();
    /* 0x805FEA88 */
    virtual void onReturn();

    /* func: 0x80601034, typeinfo: 0x809C1CF4 */
    INSTANTIATE_TYPEINFO;
};