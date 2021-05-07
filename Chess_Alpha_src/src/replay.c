#include "replay.h"

void replay(MLIST *l){
	char name[100];
	FILE *fptr;
	printFormat(fptr, name);
	
	PIECE **copyBoard = makeBoard();
	initializeBoard(copyBoard);

	fprintf(fptr, "\n////////////////////////////////\n");
	MOVE *m = NULL;
	int x= 0;
	while(GetLength(l) > 0){
		int turn = 0;
		turn = turn%2;
		m = RemoveFirstMove(l);
		fprintf(fptr, "Player %d moved from %2s to %2s.\n", turn, GetSource(m), GetDestination(m));
		removePiece(copyBoard, getColD(m), getRowD(m));
		movePiece(copyBoard, getColS(m), getRowS(m), getColD(m), getRowD(m));
		printReplayBoard(copyBoard);
		turn++;
	}
	printf("\n/////////////////////////////////\n")	
}

void printFormat(FILE *fptr, char *fname){
    int hours, minutes, seconds, day, month, year;
    time_t now;
    time(&now);
 
    struct tm *local = localtime(&now);
 
    hours = local->tm_hour;        
    minutes = local->tm_min;        
    seconds = local->tm_sec;        
 
    day = local->tm_mday;            
    month = local->tm_mon + 1;      
    year = local->tm_year + 1900;   
	hours = ((hours < 12) ? hours : hours-12);
	
    sprintf(fname, "replay %d-%d-%d %d:%d:%d.txt", year, month, day, hours, minutes, seconds);	

	fptr = fopen(fname, "w");

	fprintf(fptr, "#TicTacToeWowWeeWow\n");
	fprintf(fptr, "Version: v1.0\n");
	fprintf(fptr, "Filename: %s\n", fname);
	fprintf(fptr, "Date: %d/%d/%d %d:%d:%d\n", year, month, day, hours, minutes, seconds);

	fprintf(fptr, "\nPlayer 1");
	fprintf(fptr, "\nPlayer 2\n");
}

