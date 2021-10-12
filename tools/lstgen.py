import sys, struct, csv

tsvpath = "symbols.tsv"
if len(sys.argv) > 1:
    tsvpath = sys.argv[1]

outpath = ""
if len(sys.argv) > 2:
    outpath = sys.argv[2]

f = open(tsvpath)

pal_lst = ""
usa_lst = ""
jap_lst = ""
kor_lst = ""

syms = csv.reader(f, delimiter="\t")
next(syms)
for sym in syms:
    pal_lst += sym[0] + ":" + sym[4] + "\n"
    usa_lst += sym[1] + ":" + sym[4] + "\n"
    jap_lst += sym[2] + ":" + sym[4] + "\n"
    kor_lst += sym[3] + ":" + sym[4] + "\n"
   
f.close()

f = open(outpath + "pal.lst", "w")
f.write(pal_lst)
f.close()

f = open(outpath + "usa.lst", "w")
f.write(usa_lst)
f.close()

f = open(outpath + "jap.lst", "w")
f.write(jap_lst)
f.close()

f = open(outpath + "kor.lst", "w")
f.write(kor_lst)
f.close()

