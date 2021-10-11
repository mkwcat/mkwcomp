#pragma once
#include <mkw/UI/UIPageManager.h>

class RKContext
{
public:
    static RKContext* sInstance;

    void setNextScene(int nextScene, int r5);
    void startSceneTransition(int delay, u32 rgbaBgColor);

    UI::UIPageManager* m_scene;
};