#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piece.h"
#include "board.h"

int main(void){
	PIECE **board = makeBoard();
	PIECE *p = NewPiece('P', 'w');
	placePiece(board, p, 0, 0);
}
