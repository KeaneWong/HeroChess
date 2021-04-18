#ifndef GAME_H
#define GAME_H
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

int isLegal(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalPawn(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalKnight(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalRook(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalBishop(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalQueen(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalKing(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int makeMove(Piece** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isCheckmate(Piece **myBoard, char curTurnColor);

#endif

