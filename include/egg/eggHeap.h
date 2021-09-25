#pragma once
#include <rvl/types.h>
#include <egg/eggDisposer.h>

namespace EGG
{

class Heap : public Disposer
{
public:
    virtual ~Heap();
protected:
    /* Not included */
    virtual s32 _0(); // getHeapKind
    virtual s32 _1(); // initAllocator
public:
    virtual void* alloc(u32 len, s32 align) = 0;
    virtual void free(void* block) = 0;
protected:
    /* Not included */
    virtual s32 _2(); // destroy
    virtual s32 _3(); // resizeForMBlock
    virtual s32 _4(); // getAllocatableSize
    virtual s32 _5(); // adjust

    /* Data not included */
};

}