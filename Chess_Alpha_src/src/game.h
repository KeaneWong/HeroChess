#ifndef GAME_H
#define GAME_H
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "piece.h"
#include "movelist.h"


int isLegal(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList);

int isLegalPawn(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList);

int isLegalKnight(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalRook(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalBishop(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalQueen(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int isLegalKing(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor);

int MakeMove(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList);

int isChecked(PIECE **myBoard, char turnColor);

int isCheckmate(PIECE **myBoard, char turnColor, MLIST *myList);


//private functions
int isCheckedByRQ(PIECE **myBoard, char enemyColor, int colKing, int rowKing);//used to check for rooks or queens horizontal or vertical of the piece at colKing and rowKing
int isCheckedByBQ(PIECE **myBoard, char enemyColor, int colKing, int rowKing);//used to check for bishops or queens diagonal in all directions of the piece at colKing and rowKing
int isCheckedByN(PIECE **myBoard, char enemyColor, int colKing, int rowKing);//checks for nights
int isCheckedByP(PIECE **myBoard, char enemyColor, int colKing, int rowKing);
int isCheckedByK(PIECE **myBoard, char enemyColor, int colKing, int rowKing);

//makeMove but doesnt modify myList
int MakeMoveNoAppend(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList);

#endif

