rmdir /s /q outcompress
rmdir /s /q outuncompress
mkdir outcompress outuncompress

cd out

for %%f in (*.szs) do (
wszst decompress %%f --dest ../outuncompress/%%f
yaz0enc -e ../outuncompress/%%f -o ../outcompress/%%f
)

cd ..