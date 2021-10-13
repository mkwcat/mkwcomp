#pragma once
#include "LayoutUIControl.h"

namespace UI
{

class MessageWindowControl : public LayoutUIControl
{
public:
    /* 0x805F9700 */
    MessageWindowControl();
    /* 0x805F973C */
    virtual ~MessageWindowControl();

    /* vtable: 0x808B9EE0 */

    /* 0x805F9794 */
    void readWindowLayout(const char* lytSection, const char* ctrlName,
                          const char* positionEntry);

    /* 0x805F9E40 */
    INSTANTIATE_TYPEINFO;
    /* 0x805F96F4 */
    virtual const char* getTypeName();
};

} // namespace UI