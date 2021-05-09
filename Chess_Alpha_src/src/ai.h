#ifndef AI_H
#define AI_H
#include "piece.h"
#include "movelist.h"
#include "tree.h"


int GetTurn(PIECE **myBoard, char computerColor, MLIST *myList);

//private functions
int GetValue(PIECE *myPiece, char curTurnColor);//returns a value based on what type the inputted piece is. Also outputs a positive number for friendly and negative number for enemy pieces

int SumBoard(PIECE **myBoard, char curTurnColor);//adds up all the pieces on the board to analyze the risk, benefits, etc. using GetValue. Used to determine the worth of a board

MOVE *HighestEval(PIECE **myBoard, char curTurnColor, MLIST *myList);//this traverses the whole board and every possible move, and the resulting board from the move. 
//Then it uses SumBoard to determine how much that board is worth, and returns what move leads to the highest worth board

void AllPossibilities(PIECE **myBoard, char curTurnColor, MLIST *myList, TREENODE *root);//gets every single possible move on the board and stores them as children to root, all connected to one another by pointer links

int MakeRandomOpeningMove(PIECE **myBoard, char curTurnColor, MLIST *myList);


//private functions

//a function used to do a move just like MakeMoveNoAppend where it doesnt append the done mvoe to myList, but it adds the move to an empty node blankNode instead. Used primarily in AllPossibilities
int MakeMoveAppendNode(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList, TREENODE *blankNode);



int MakeOpeningMove(PIECE **myBoard, char curTurnColor, MLIST *myList);

int SicilianDefense(PIECE **myBoard, char curTurnColor, MLIST *myList);

int QueensGambit(PIECE **myBoard, char curTurnColor, MLIST *myList);

int EnglishOpening(PIECE **myBoard, char curTurnColor, MLIST *myList);

int DutchDefense(PIECE **myBoard, char curTurnColor, MLIST *myList);

#endif