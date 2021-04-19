######################################################################
# Makefile: Makefile for HeroChess -  EECS22L Spring 2021
#
# 04/18/21 Rachel Villamor	Initial Version
#
######################################################################


# design names
DESIGN = HeroChess

#libs


CC     = gcc
DEBUG  = -DDEBUG 
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall
AR     = ar rc
RANLIB = ranlib

# replay files
TXT	= movelog.txt 

all: HeroChess


########### generate object files ###########

#target to generate settings.o
settings.o: settings.h settings.c
	$(CC) $(CFLAGS) settings.c -o settings.o

#target to generate piece.o
piece.o: piece.h piece.c
	$(CC) $(CFLAGS) piece.c -o piece.o 

#target to generate move.o
move.o: move.h move.c
	$(CC) $(CFLAGS) move.c -o move.o 

#target to generate game.o
game.o: settings.h piece.h game.h game.c 
	$(CC) $(CFLAGS) game.c -o game.o

#target to generate board.o
board.o: settings.h piece.h board.h board.c 
	$(CC) $(CFLAGS) board.c -o board.o

#target to generate ai.o
ai.o: settings.h piece.h ai.h ai.c
	$(CC) $(CFLAGS) ai.c -o ai.o

#target to generate movelist.o
movelist.o: piece.h move.h movelist.h movelist.c
	$(CC) $(CFLAGS) movelist.c -o movelist.o

#target to generate main.o
main.o: main.c settings.h piece.h move.h game.h board.h ai.h movelist.h
	$(CC) $(CFLAGS) main.c -o main.o


########### generate library files ###########



########### generate executables ###########

#target to generate HeroChess
HeroChess: main.o 
	$(CC) $(LFLAGS) main.o settings.o piece.o move.o game.o board.o ai.o movelist.o -o HeroChess -lm

clean:
	rm -f *.o $(DESIGN) $(TXT)

