#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <assert.h>

/* move struct */
struct Move{
	PIECE *piece;
	PIECE *removedPiece;
	char *source;	
	char *destination;
};

/* alias */
typedef struct Move MOVE;

/* Create struct that contains each moves */
MOVE *NewMove(PIECE *piece, PIECE *removedPiece, char *source, char* destination);

/* Delete Move */
void DeleteMove(MOVE *m);

/* return move as char pointer*/
char *GetMove(MOVE *m);

/* return player number */
PIECE *GetPiece(MOVE *m);

void PrintMove(MOVE *m);
#endif
