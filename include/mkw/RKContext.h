#pragma once
#include <mkw/UI/UIPageManager.h>

class RKContext
{
public:
    static RKContext* sInstance;

    void setNextScene(int nextScene, int r5);
    void startSceneTransition(int delay, u32 rgbaBgColor);

    UI::UIPageManager* m_scene;
    u8 fill_0x4[0x94];

    struct {
        u8 fill[0x4E8];
        u8 m_licenseId;
        u8 fill_0x4E9[0x510 - 0x4E9];
    } * m_98;
};