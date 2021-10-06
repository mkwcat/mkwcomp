#include "CompFile.cpp"
#include "ForcedHandleBypassPage.cpp"
#include "SelectionPage.cpp"
#include "SettingsPage.cpp"
#include "UI.cpp"
#include "file.cpp"
#include "main.cpp"
#include "replay.cpp"
#include "util.cpp"

extern "C" {

typedef void (*PFN_voidfunc)();
__attribute__((section(".ctors"))) extern PFN_voidfunc _ctors[];
__attribute__((section(".ctors"))) extern PFN_voidfunc _ctors_end[];

void _prolog();
void _epilog();
void _unresolved();
void __start()
{
    _prolog();
}
}

__declspec(noinline) void _prolog()
{
    // Run global constructors
    for (PFN_voidfunc* ctor = _ctors; ctor != _ctors_end && *ctor; ++ctor) {
        (*ctor)();
    }

    // Run main
    main();
}

__declspec(noinline) void _epilog()
{
    // Infinite loop
    _epilog();
}

__declspec(noinline) void _unresolved()
{
    // Infinite loop
    _unresolved();
}