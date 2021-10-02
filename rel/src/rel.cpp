#include "competition.cpp"
#include "file.cpp"
#include "main.cpp"
#include "ui.cpp"
#include "util.cpp"
#include "replay.cpp"

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