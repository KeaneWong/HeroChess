#ifndef BOARD_H
#define BOARD_H
#define size 8

#include <assert.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "piece.h"

PIECE **makeBoard();

void deleteBoard(PIECE **myBoard);

PIECE *getPiece(PIECE **myBoard, int col, int row);

void placePiece(PIECE **myBoard, PIECE *p, int col, int row);

PIECE removePiece(PIECE **myBoard, int col, int row);

PIECE *movePiece(PIECE** myBoard, int colSource, int rowSource, int colDestination,int rowDestination);

void printBoard(PIECE** myBoard);

void initializeBoard(PIECE** myBoard);

int isEmpty(PIECE **myBoard, int col, int row);

#endif
