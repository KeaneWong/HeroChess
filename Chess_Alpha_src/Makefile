# Makefile: Makefile for HeroChess -  EECS22L Spring 2021
#########################################################

# design names
DESIGN = bin/HeroChess

#libs

# gcc and tags
CC     = gcc
DEBUG  = -DDEBUG 
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall

# executables and replay files
TXT	= bin/movelog.txt
SRC	= src/*.o

all: HeroChess


########### generate object files ###########

#target to generate settings.o
settings.o: src/settings.h src/settings.c
	$(CC) $(CFLAGS) src/settings.c -o src/settings.o

#target to generate tree.o
tree.o: src/tree.h src/tree.c
	$(CC) $(CFLAGS) src/tree.c -o src/tree.o

#target to generate piece.o
piece.o: src/piece.h src/piece.c
	$(CC) $(CFLAGS) src/piece.c -o src/piece.o 

#target to generate move.o
move.o: src/move.h src/move.c
	$(CC) $(CFLAGS) src/move.c -o src/move.o 

#target to generate game.o
game.o: src/settings.h src/piece.h src/movelist.h src/game.h src/game.c  
	$(CC) $(CFLAGS) src/game.c -o src/game.o

#target to generate board.o
board.o: src/settings.h src/piece.h src/board.h src/board.c 
	$(CC) $(CFLAGS) src/board.c -o src/board.o

#target to generate ai.o
ai.o: src/settings.h src/piece.h src/ai.h src/ai.c src/tree.h
	$(CC) $(CFLAGS) src/ai.c -o src/ai.o

#target to generate movelist.o
movelist.o: src/piece.h src/move.h src/movelist.h src/movelist.c
	$(CC) $(CFLAGS) src/movelist.c -o src/movelist.o

#target to generate main.o
main.o: src/main.c src/settings.h src/piece.h src/move.h src/game.h src/board.h src/ai.h src/movelist.h
	$(CC) $(CFLAGS) src/main.c -o src/main.o


########### generate library files ###########



########### generate executables ###########

# target to generate HeroChess
HeroChess: src/main.o src/settings.o src/piece.o src/move.o src/game.o src/board.o src/ai.o src/movelist.o
	$(CC) $(LFLAGS) src/main.o src/settings.o src/piece.o src/move.o src/game.o src/board.o src/ai.o src/movelist.o -o bin/HeroChess -lm

# delete all executables currently in the source and binary directories
clean:
	rm -f $(SRC) $(DESIGN) $(TXT)

# test game
test: 

# tar the source code package
tar:
	tar zcvf Chess_Beta_src.tar.gz Chess_Beta_src   
