#pragma once
#include <rvl/types.h>

namespace UI
{

namespace SceneKind
{
enum { Menu = 1, Race = 2, Test = 3, Globe = 4 };
}

typedef u32 SceneID;

class UIPage;

// thing in menudata
class Scene
{
public:
    void buildPage(s32 page);
    void showPageOnTop(s32 page);

    void registerPage(s32 index, UIPage* page) {
        m_pages[index] = page;
    }

    UIPage* getPage(s32 index) {
        return m_pages[index];
    }

    SceneID m_sceneId;
    u32 _4;
    UIPage* m_pages[210];
};

extern class MenuData
{
public:
    void setNextScene(int nextScene, int r5);
    void startSceneTransition(int delay, u32 rgbaBgColor);

    Scene* m_scene;
}* MenuDataInstance;

} // namespace UI