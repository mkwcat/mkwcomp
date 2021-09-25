#include <string.h>
#include <rvl/types.h>
#include <rvl/ipc.h>
#include <rvl/dvd.h>
#include <egg/eggHeap.h>

/* [TODO] Port these to every region. */
const u32 loader_symbols[][4] = {
    { 0x00000000, 0x00000000, 0x801938F8, 0x00000000 }, /*  0: IOS_Open */
    { 0x00000000, 0x00000000, 0x80193AD8, 0x00000000 }, /*  0: IOS_Close */
};

s32 rmc_index = -1;

#define PORT(index) symbols[index][rmc_index];
#define DEFINE_EXTERNAL_FUNCTION(_definition, _index) \
    asm _definition { \
        nofralloc

        li r12, index << 2
        b port_call
    }

asm void port_call()
{
    nofralloc

    lis r11, rmc_index@ha
    lwz r11, rmc_index@l(r11)
    srwi r11, r11, 2
    addis r12, r12, loader_symbols@ha
    addi r12, r12, loader_symbols@l
    lwzx r12, r12, r11
    mtctr r12
    bctr
}

DEFINE_EXTERNAL_FUNCTION(
    s32 IOS_Open()
)








bool relLinkHook();
void loaderMain(void* rel, void* bss, EGG::Heap* heap);
void* loadCustomModule(EGG::Heap* heap);

const char dvdRelPath[] = "/rel/patch_%s.rel";

asm bool relLinkHook()
{
    nofralloc    
    mflr r26

    /* r3 = module, r4 = bss */
    mr r5, r24 // heap
    bl loaderMain
    li r3, 1

    mtlr r26
    blr
}

EGG::DvdFile* makeDvdFile()
{
    /* Avoid having to define the constructor lol */
}






void loaderMain(void* rel, void* bss, EGG::Heap* heap)
{
    char region = *reinterpret_cast<char*>(0x80000003);
    rmc_index = region == 'E' ? 0
              : region == 'J' ? 1
              : region == 'P' ? 2
              : region == 'K' ? 3 : -1;
    assert(rmc_index != -1);


}




bool isDolphin()
{
    /* check for /dev/dolphin */
    s32 fd = IOS_Open("/dev/dolphin", 0);
    if (fd >= 0) {
        IOS_Close(fd);
        return true;
    }
    /* or on an older version of dolphin, this bug will work */
    else if (fd = IOS_Open("/title", 1); fd == -106)
        return true;

    if (fd >= 0)
        IOS_Close(fd);
    return false;
}


void* loadCustomModule(EGG::Heap* heap)
{
    const s32 entryNum = DVDConvertPathToEntrynum(dvdRelPath);
    if (entryNum != -1) {
        loadFromDVD(heap, entryNum);
    }
    return nullptr;
}

void* loadFromDVD(EGG::Heap* heap, s32 entryNum)
{
    DVDFileInfo file;
    const bool ret = DVDFastOpen(entryNum, file);
    assert(ret);

    void* data = heap->alloc((file.byteLength + 31) & ~31, 32);
    assert(data != nullptr);


    
}


















