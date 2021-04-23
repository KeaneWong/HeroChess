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
	
}

PIECE *getPiece(PIECE **myBoard, int col, int row){
	PIECE *p =  &myBoard[row][col];
	return p;
}

void placePiece(PIECE **myBoard, PIECE *p, int col, int row){
	myBoard[row][col] = *p;	
}

void removePiece(PIECE **myBoard, int col, int row){

}

int movePiece(PIECE **myBoard, int col, int row, int colDest, int rowDest)
{
	
}
