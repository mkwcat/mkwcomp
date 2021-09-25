mwcceppc -O4,p -gccext on -proc gekko -enum int -Cpp_exceptions off -RTTI off -fp hard -use_lmw_stmw on -sdata 0 -sdata2 0 -ipa file -func_align 4 -c -gccinc -I../include main.cpp -o main.plf
mwldeppc -codeaddr 0x80004100 -proc gekko -fp hard main.plf -o main.elf
powerpc-eabi-objcopy main.elf loader.bin -O binary