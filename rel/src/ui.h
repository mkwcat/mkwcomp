#pragma once

#include <mkw/UI/Scene.h>
#include <mkw/UI/PushButton.h>
#include <rvl/types.h>

bool buildPagesReplace(UI::Scene* scene, UI::SceneID id);
bool showBasePagesReplace(UI::Scene* scene, UI::SceneID id);
bool sceneHasBackModelReplace(UI::SceneID id);
s32 sceneGetBGMReplace(UI::SceneID id);
s32 sceneGetBGMGroupReplace(UI::SceneID id);
s32 patchLicenseSelectGetNextScene();

void eventExplanationSelectEvent(UI::UIPage* page, UI::PushButton* button,
                                 int r5);
void eventExplanationBackEvent(UI::UIPage* page, int r4, int r5);
s32 eventExplanationGetNextPage(UI::UIPage* page);

void wiiWheelPageRejectController(UI::UIPage* page);

asm void hudWatchReplayHook();