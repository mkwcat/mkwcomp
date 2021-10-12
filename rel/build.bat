build.py
powerpc-eabi-ld build/patch2.plf -o build/patch2.elf -Tlink.ld -r
python ../tools/lstgen.py symbols.tsv mkw.
elf2rel -i build/patch2.elf -s mkw.pal.lst -o patch_P.rel
elf2rel -i build/patch2.elf -s mkw.usa.lst -o patch_E.rel
elf2rel -i build/patch2.elf -s mkw.jap.lst -o patch_J.rel
elf2rel -i build/patch2.elf -s mkw.kor.lst -o patch_K.rel
copy patch_P.rel C:\Users\twiggo\Documents\Wii\Dolphin\Dolphin-x64\User\Wii\xoris\rel\patch_P.rel
copy patch_E.rel C:\Users\twiggo\Documents\Wii\Dolphin\Dolphin-x64\User\Wii\xoris\rel\patch_E.rel
copy patch_J.rel C:\Users\twiggo\Documents\Wii\Dolphin\Dolphin-x64\User\Wii\xoris\rel\patch_J.rel
copy patch_K.rel C:\Users\twiggo\Documents\Wii\Dolphin\Dolphin-x64\User\Wii\xoris\rel\patch_K.rel