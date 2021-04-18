#ifndef BOARD_H
#define BOARD_H
#define size 8
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "piece.h"

PIECE **makeBoard();

void deleteBoard(PIECE *myBoard);

PIECE *getPiece(PIECE **myBoard, int col, int row);

void placePiece(PIECE **myBoard, PIECE *p, int col, int row);

void removePiece(PIECE **myBoard, int col, int row);

#endif
