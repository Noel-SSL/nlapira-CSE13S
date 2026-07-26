
.PHONY: all

all: unittests compress decompress 

unittests: unittests.o nibbler.o
	clang unittests.o nibbler.o -o unittests 

compress: compress.o nibbler.o
	clang compress.o nibbler.o -o compress

decompress: decompress.o nibbler.o
	clang decompress.o nibbler.o -o decompress


nibbler.o: nibbler.c nibbler.h
	clang -c -Wall -Werror -gdwarf-4 nibbler.c 

unittests.o: unittests.c
	clang -c -Wall -Werror -gdwarf-4 unittests.c

compress.o: compress.c
	clang -c -Wall -Werror -gdwarf-4 compress.c 

decompress.o: decompress.c 
	clang -c -Wall -Werror -gdwarf-4 decompress.c







