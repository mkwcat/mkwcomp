#pragma once
#include <mkw/UI/Scene.h>
#include <mkw/UI/UIPage.h>

#define SAVEMANAGER_PAGE_ID 0x00

class SaveManagerPage : public UI::UIPage
{
public:
    SaveManagerPage();
    virtual ~SaveManagerPage();

    static SaveManagerPage* getStaticInstance();
    static void build(UI::Scene* scene);

    virtual void onInit();
    virtual void onDeinit();

protected:
    UI::PageEventBase m_events;

public:
    static UI::AutoTypeInfo<UI::UIPage> sTypeInfo;
    virtual const UI::TypeInfo* getTypeInfo()
    {
        return &sTypeInfo;
    }
};