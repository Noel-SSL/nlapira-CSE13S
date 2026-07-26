.PHONY: all 

CFLAGS = -Wall -Werror -gdwarf-4

all: unique unittests

unique: unique.o tree.o
	clang unique.o tree.o -o unique

unittests: unittests.o tree.o
	clang unittests.o tree.o -o unittests 

tree.o: tree.c tree.h
	clang -c $(CFLAGS) tree.c

unique.o: unique.c 
	clang -c $(CFLAGS) unique.c

unittests.o: unittests.c
	clang -c $(CFLAGS) unittests.c 