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

void deleteBoard(PIECE *myBoard){
	
}

PIECE *getPiece(PIECE **myBoard, int col, int row){
	PIECE *p = &myBoard[row][col];
	return p;
}

void placePiece(PIECE **myBoard, PIECE *p, int col, int row){
	myBoard[row][col] = *p;	
}

PIECE removePiece(PIECE **myBoard, int col, int row){
	PIECE p = myBoard[row][col];
	PIECE *e = NewPiece(' ', ' ');
	myBoard[row][col] = *e;
	return p;
}

PIECE *movePiece(PIECE** myBoard, int colSource, int rowSource, int colDestination,int rowDestination){
	PIECE *p = NULL;
	PIECE *e = NewPiece(' ', ' ');
	myBoard[rowDestination][colDestination] = myBoard[rowSource][colSource];
	myBoard[rowSource][colSource] = *e;
	p = &myBoard[rowDestination][colDestination];
	return p;
}

void printBoard(PIECE** myBoard){
	int i = 0, j = 0;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("row: %d col: %d %c%c\n", i, j, GetColor(&myBoard[i][j]), GetType(&myBoard[i][j]));
		}
	}
}

void initializeBoard(PIECE** myBoard){
	int i = 0, j = 0;
	PIECE *blank = NewPiece(' ', ' ');
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			myBoard[i][j] = *blank;
		}
	}
}

int isEmpty(PIECE **myBoard, int col, int row){
	return (GetColor(&myBoard[row][col]) == ' ' && GetType(&myBoard[row][col]) == ' ');
}
