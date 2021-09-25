#pragma once
#include <rvl/types.h>

namespace EGG
{

class Disposer
{
public:
    virtual ~Disposer();
    Disposer();
private:
    u8 fill[0x28];
};

}