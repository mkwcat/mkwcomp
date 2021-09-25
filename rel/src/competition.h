#pragma once
#include "file.h"
#include <egg/eggFile.h>
#include <egg/eggTaskThread.h>
#include <mkw/LeaderboardEntry.h>
#include <mkw/MiiData.h>
#include <mkw/RaceTime.h>
#include <mkw/common.h>
#include <rvl/types.h>

namespace RKC
{

struct FileObjective {
    u32 rkcoMagic;
    u16 gameMode;
    u8 courseId;
    u8 engineClass;
    u8 lapCount;
    u8 pad_0x9;
    enum { RESTRICTION_KARTS_ONLY, RESTRICTION_BIKES_ONLY, RESTRICTION_NONE };
    u16 vehicleRestriction;
    u16 cameraAngle;
    u16 minimapObject;
    u16 unknown_0x10;
    u16 unknown_0x12;
    u16 cannonFlag;
    u16 cpuCount;
    u8 cpu[22];
    bool wiiWheelOnly;
    u8 pad_0x2F;
    u16 commonObjSetting;
    u16 requiredScore;
    u8 introSetting;
    u8 pad_0x35;
    u16 unknown_0x36;
    u8 pad_0x38[2];
    u16 checksum;
};
static_assert(sizeof(FileObjective) == 0x3C, "sizeof(FileObjective) != 0x3C");

struct FileHeader {
    u32 rkctMagic;
    u32 fileSize;
    u32 archiveOffset;
    u32 unknown;
    FileObjective objective;
};
static_assert(sizeof(FileHeader) == 0x4C, "sizeof(FileHeader) != 0x4C");

} // namespace RKC

struct LdbFileEntry {
    MiiData mii; // size 0x4A
    u16 miiChecksum; // crc16

    u32 minutes : 7;
    u32 seconds : 7;
    u32 milliseconds : 10;

    u32 vehicleId : 6;
    u8 isEnabled : 1;
    u8 characterId : 7;
    u8 controllerId : 3;

    u8 unk_51_3 : 5;
    u8 fill[14];
} __attribute__((packed));

#define LDB_FILE_SIZE (sizeof(LdbFileEntry) * 5)

class CompFile
{
public:
    static CompFile* sInstance;

    virtual ~CompFile();
    CompFile();

    bool isTaskExist() const;
    bool isFileAvailable() const;
    int compId() const;
    u8* data();
    RKC::FileHeader* header();
    void switchCompetition(int compId);
    void rewriteLeaderboard();
    void readFile();
    void getLeaderboardPath(char* path);
    bool readLdbFile();
    void openLdbFile();
    void writeLdbTask();
    void setText(const wchar_t* title, const wchar_t* explanation);

    void getLdbEntry(u8 position, LeaderboardEntry* entry);
    int getTimeLdbPosition(RaceTime* time);
    void insertTimeInLdb(LeaderboardEntry* entry, u32 position);

    const wchar_t* m_compTitle;
    const wchar_t* m_compExplanation;

private:
    EGG::TaskThread* m_thread;

    NandFile* m_ldbFile;
    LdbFileEntry m_leaderboard[5] ATTRIBUTE_ALIGN(32);

    union {
        u8 m_rkcData[0x4800] ATTRIBUTE_ALIGN(32);
        RKC::FileHeader m_rkc;
    };

    int m_compId;
    bool m_isFileAvailable;
    bool m_isLdbAvailable;
};

struct CompInfo {
    u8 unk_0x0;
    const void* rkcData;
    u32 unk_0x8;
    u32 unk_0xC;
    const wchar_t* titleText;
    u32 titleTextLen;
    u8 unk_0x18;
};

int checkForCompetitionReplace(u8* r3, CompInfo* info);
const wchar_t* getCompetitionTextReplace(u8* r3, u32* len);
int getTimeLdbPosition(u8* r3, RaceTime* time);
void insertTimeInLdb(u8* r3, LeaderboardEntry* entry, int position);
void getLdbEntry(u8* r3, u8 position, LeaderboardEntry* entry);