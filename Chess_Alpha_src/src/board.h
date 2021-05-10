/************************************************************************/
/* 		HeroChess V1.0 by The Avengineers			*/
/* 		EECS 22L - University of California, Irvine		*/
/*									*/
/* board.h: contains declarations of structs and functions in board.c	*/
/*									*/
/* Modifications:							*/
/* Date (YYYY/MM/DD)	Author			Description		*/
/* 2021/04/17		Paul Lee		Initial Version		*/
/************************************************************************/

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

PIECE **copyBoard(PIECE **myBoard);

PIECE *getPiece(PIECE **myBoard, int col, int row);

void placePiece(PIECE **myBoard, PIECE *p, int col, int row);

PIECE removePiece(PIECE **myBoard, int col, int row);

PIECE *movePiece(PIECE** myBoard, int colSource, int rowSource, int colDestination,int rowDestination);

void printBoard(PIECE** myBoard);

void printReplayBoard(PIECE** myBoard, FILE* fptr);

void initializeBoard(PIECE** myBoard);

int isEmpty(PIECE **myBoard, int col, int row);

void checkForPromotion(PIECE **myBoard);

#endif
