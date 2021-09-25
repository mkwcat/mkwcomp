#pragma once
#include "LayoutUIControl.h"
#include <rvl/types.h>

namespace UI
{

class CtrlMenuPageTitleText : public LayoutUIControl
{
public:
    virtual void _20();
    virtual void _28();
    virtual const char* getKindString();

    void initLayout(int r4);
};

} // namespace UI