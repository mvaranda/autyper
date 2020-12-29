rm -f m.exe
gcc -Wall -g -D_MACOS -I/usr/include/malloc/ minimad.c libmad.a -o m