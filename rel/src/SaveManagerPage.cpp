#include "SaveManagerPage.h"
#include <mkw/UI/UIPageManager.h>
#include <rvl/os.h>

TYPEINFO_DERIVED(SaveManagerPage, UI::UIPage);

SaveManagerPage::SaveManagerPage()
{
}

SaveManagerPage::~SaveManagerPage()
{
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
    m_inputs.init(0, 0);
    setInputManager(&m_inputs);

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

void SaveManagerPage::build(UI::UIPageManager* scene)
{
    SaveManagerPage* page = new SaveManagerPage();
    scene->setPage(SAVEMANAGER_PAGE_ID, page);
    page->init(SAVEMANAGER_PAGE_ID);
}