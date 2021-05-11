#########################################################################
# 		HeroChess V1.0 by The Avengineers			#
# 		EECS 22L - University of California, Irvine		#
#									#
# Makefile: contains all commands needed for compilation		#
# 	and creating necessary executables for the game, HeroChess	#
#									#
# Modifications:							#
# Date (YYYY/MM/DD)	Author			Description		#
# 2021/04/19		Rachel Villamor		Initial Version		#
#########################################################################

#libs

# gcc and tags
CC     = gcc
DEBUG  = -DDEBUG 
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall

# executables and replay files
DESIGN	= bin/HeroChess
TEST	= bin/TestHeroChess
TXT	= bin/*.txt
SRC	= src/*.o

all: HeroChess TestHeroChess


########### generate object files ###########

#target to generate settings.o
settings.o: src/settings.h src/settings.c
	$(CC) $(CFLAGS) src/settings.c -o src/settings.o

#target to generate tree.o
tree.o: src/move.h src/tree.h src/tree.c
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
ai.o:	src/tree.h src/movelist.h src/game.h src/settings.h src/piece.h src/ai.h src/ai.c
	$(CC) $(CFLAGS) src/tree.c src/ai.c -o src/ai.o

#target to generate movelist.o
movelist.o: src/piece.h src/move.h src/movelist.h src/movelist.c
	$(CC) $(CFLAGS) src/movelist.c -o src/movelist.o

#target to generate replay.o
replay.o: src/board.h src/piece.h src/move.h src/game.h src/board.h src/movelist.h
	$(CC) $(CFLAGS) src/replay.c -o src/replay.o

#target to generate main.o
main.o: src/main.c src/settings.h src/piece.h src/move.h src/game.h src/board.h src/ai.h src/movelist.h src/replay.h
	$(CC) $(CFLAGS) src/main.c -o src/main.o

#target to generate testmain.o
#testmain.o: src/main.c src/settings.h src/piece.h src/move.h src/game.h src/board.h src/ai.h src/movelist.h src/replay.h
#	$(CC) $(CFLAGS) $(DEBUG) -c src/main.c -o src/testmain.o


############# generate executables #############
# target to generate HeroChess
HeroChess: src/main.o src/tree.o src/settings.o src/piece.o src/move.o src/game.o src/board.o src/ai.o src/movelist.o src/replay.o
	$(CC) $(LFLAGS) src/main.o src/tree.o src/settings.o src/piece.o src/move.o src/game.o src/board.o src/ai.o src/movelist.o src/replay.o -o bin/HeroChess -lm

src/testmain.o: src/main.c src/settings.h src/piece.h src/move.h src/game.h src/board.h src/ai.h src/movelist.h src/replay.h
	gcc -c -DDEBUG -Wall -std=c99 src/main.c -o src/testmain.o

# target to generate HeroChess with test mode on
TestHeroChess: src/testmain.o src/tree.o src/settings.o src/piece.o src/move.o src/game.o src/board.o src/ai.o src/movelist.o src/replay.o
	$(CC) $(LFLAGS) src/testmain.o src/tree.o src/settings.o src/piece.o src/move.o src/game.o src/board.o src/ai.o src/movelist.o src/replay.o -o bin/TestHeroChess -lm

# delete all executables currently in the source and binary directories
clean:
	rm -f $(DESIGN) $(TEST) $(TXT) $(SRC)

# test game
test: 
	./TestHeroChess	

# tar the source code package
tar:
	tar zcvf Chess_V1.0_src.tar.gz Chess_V1.0_src   
