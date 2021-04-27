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
	PIECE *wRl = NewPiece('R', 'w');
	PIECE *wRr = NewPiece('R', 'w');
	PIECE *wNl = NewPiece('N', 'w');
	PIECE *wNr = NewPiece('N', 'w');
	PIECE *wBl = NewPiece('B', 'w');
	PIECE *wBr = NewPiece('B', 'w');
	PIECE *wQ = NewPiece('Q', 'w');
	PIECE *wK = NewPiece('K', 'w');

	placePiece(myBoard, wRl, 0, 0);
	placePiece(myBoard, wRr, 0, 7);
	placePiece(myBoard, wNl, 0, 1);
	placePiece(myBoard, wNr, 0, 6);
	placePiece(myBoard, wBl, 0, 2);
	placePiece(myBoard, wBr, 0, 5);
	placePiece(myBoard, wK, 0, 3);
	placePiece(myBoard, wQ, 0, 4);

	PIECE *bRl = NewPiece('R', 'b');
	PIECE *bRr = NewPiece('R', 'b');
	PIECE *bNl = NewPiece('N', 'b');
	PIECE *bNr = NewPiece('N', 'b');
	PIECE *bBl = NewPiece('B', 'b');
	PIECE *bBr = NewPiece('B', 'b');
	PIECE *bQ = NewPiece('Q', 'b');
	PIECE *bK = NewPiece('K', 'b');

	placePiece(myBoard, bRl, 7, 0);
	placePiece(myBoard, bRr, 7, 7);
	placePiece(myBoard, bNl, 7, 1);
	placePiece(myBoard, bNr, 7, 6);
	placePiece(myBoard, bBl, 7, 2);
	placePiece(myBoard, bBr, 7, 5);
	placePiece(myBoard, bK, 7, 3);
	placePiece(myBoard, bQ, 7, 4);

	for(i = 0; i < size; i++){
		PIECE *wP = NewPiece('P', 'w');
		placePiece(myBoard, wP, 1, i);
	}
	for(i = 0; i < size; i++){
        PIECE *bP = NewPiece('P', 'b');
        placePiece(myBoard, bP, 6, i);
    }

	for(i = 2; i < size-2; i++){
		for(j = 0; j < size; j++){	
			myBoard[i][j] = makeBlank();	
		}
	}
}

int isEmpty(PIECE **myBoard, int col, int row){
	return (GetColor(&myBoard[col][row]) == ' ' && GetType(&myBoard[col][row]) == ' ');
}
