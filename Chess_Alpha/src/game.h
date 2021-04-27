#ifndef GAME_H
#define GAME_H
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "piece.h"


int isLegal(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalPawn(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalKnight(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalRook(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalBishop(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalQueen(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalKing(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int makeMove(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isChecked(PIECE **myBoard, char turnColor);

int isCheckmate(PIECE **myBoard, char turnColor);


//private function
int Castle(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);



#endif

