#ifndef AI_H
#define AI_H
#include "piece.h"
#include "movelist.h"
#include "tree.h"


//A function to makemove on the AI's behalf based on what its turn is. Recursively searches to a depth of moves equal to Depth. 
int GetAITurn(PIECE **myBoard, char computerColor, MLIST *myList, int Depth);

//private functions
int GetValue(PIECE *myPiece, char curTurnColor);//returns a value based on what type the inputted piece is. Also outputs a positive number for friendly and negative number for enemy pieces

int SumBoard(PIECE **myBoard, char curTurnColor);//adds up all the pieces on the board to analyze the risk, benefits, etc. using GetValue. Used to determine the worth of a board

MOVE *HighestEval(PIECE **myBoard, char curTurnColor, MLIST *myList);//this traverses the whole board and every possible move, and the resulting board from the move. 
//Then it uses SumBoard to determine how much that board is worth, and returns what move leads to the highest worth board

void AllPossibilities(PIECE **myBoard, char curTurnColor, MLIST *myList, TREENODE *root);//gets every single possible move on the board and stores them as children to root, all connected to one another by pointer links

int MakeOpeningMove(PIECE **myBoard, char curTurnColor, MLIST *myList);//makes a random hardcoded opening move from a small library


//private functions

//a function used to do a move just like MakeMoveNoAppend where it doesnt append the done mvoe to myList, but it adds the move to an empty node blankNode instead. Used primarily in AllPossibilities
int MakeMoveAppendNode(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList, TREENODE *blankNode);

int SearchMovesRecursive(PIECE **myBoard, char computerColor, MLIST *myList,TREENODE *myNode, MOVE *bestMove, int Depth, int originalDepth);//a helper function to recursively look through the various levels of moves


//A set of opening moves
int SicilianDefense(PIECE **myBoard, char curTurnColor, MLIST *myList);

int QueensGambit(PIECE **myBoard, char curTurnColor, MLIST *myList);

int EnglishOpening(PIECE **myBoard, char curTurnColor, MLIST *myList);

int DutchDefense(PIECE **myBoard, char curTurnColor, MLIST *myList);

#endif