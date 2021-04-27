#include "board.h"

PIECE **makeBoard(){
	int i = 0;
	PIECE **board;
	board = (PIECE **)malloc(sizeof(PIECE*) * size);
	for(i = 0; i<size; i++){
		board[i] = (PIECE *)malloc(sizeof(PIECE) * size);
	}
	return board;
}

void deleteBoard(PIECE **myBoard){
	assert(myBoard);		
	free(myBoard);
}

PIECE *getPiece(PIECE **myBoard, int col, int row){
	PIECE *p = &myBoard[col][row];
	return p;
}

void placePiece(PIECE **myBoard, PIECE *p, int col, int row){
	myBoard[col][row] = *p;	
}

PIECE removePiece(PIECE **myBoard, int col, int row){
	PIECE p = myBoard[col][row];	
	myBoard[col][row] = makeBlank();
	return p;
}

PIECE *movePiece(PIECE** myBoard, int colSource, int rowSource, int colDestination,int rowDestination){
	PIECE *p = NULL;
	p = &myBoard[colDestination][rowDestination];
	printf("%c%c\n", GetColor(&myBoard[colDestination][rowDestination]), GetType(&myBoard[colDestination][rowDestination]));
	myBoard[colDestination][rowDestination] = myBoard[colSource][rowSource];
	myBoard[colSource][rowSource] = makeBlank();	
	return p;
}

void printBoard(PIECE** myBoard){
	int i = 0, j = 0;
	printf("   ----------------------------------------\n");
	for(i = 0; i < size; i++){
		printf("%d", 8-i);
		for(j = 0; j < size; j++){	
			printf(" | %c%c", GetColor(&myBoard[i][j]), GetType(&myBoard[i][j]));
		}
		printf(" |\n");
		printf("   ----------------------------------------\n");

	}	
	printf("     a    b    c    d    e    f    g    h\n");
}

void initializeBoard(PIECE** myBoard){
	int i = 0, j = 0;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){	
			myBoard[i][j] = makeBlank();	
		}
	}
}

int isEmpty(PIECE **myBoard, int col, int row){
	return (GetColor(&myBoard[col][row]) == ' ' && GetType(&myBoard[col][row]) == ' ');
}
