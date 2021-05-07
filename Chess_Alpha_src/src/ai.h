#ifndef AI_H
#define AI_H
#include "piece.h"
#include "movelist.h"
#include "tree.h"


int GetTurn(PIECE **myBoard, char computerColor, MLIST *myList);


//private functions
int GetValue(PIECE *myPiece, char curTurnColor);

int SumBoard(PIECE **myBoard, char curTurnColor);//adds up all the pieces on the board to analyze the risk, benefits, etc.

MOVE *HighestEval(PIECE **myBoard, char curTurnColor, MLIST *myList);//this gets the highest rated move

void AllPossibilities(PIECE **myBoard, char curTurnColor, MLIST *myList, TREENODE *root);//gets every single possible move on the board and stores them as children to root, all connected to one another by pointer links

//private functions

//a function used to do a move just like MakeMoveNoAppend where it doesnt append the done mvoe to myList, but it adds the move to an empty node blankNode instead
int MakeMoveAppendNode(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList, TREENODE *blankNode);

#endif