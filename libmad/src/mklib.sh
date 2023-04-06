set -x

DEFS='-DNDEBUG -DFPM_INTEL -DWIN32 -D_LIB -DHAVE_CONFIG_H -DASO_ZEROCHECK'
CFLAGS='-Wall -c -g'

gcc $CFLAGS $DEFS bit.c -o bit.o
gcc $CFLAGS $DEFS decoder.c -o decoder.o
gcc $CFLAGS $DEFS fixed.c -o fixed.o
gcc $CFLAGS $DEFS frame.c -o frame.o
gcc $CFLAGS $DEFS huffman.c -o huffman.o
gcc $CFLAGS $DEFS layer12.c -o layer12.o
gcc $CFLAGS $DEFS layer3.c -o layer3.o
gcc $CFLAGS $DEFS stream.c -o stream.o
gcc $CFLAGS $DEFS synth.c -o synth.o
gcc $CFLAGS $DEFS timer.c -o timer.o
gcc $CFLAGS $DEFS version.c -o version.o

ar ruv libmad-linux.a bit.o decoder.o fixed.o frame.o huffman.o layer12.o layer3.o stream.o synth.o timer.o version.o

ranlib libmad-linux.a

cp libmad-linux.a ../
