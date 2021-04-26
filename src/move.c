#include "move.h"

/*create new move struct */
MOVE *NewMove(PIECE *piece, PIECE *removedPiece, char *source, char *destination){
	MOVE *m;
	m = (MOVE *)malloc(sizeof(MOVE));
	if (!m)
	{ 
		perror("Out of memory! Aborting...");
		exit(10);
	} /* fi */
	m->piece = piece;
	m->removedPiece = removedPiece;
	m->source = source;
	m->destination = destination;
	return m;
} 
/* delete move */
void DeleteMove(MOVE *m){
	assert(m);	
	free(m);
}
/*return player number*/
PIECE *GetPiece(MOVE *m){
	return m->piece;
}
/* return Move */
char *GetMove(MOVE *m){
	return m->source;
}

void PrintMove(MOVE *m){
	assert(m);
	printf("%c%c %2s %2s\n", m->piece->color, m->piece->type, m->source, m->destination);
	if(m->removedPiece != NULL){
		printf("%c%c\n",m->removedPiece->color, m->removedPiece->type);
	}
}

