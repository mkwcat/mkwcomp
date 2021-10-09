#include "SaveManagerPage.h"
#include <rvl/os.h>

UI::AutoTypeInfo<UI::UIPage> SaveManagerPage::sTypeInfo;

SaveManagerPage::SaveManagerPage()
{
}

SaveManagerPage::~SaveManagerPage()
{
}

SaveManagerPage* SaveManagerPage::getStaticInstance()
{
    return UI::UIPage::cast<SaveManagerPage>(
        UI::MenuDataInstance->m_scene->getPage(SAVEMANAGER_PAGE_ID));
}

static void waitForSaveData()
{
    while (CompFile::sInstance->m_saveDataStatus == CompFile::SAVE_WAITING) {
        OSSleepTicks(OSMillisecondsToTicks(16));
    }

    while (CompFile::sInstance->m_ghostDataStatus == CompFile::SAVE_WAITING) {
        OSSleepTicks(OSMillisecondsToTicks(16));
    }
}

void SaveManagerPage::onInit()
{
    m_events.init(0, 0);
    setEventController(&m_events);

    waitForSaveData();
}

void SaveManagerPage::onDeinit()
{
    waitForSaveData();

    if (CompFile::sInstance->m_saveDataStatus != CompFile::SAVE_OK ||
        CompFile::sInstance->m_ghostDataStatus != CompFile::SAVE_OK) {
        // TODO: transition to a "save corrupted" screen
        OSReport("SaveManagerPage: m_saveDataStatus: %d, m_saveFsError: %d\n"
                 "                 m_ghostDataStatus: %d, m_ghostFsError: %d\n",
                 CompFile::sInstance->m_saveDataStatus,
                 CompFile::sInstance->m_saveFsError,
                 CompFile::sInstance->m_ghostDataStatus,
                 CompFile::sInstance->m_ghostFsError);
        while (1) {
        }
    }
}

void SaveManagerPage::build(UI::Scene* scene)
{
    SaveManagerPage* page = new SaveManagerPage();
    scene->registerPage(SAVEMANAGER_PAGE_ID, page);
    page->init(SAVEMANAGER_PAGE_ID);
}