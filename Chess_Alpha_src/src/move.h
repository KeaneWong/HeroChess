#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <assert.h>

/* move struct */
struct Move{
	PIECE piece;
	PIECE removedPiece;
	char *source;	
	char *destination;
};

/* alias */
typedef struct Move MOVE;

/* Create struct that contains each moves */
MOVE *NewMove(PIECE *piece, PIECE *removedPiece, char *source, char *destination);

/* Delete Move */
void DeleteMove(MOVE *m);

PIECE GetRemovedPiece(MOVE *m);
/* return move as char pointer*/
char *GetSource(MOVE *m);

char *GetDestination(MOVE *m);

/* return player number */
PIECE GetPiece(MOVE *m);

void PrintMove(MOVE *m);

int getColS(MOVE* m);

int getRowS(MOVE* m);

int getColD(MOVE* m);

int getRowD(MOVE* m);


#endif
