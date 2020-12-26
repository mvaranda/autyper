SET DEFS=-DNDEBUG -DFPM_INTEL -DWIN32 -D_LIB -DHAVE_CONFIG_H -DASO_ZEROCHECK
SET CFLAGS=-Wall -g

gcc %CFLAGS% %DEFS% -c bit.c -o bit.o
gcc %CFLAGS% %DEFS% -c decoder.c -o decoder.o
gcc %CFLAGS% %DEFS% -c fixed.c -o fixed.o
gcc %CFLAGS% %DEFS% -c frame.c -o frame.o
gcc %CFLAGS% %DEFS% -c huffman.c -o huffman.o
gcc %CFLAGS% %DEFS% -c layer12.c -o layer12.o
gcc %CFLAGS% %DEFS% -c layer3.c -o layer3.o
gcc %CFLAGS% %DEFS% -c stream.c -o stream.o
gcc %CFLAGS% %DEFS% -c synth.c -o synth.o
gcc %CFLAGS% %DEFS% -c timer.c -o timer.o
gcc %CFLAGS% %DEFS% -c version.c -o version.o

ar ruv libmad.a bit.o decoder.o fixed.o frame.o huffman.o layer12.o layer3.o stream.o synth.o timer.o version.o

ranlib libmad.a

copy libmad.a ..\
