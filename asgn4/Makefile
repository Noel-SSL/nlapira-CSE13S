# <target>: <dependencies>
##			<command>


lcr: lcr.o randi.o game.o 
	clang lcr.o randi.o game.o -o lcr

lcr.o: lcr.c
	clang -c -Wall -Werror lcr.c

randi.o: randi.c randi.h
	clang -c -Wall -Werror randi.c

game.o: game.c game.h
	clang -c -Wall -Werror game.c




