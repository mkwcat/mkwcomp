#include "elf.h"
#include <cstdio>
#include <cstring>
#include <vector>



namespace Args
{
    char* infname = nullptr;
    char* outfname = nullptr;
    char* symsfname = nullptr;
}


void printOption(const char* opt, u32 optLen)
{
    char str[64];
    std::strncpy(str, opt, optLen < 60 ? optLen + 1 : 60);

    if (optLen > 60)
        std::fprintf(stderr, "%.60s...", str);
    else
        std::fprintf(stderr, "%.60s", str);
}

bool optCmd(const char* opt, u32 optLen, const char* match,
    char** set, char* val)
{
    if (strncmp(opt, match, optLen))
        return false;
    
    if (*set != nullptr) {
        std::fprintf(stderr, "warning: option '");
        printOption(opt, optLen);
        std::fprintf(stderr, "' redefined\n");
    }
    *set = val;
    return true;
}

s32 readOpt(char** argv, s32 argc)
{
    s32 len = std::strlen(argv[0]);
    if (len == 0)
        return argc - 1;
    
    if (argv[0][0] != '-') {
        std::fprintf(stderr, "error: expected option, got '%s'\n", argv[0]);
        return -1;
    }

    char* cmd = &argv[0][1];
    char* end = std::strchr(cmd, '=');
    char* val = end + 1;
    if (!end) {
        end = cmd + len - 1;
        if (argc < 2) {
            std::fprintf(stderr,
                "error: expected value to '%s' command\n", cmd);
            return -1;
        }
        val = argv[1];
        argc--;
    }

    s32 optlen = end - cmd;
    bool found = optCmd(cmd, optlen, "in", &Args::infname, val) ? true
               : optCmd(cmd, optlen, "out", &Args::outfname, val) ? true
               : optCmd(cmd, optlen, "syms", &Args::symsfname, val) ? true
               : false;
    if (!found) {
        std::fprintf(stderr, "error: unknown option '");
        printOption(cmd, optlen);
        std::fprintf(stderr, "'\n");
        return -1;
    }
    return argc - 1;
}

s32 main(s32 argc, char** argv)
{
    if (argc < 2)
    {
        std::printf(
            "usage: makerel -in <input elf name> -out <output rel name>"
            "-syms <symbol file name>\n");
        return 1;
    }

    for (s32 argn = argc - 1; argn > 0;)
    {
        char** arg = argv + (argc - argn);
        argn = readOpt(arg, argn);
        if (argn == -1)
            return -1;
    }

    if (!Args::infname || !Args::outfname || !Args::symsfname) {
        std::fprintf(stderr,
            "error: one or more required arguments are missing\n");
        return -1;
    }
}