#include "CompFile.h"
#include "patch.h"
#include "util.h"
#include <algorithm>
#include <egg/eggDvdFile.h>
#include <mkw/MenuSet.h>
#include <mkw/Random.h>
#include <mkw/SaveDataManager.h>
#include <rvl/ipc.h>
#include <rvl/nand.h>
#include <rvl/os.h>
#include <stdio.h>
#include <string.h>

#define MKWCOMP_ROOT "/mkwcomp"
#define MKWCOMP_SAVE_ROOT MKWCOMP_ROOT "/save"

CompFile compFileInstance;
CompFile* CompFile::sInstance = &compFileInstance;

bool CompFile::isTaskExist() const
{
    return m_thread->isTaskExist();
}

bool CompFile::isFileAvailable() const
{
    return m_isFileAvailable;
}

int CompFile::compId() const
{
    return m_compId;
}

u8* CompFile::data()
{
    return m_rkcData;
}

RKC::FileHeader* CompFile::header()
{
    return &m_rkc;
}

CompFile::CompFile()
{
    m_thread = EGG::TaskThread::create(2, 20, 0x1000, nullptr);
    m_isFileAvailable = false;

    if (isRiivolution())
        m_ldbFile = new RiivoFile();
    else
        m_ldbFile = new NandFile();
}

CompFile::~CompFile()
{
}

static inline void getCompPath(int compId, char* out)
{
    sprintf(out, "/Race/Competition/comp%02d.rkc", compId);
}

void CompFile::readFile()
{
    char path[64];
    getCompPath(m_compId, path);

    EGG::DvdFile file;
    if (!file.open(path)) {
        OSReport("ERROR: Failed to open competition %d!\n", m_compId);
        return;
    }

    u32 fileSize = file.getFileSize();
    if (fileSize < sizeof(RKC::FileHeader)) {
        OSReport("ERROR: File is too small to be a competition file (id %d)!\n",
                 m_compId);
        return;
    }
    if (fileSize > sizeof(m_rkcData)) {
        OSReport(
            "ERROR: Competition file is too big to fit in buffer! (id %d)\n",
            m_compId);
        return;
    }

    s32 result = file.readData(reinterpret_cast<void*>(m_rkcData), fileSize, 0);
    if (result != fileSize) {
        OSReport("ERROR: Failed to read header from competition %d!\n",
                 m_compId);
        return;
    }

    m_isFileAvailable = true;
}

static const char* ldbPathRoot()
{
    if (isRiivolution())
        return MKWCOMP_SAVE_ROOT;

    static char sHomeDir[IPC_MAX_PATH + 1];
    static bool sGotHomeDir = false;

    if (!sGotHomeDir) {
        NANDGetHomeDir(sHomeDir);
        sGotHomeDir = true;
    }

    return sHomeDir;
}

void CompFile::getLeaderboardPath(char* path)
{
    snprintf(path, 128, "%s/comp%02d.ldb", ldbPathRoot(), m_compId);
}

void CompFile::getGhostDataPath(char* path)
{
    snprintf(path, 128, "%s/comp%02d.rkg", ldbPathRoot(), m_compId);
}

bool CompFile::readLdbFile()
{
    if (m_ldbFile->getFileSize() < sizeof(m_leaderboard)) {
        OSReport("ERROR: Leaderboard file invalid size\n");
        return false;
    }

    s32 ret = m_ldbFile->readData(&m_leaderboard, sizeof(m_leaderboard), 0);
    if (ret != sizeof(m_leaderboard)) {
        OSReport("ERROR: Failed to read leaderboard data\n");
        return false;
    }

    return true;
}

void CompFile::openLdbFile()
{
    memset(m_leaderboard, 0, sizeof(m_leaderboard));

    char path[128];
    getLeaderboardPath(path);

    bool ret = m_ldbFile->open(path, NAND_MODE_READ);

    if (!ret) {
        OSReport("Failed to open leaderboard file\n");
        return;
    }

    ret = readLdbFile();
    m_ldbFile->close();

    if (!ret) {
        memset(m_leaderboard, 0, sizeof(m_leaderboard));
        return;
    }
}

void CompFile::writeLdbTask()
{
    char path[128];
    getLeaderboardPath(path);

    bool ret = m_ldbFile->openCreate(path, NAND_MODE_WRITE);

    if (!ret) {
        OSReport("Failed to open leaderboard file\n");
        return;
    }

    s32 sret = m_ldbFile->writeData(&m_leaderboard, sizeof(m_leaderboard), 0);
    m_ldbFile->close();

    if (sret != sizeof(m_leaderboard)) {
        OSReport("ERROR: Leaderboard write failed!\n");
    }
}

void CompFile::writeGhostDataTask()
{
    char path[128];
    getGhostDataPath(path);

    bool ret = m_ldbFile->openCreate(path, NAND_MODE_WRITE);

    if (!ret) {
        OSReport("Failed to open ghost file\n");
        return;
    }

    RKG::File* rkg = SaveDataManager::sInstance->m_rkgFile;
    memset(rkg, 0, sizeof(RKG::File));

    // Using an unused 32-bit field in the RKG to store the seed.
    *(u32*)((u32)rkg + 0x38) = m_ghostSeed;
    m_ghost.makeRKG(rkg);

    s32 sret = m_ldbFile->writeData(rkg, sizeof(RKG::File), 0);
    m_ldbFile->close();

    if (sret != sizeof(RKG::File)) {
        OSReport("ERROR: Ghost write failed!\n");
    }
}

static void taskEntry(void* arg)
{
    CompFile* object = reinterpret_cast<CompFile*>(arg);
    object->readFile();
    object->openLdbFile();
}

static void writeLdbTaskEntry(void* arg)
{
    CompFile* object = reinterpret_cast<CompFile*>(arg);
    object->writeLdbTask();
}

static void writeGhostTaskEntry(void* arg)
{
    CompFile* object = reinterpret_cast<CompFile*>(arg);
    object->writeGhostDataTask();
}

void CompFile::switchCompetition(int compId)
{
    if (compId == m_compId)
        return;

    m_compId = compId;
    m_isFileAvailable = false;
    m_isLdbAvailable = false;

    m_thread->request(taskEntry, reinterpret_cast<void*>(this), nullptr);
}

void CompFile::rewriteLeaderboard()
{
    m_thread->request(writeLdbTaskEntry, reinterpret_cast<void*>(this),
                      nullptr);
}

void CompFile::saveGhostData(GhostData* data, u32 seed)
{
    m_ghost = *data;
    m_ghostSeed = seed;

    m_thread->request(writeGhostTaskEntry, reinterpret_cast<void*>(this),
                      nullptr);
}

void CompFile::setText(const wchar_t* title, const wchar_t* explanation)
{
    m_compTitle = title;
    m_compExplanation = explanation;
}

static bool ldbEntryCompare(LdbFileEntry& entry, GhostData::RaceTime* time)
{
    if (!entry.isEnabled)
        return false;

    if (entry.minutes != time->minutes)
        return entry.minutes < time->minutes;

    if (entry.seconds != time->seconds)
        return entry.seconds < time->seconds;

    if (entry.milliseconds != time->milliseconds)
        return entry.milliseconds < time->milliseconds;

    return true;
}

int CompFile::getTimeLdbPosition(GhostData::RaceTime* time)
{
    // Don't allow any leaderboard positions if the Wii Wheel restriction has
    // been disabled
    if (m_rkc.objective.forceWiiWheel && m_forceHandleDisabled)
        return -1;

    LdbFileEntry* entry = std::lower_bound(&m_leaderboard[0], &m_leaderboard[5],
                                           time, ldbEntryCompare);
    if (entry == &m_leaderboard[5])
        return -1;

    return indexInArray(m_leaderboard, entry);
}

void CompFile::getLdbEntry(u8 position, LeaderboardEntry* entry)
{
    if (position > 4) {
        entry->time.valid = false;
        return;
    }

    LdbFileEntry* ldb = &m_leaderboard[position];

    memcpy(&entry->mii, &ldb->mii, sizeof(MiiData));

    entry->time.minutes = ldb->minutes;
    entry->time.seconds = ldb->seconds;
    entry->time.milliseconds = ldb->milliseconds;

    entry->characterId = ldb->characterId;
    entry->vehicleId = ldb->vehicleId;
    entry->controllerId = ldb->controllerId;

    entry->time.valid = ldb->isEnabled;
}

void CompFile::insertTimeInLdb(LeaderboardEntry* entry, u32 position)
{
    if (position < 4) {
        memmove(&m_leaderboard[position + 1], &m_leaderboard[position],
                (4 - position) * sizeof(LdbFileEntry));
    }

    LdbFileEntry* ldb = &m_leaderboard[position];

    memcpy(&ldb->mii, &entry->mii, sizeof(MiiData));

    ldb->minutes = entry->time.minutes;
    ldb->seconds = entry->time.seconds;
    ldb->milliseconds = entry->time.milliseconds;

    ldb->characterId = entry->characterId;
    ldb->vehicleId = entry->vehicleId;
    ldb->controllerId = entry->controllerId;

    ldb->isEnabled = entry->time.valid;

    rewriteLeaderboard();
}

struct CompInfo {
    u8 unk_0x0;
    const void* rkcData;
    u32 unk_0x8;
    u32 unk_0xC;
    const wchar_t* titleText;
    u32 titleTextLen;
    u8 unk_0x18;
};

int checkForCompetitionReplace(u8* r3, CompInfo* info)
{
    while (!CompFile::sInstance->isFileAvailable()) {
        if (!CompFile::sInstance->isTaskExist())
            return 0;
        OSSleepTicks(OSMillisecondsToTicks(16));
    }

    info->unk_0x0 = 0;
    info->unk_0xC = 1;
    info->unk_0x18 = 1;
    info->unk_0x0 = 1;

    info->titleText = CompFile::sInstance->m_compTitle;
    info->titleTextLen = 5;

    info->rkcData = CompFile::sInstance->data();
    return 1;
}

const wchar_t* getCompetitionTextReplace(u8* r3, u32* len)
{
    return CompFile::sInstance->m_compExplanation;
}

int getTimeLdbPosition(u8* r3, GhostData::RaceTime* time)
{
    return CompFile::sInstance->getTimeLdbPosition(time);
}

void insertTimeInLdb(u8* r3, LeaderboardEntry* entry, int position)
{
    CompFile::sInstance->insertTimeInLdb(entry, position);
}

void getLdbEntry(u8* r3, u8 position, LeaderboardEntry* entry)
{
    CompFile::sInstance->getLdbEntry(position, entry);
}

void saveTournamentGhost(u8* r3, int r4, int r5, GhostData* ghost)
{
    if (!ghost->m_valid)
        return;

    CompFile::sInstance->saveGhostData(
        ghost, MenuSet::sInstance->currentRace.seedSession);
}

// Non-race finish times normally have a 16 ms randomness to them. This patches
// that to always give the best time.
int randomFinishTimeHook(Random* random, int limit)
{
    if (isTournamentMode())
        return 0;

    return random->nextLimited(limit);
}

extern Instruction<1> Patch_Nwc24DlManager_init;
extern Instruction<1> Patch_Nwc24DlManager_CheckForCompetition;
extern Instruction<1> Patch_Nwc24DlManager_GetCompetitionText;
extern Instruction<1> Patch_Nwc24DlManager_GetLdbTimeRank;
extern Instruction<1> Patch_Nwc24DlManager_InsertTimeInLdb;
extern Instruction<1> Patch_Nwc24DlManager_GetLdbEntry;
extern Instruction<1> Patch_SaveTournamentGhost;
extern Instruction<1> Patch_NoRandomFinishTime;
void initCompFilePatches()
{
    Patch_Nwc24DlManager_init.setBlr();
    Patch_Nwc24DlManager_CheckForCompetition.setB(checkForCompetitionReplace);
    Patch_Nwc24DlManager_GetCompetitionText.setB(getCompetitionTextReplace);
    Patch_Nwc24DlManager_GetLdbTimeRank.setB(getTimeLdbPosition);
    Patch_Nwc24DlManager_InsertTimeInLdb.setB(insertTimeInLdb);
    Patch_Nwc24DlManager_GetLdbEntry.setB(getLdbEntry);

    Patch_SaveTournamentGhost.setBL(saveTournamentGhost);
    Patch_NoRandomFinishTime.setBL(randomFinishTimeHook);
}