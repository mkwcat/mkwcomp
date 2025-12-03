import os

MWCC = "mwcceppc.exe"
MWLD = "mwldeppc.exe"
CLANGPP = "tools\\clang++.exe"
LDLLD = "tools\\ld.lld.exe"
KCONV = "tools\\KuriboConverter.exe"

MWCC_ARGS = [
	"-DGEKKO -DRII_CLIENT",
	"-gccext on",
	"-proc gekko",
	"-enum int",
	"-Cpp_exceptions off",
	"-RTTI off",

	"-pragma \"opt_usedef_mem_limit 900\"",
	"-pragma \"cpp1x on\"",

	"-ipa file",
	"-O4,p",
	"-inline all",
	"-fp hard",
	"-use_lmw_stmw on",

    "-func_align 4",

	"-tune_relocations",
	
	"-sdata 0",
	"-sdata2 0",

	"-gccinc",
    "-I" + "../include"
]

def compile_mwcc(src, dst):
	mwcc_string = MWCC + " " + " ".join(MWCC_ARGS + ["-c", src, "-o", dst])
	#print(mwcc_string)
	os.system(mwcc_string)

CLANG_ARGS = [
	"--target=powerpc-unknown-eabi",
	"-Os",
	#"-flto",
	"-ffunction-sections",
	"-fdata-sections",
	" -ffast-math "

	"-Isource/imgui",
	"-IC:/devkitPro/devkitPPC/powerpc-eabi/include",
	"-IC:/devkitPro/devkitPPC/powerpc-eabi/include/c++/10.2.0",
	"-IC:/devkitPro/devkitPPC/powerpc-eabi/include/c++/10.2.0/powerpc-eabi",
	"-IC:\\devkitPro\\devkitPPC\\lib\\gcc\\powerpc-eabi\\10.2.0\\include",
	"-IC:\\devkitPro\\devkitPPC\\lib\\gcc\\powerpc-eabi\\10.2.0\\include-fixed",
	"-fno-exceptions",
	"-fno-rtti"
]

# Outputs bitcode, make sure to use compile_bc
def gen_ir_clang(src, dst):
	clang_string = CLANGPP + " " + " ".join(CLANG_ARGS + ["-c", src, "-o", dst])
	#print(clang_string)
	os.system(clang_string)

def compile_ir(sources, dst):
	ldlld_string = LDLLD + " " + " ".join(sources) + " -o " + dst + " -relocatable"
	#print(ldlld_string)
	os.system(ldlld_string)

def compile_clang(sources, dst):
	bc_files = []

	for source in sources:
		bc_file = "out/" + source.replace("\\", "_").replace("/", "_") + ".bc"
		gen_ir_clang(source, bc_file)
		bc_files.append(bc_file)

	compile_ir(bc_files, dst)

def link_mwld(sources, dst):
	mwld_string = MWLD + " -fp hard -partial -strip_partial -r1 " + sources + " -o " + dst
	#print(mwld_string) 
	os.system(mwld_string)

def build_kxe(source, dest, symbols):
	kconv_string = KCONV + " " + " ".join([source, dest, symbols])
	#print(kconv_string)
	os.system(kconv_string)

def copy_to(cfrom, cto):
	xcopy_string = "xcopy /s %s %s /F /Y" % (cfrom, cto)
	#print(xcopy_string)
	os.system(xcopy_string)

def make_o(cfrom, cto):
	cmd = "tools\\makeo.exe -s .rodata -a 32 -o %s %s" % (cto, cfrom)
	os.system(cmd)

compile_mwcc("src/rel.cpp", "build/patch.plf")
link_mwld("build/patch.plf", "build/patch2.plf")

