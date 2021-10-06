#include "ForcedHandleBypassPage.h"

ForcedHandleBypassPage::ForcedHandleBypassPage()
    : m_ptr_selectYes(this, &ForcedHandleBypassPage::selectYes)
{
    m_noResume = false;
    m_wiiWheelPageDisabled = false;
}

ForcedHandleBypassPage::~ForcedHandleBypassPage()
{
}

void ForcedHandleBypassPage::onInit()
{
    CompFile::sInstance->m_forceHandleDisabled = false;
    setEventController(&m_events);
}

void ForcedHandleBypassPage::onShow()
{
    UI::MessageYesNoBoxPage* msgPage =
        UI::UIPage::cast<UI::MessageYesNoBoxPage>(
            UI::MenuDataInstance->m_scene->getPage(0x4E));

    msgPage->configMessage(0x2800, nullptr);
    msgPage->configOption(0, 0xFAC, nullptr, 1, &m_ptr_selectYes);
    msgPage->configOption(1, 0xFAD, nullptr, -1, nullptr);
    m_noResume = false;
    showNextPage(0x4E, 0);
}

void ForcedHandleBypassPage::selectYes(UI::MessageYesNoBoxPage* page,
                                       UI::PushButton* button)
{
    CompFile::sInstance->m_forceHandleDisabled = true;

    const int sceneId = UI::MenuDataInstance->m_scene->m_sceneId;
    if (sceneId == 0x88) {
        // Normal tournament intro
        UI::MenuDataInstance->setNextScene(0x2D, 0);
    } else if (sceneId == 0x89) {
        // For bosses specifically
        UI::MenuDataInstance->setNextScene(0x1D, 0);
    }

    f32 delay = button->getSelectDelay();
    UI::MenuDataInstance->startSceneTransition((int)delay, 0x000000FF);

    UI::UIPage* lastPage = UI::MenuDataInstance->m_scene->getPage(0xBA);
    lastPage->startTransitionOut(UI::UIPage::SLIDE_FORWARD, delay);

    m_noResume = true;
}

void ForcedHandleBypassPage::onReturn()
{
    UI::UIPage* lastPage = UI::MenuDataInstance->m_scene->getPage(0xBA);
    if (!m_noResume) {
        // These calls emulate two functions required to dereference the
        // current controller
        lastPage->onShow();
        lastPage->_3C();
        m_wiiWheelPageDisabled = false;
    }
    startTransitionOut(UI::UIPage::SLIDE_FORWARD, 0);
}

int ForcedHandleBypassPage::isWiiWheelPageDisabled()
{
    ForcedHandleBypassPage* page = UI::UIPage::cast<ForcedHandleBypassPage>(
        UI::MenuDataInstance->m_scene->getPage(0x87));
    return page->m_wiiWheelPageDisabled;
}
void ForcedHandleBypassPage::setWiiWheelPageDisabled(bool set)
{
    ForcedHandleBypassPage* page = UI::UIPage::cast<ForcedHandleBypassPage>(
        UI::MenuDataInstance->m_scene->getPage(0x87));
    page->m_wiiWheelPageDisabled = set;
}

UI::AutoTypeInfo<UI::UIPage> ForcedHandleBypassPage::sTypeInfo;

void wiiWheelPageRejectController(UI::UIPage* page)
{
    if (ForcedHandleBypassPage::isWiiWheelPageDisabled())
        return;

    ForcedHandleBypassPage::setWiiWheelPageDisabled(true);
    page->showNextPage(0x87, 0);
}

extern Instruction<11> Patch_WiiWheelOnlyPage;
void ForcedHandleBypassPage::staticInit()
{
    Patch_WiiWheelOnlyPage.setBL(wiiWheelPageRejectController);
    Patch_WiiWheelOnlyPage.setB(&Patch_WiiWheelOnlyPage.m_instr[11], 1);
}