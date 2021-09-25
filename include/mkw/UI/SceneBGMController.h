#pragma once
#include <rvl/types.h>

namespace UI
{

extern class SceneBGMController
{
public:
    /* BGM continues playing through scene transition */
    void enableBGMPersist();

} * SceneBGMControllerInstance;

} // namespace UI