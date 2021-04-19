#ifndef PIECE_H
#define PIECE_H
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

struct Piece{
	char type;
	char color;
};

typedef struct Piece PIECE;

PIECE *NewPiece(char type, char color);

char GetType(PIECE *mypiece);

char GetColor(PIECE *mypiece);

#endif

