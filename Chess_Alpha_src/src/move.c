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
	m->piece = *piece;	
	m->removedPiece = *removedPiece;
	m->source = malloc(sizeof(char)*2);
	m->destination = malloc(sizeof(char)*2);
	strcpy(m->source, source);
	strcpy(m->destination, destination);
	return m;
} 
/* delete move */
void DeleteMove(MOVE *m){
	assert(m);	
	free(m);
}
/*return player number*/
PIECE GetPiece(MOVE *m){
	return m->piece;
}

PIECE GetRemovedPiece(MOVE *m){
	return m->removedPiece;
}
/* return Move */
char *GetSource(MOVE *m){
	return m->source;
}

char *GetDestination(MOVE *m){
	return m->destination;
}

void PrintMove(MOVE *m){
	assert(m);

	printf(" %c%c %2s %2s\n", GetColor(&m->piece), GetType(&m->piece), m->source, m->destination);
	if(m->removedPiece.type != ' '){
		printf("Piece taken: %c%c\n",GetColor(&m->removedPiece), GetType(&m->removedPiece));
	}
	else
	{
		printf("\n");
	}
}

int getColS(MOVE *m){
	return ((m->source)[0]-'A');
}
int getColD(MOVE *m){
	return ((m->destination)[0]-'A');
}
int getRowS(MOVE *m){
	return ((m->source)[1]-'1');
}
int getRowD(MOVE *m){
	return ((m->destination)[1]-'1');
}
