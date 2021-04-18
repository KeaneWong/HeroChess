#include "piece.h"

PIECE *NewPiece(char type, char color){
	PIECE *p;
	p = (PIECE*)malloc(sizeof(PIECE));
	if (!p)
	{ 
		perror("Out of memory! Aborting...");
		exit(10);
	} /* fi */

	p->type = type;
	p->color = color;
	return p;
}
/*return player number*/
char GetType(PIECE *mypiece){
	return mypiece->type;
}

char GetColor(PIECE *mypiece){
	return mypiece->color;
}
