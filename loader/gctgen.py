import sys, struct

f = open(sys.argv[1])
addr = int(sys.argv[2], 16)

f.seek(0, 2)
size = f.tell()
f.seek(0, 0)

sys.stdout.write("{0:08X} {1:08X}\n".format(0xC2000000 | (addr & 0x1FFFFFF), (size + 0x40 + 1) >> 3))
sys.stdout.write("3D608000 616940FC\n48000005 7D4802A6\n394A0030 ")
sys.stdout.write("{0:08X}\n".format(0x38000000 | ((size + 3) >> 2)))
sys.stdout.write("7C0903A6 840A0004\n94090004 7C0048AC\n7C004FAC 4200FFF0\n616B4100 7D6903A6\n7D4803A6 4E800420\n")


while 1:
    for i in range(8):
        if size > 0:
            b = struct.unpack('B', f.read(1))[0]
            size -= 1
        else:
            if i == 4:
                sys.stdout.write(" 00000000\n")
                exit(0)
            if i == 0:
                b = 0x60
            else:
                b = 0
        if i == 4:
            sys.stdout.write(' ')
        sys.stdout.write("{0:02X}".format(b))
    sys.stdout.write('\n')