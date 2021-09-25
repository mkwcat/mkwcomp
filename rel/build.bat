build.py
powerpc-eabi-ld build/patch2.plf -o build/patch2.elf -Tlink.ld -r
elf2rel -i build/patch2.elf -s mkw.eu.lst -o patch_P.rel
elf2rel -i build/patch2.elf -s mkw.us.lst -o patch_E.rel
copy patch_P.rel C:\Users\twiggo\Documents\Wii\Dolphin\Dolphin-x64\User\Wii\xoris\rel\patch_P.rel
copy patch_E.rel C:\Users\twiggo\Documents\Wii\Dolphin\Dolphin-x64\User\Wii\xoris\rel\patch_E.rel