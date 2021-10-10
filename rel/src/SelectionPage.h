#pragma once
#include <mkw/UI/CtrlMenuBackButton.h>
#include <mkw/UI/CtrlMenuPageTitleText.h>
#include <mkw/UI/LayoutUIControl.h>
#include <mkw/UI/SheetSelectControl.h>
#include <mkw/UI/UIPage.h>

class SelectionPage : public UI::UIPage
{
public:
    SelectionPage();
    virtual ~SelectionPage();

    virtual void onInit();
    virtual int getNextPageID();

public:
    void updatePageNumText();
    void updateButtonTexture();
    void updateCompetitionName();
    int buttonCompId(int buttonId);
    int compIdButton(int compId);

protected:
    void onSelectEvent(UI::PushButton* button, int r5);
    void onFreeToSelectEvent(UI::PushButton* button, int r5);
    void onBackEvent(int r4, int r5);
    void onArrowRightEvent(UI::SheetSelectControl* arrow, int r5);
    void onArrowLeftEvent(UI::SheetSelectControl* arrow, int r5);

protected:
    UI::PushButton m_buttons[10];
    UI::SheetSelectControl m_arrows;
    UI::LayoutUIControl m_pageNumControl;
    UI::LayoutUIControl m_compName;

    UI::CtrlMenuPageTitleText m_titleText;
    UI::CtrlMenuBackButton m_backButton;

    UI::PageEventSelection m_events;

    int m_nextPage;

    UI::Event<SelectionPage, UI::PushButton*, int> m_ptr_onSelectEvent;
    UI::Event<SelectionPage, UI::PushButton*, int> m_ptr_onFreeToSelectEvent;
    UI::Event<SelectionPage, int, int> m_ptr_onBackEvent;
    UI::Event<SelectionPage, UI::SheetSelectControl*, int> m_ptr_onArrowLeftEvent;
    UI::Event<SelectionPage, UI::SheetSelectControl*, int>
        m_ptr_onArrowRightEvent;

    int m_pageNum;
    int m_selectedButtonId;
    int m_selectedCompId;

public:
    static int s_lastCompId;

public:
    INSTANTIATE_TYPEINFO;
};