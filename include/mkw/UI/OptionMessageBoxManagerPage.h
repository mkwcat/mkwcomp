#pragma once
#include "Function.h"
#include "UIInputManager.h"
#include "UIPage.h"
#include <rvl/types.h>

namespace UI
{

class OptionMessageBoxManagerPage : UIPage
{
public:
    /* 0x805FF328 */
    OptionMessageBoxManagerPage();
    /* 0x805FF3A4 */
    virtual ~OptionMessageBoxManagerPage();

    /* 0x805FF40C */
    virtual void onInit();
    /* 0x805FF478 */
    virtual void onShow();
    /* 0x805FF4E0 */
    virtual void _4C();
    /* 0x805FF6C4 */
    virtual void onReturn();

    /* 0x80601014 */
    virtual int getNextPageID();
    /* func: 0x8060101C typeinfo: 0x809C1CFC */
    INSTANTIATE_TYPEINFO;

protected:
    /* 0x80600F88 */
    /* 0x44 */ FunctionImp<OptionMessageBoxManagerPage, int, int>
        m_ptr_event0x44;
    /* 0x58 */ UIInputManager m_inputs;

public:
    /* 0x68 */ int m_option;
    /* 0x6C */ int unk_0x6C; // probably nwc24 related
    /* 0x70 */ int m_nextPage;
    /* 0x74 */ int unk_0x74;
};
static_assert(sizeof(OptionMessageBoxManagerPage) == 0x78,
              "sizeof(OptionMessageBoxManagerPage) != 0x78");

} // namespace UI