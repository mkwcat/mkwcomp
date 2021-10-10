#pragma once
#include <mkw/UI/Scene.h>
#include <mkw/UI/UIPage.h>

#define SAVEMANAGER_PAGE_ID 0x00

class SaveManagerPage : public UI::UIPage
{
public:
    SaveManagerPage();
    virtual ~SaveManagerPage();

    static void build(UI::Scene* scene);

    virtual void onInit();
    virtual void onDeinit();

protected:
    UI::PageEventBase m_events;

public:
    INSTANTIATE_TYPEINFO;
};