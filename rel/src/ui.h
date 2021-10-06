#pragma once

#include <mkw/UI/Scene.h>
#include <mkw/UI/PushButton.h>
#include <rvl/types.h>

#define BACKGROUND_PAGE_ID 0x5C
#define TOURNAMENT_SELECT_PAGE_ID 0x8C
#define TOURNAMENT_SELECT_SCENE_ID 0x85
#define TOURNAMENT_SCENE_ID 0x2D
#define LICENSE_SETTINGS_SCENE_ID 0x47
#define SETTINGS_SCENE_ID 0x8C

#define MID_SETTINGS 0x1B58

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
void hudQuitReplayHook();
int resultMusicHook(int bgmId);