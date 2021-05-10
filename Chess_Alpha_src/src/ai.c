/************************************************************************/
/* 		HeroChess V1.0 by The Avengineers			*/
/* 		EECS 22L - University of California, Irvine		*/
/*									*/
/* ai.c: contains defintions of functions for automated player gameplay	*/
/*									*/
/* Modifications:							*/
/* Date (YYYY/MM/DD)	Author			Description		*/
/* 2021/04/23		Keane Wong		Initial Version		*/
/************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "ai.h"
#include "game.h"
#include "board.h"
#include "move.h"

// returns value based on type of inputted piece; positive values for friendly pieces and negative values for enemy pieces
int GetValue(PIECE *myPiece, char curTurnColor)
{
	char type = GetType(myPiece);
	int value;
	switch(type)
	{
		case 'P':
		{
			value = 10;
			break;
		}
		case 'R':
		{
			value = 50;
			break;
		}
		case 'N':
		{
			value = 30;
			break;
		}
		case 'B':
		{
			value = 30;
			break;
		}
		case 'Q':
		{
			value = 90;
			break;
		}
		case 'K':
		{
			value = 900;
			break;
		}
		default:		//for an empty square value = 0, as it adds no value to the boardl
		{
			value = 0;
		}
	}
	if(curTurnColor == GetColor(myPiece))//positive values correspond to a friendly piece
	{
		return value;
	}
	else
	{
		return (0-value);
	}
}

int GetTurn(PIECE **myBoard, char computerColor, MLIST *myList)
{







return 0;

}

// determines worth of a board by adding all the pieces values; analyzes risk and benefits
int SumBoard(PIECE **myBoard, char curTurnColor)
{
	int sumValue = 0;
	for(int i =0; i < 8; i++)
	{
		for(int j =0; j < 8; j++)
		{	
			sumValue+=GetValue(getPiece(myBoard,i,j),curTurnColor);

		}
	}
	return sumValue;

}

// evaluates board and determines what move would leave it in the best position 
MOVE *HighestEval(PIECE **myBoard, char curTurnColor, MLIST *myList)
{
	PIECE **tempBoard = copyBoard(myBoard);
	int bestMoveValue = -1000000;//some arbitrary impossibly low number to represent negative infinity
	int colS;		//coordinates of the best move
	int rowS;
	int colD;
	int rowD;
	for(int i = 0 ; i < 8; i++)//nested loop that goes through entire board, looking for friendly pieces that could potentially end check
	{
		for(int j = 0; j < 8; j++)
		{
			int tValue;
			if(GetColor(getPiece(tempBoard,i,j)) != curTurnColor)//if its an enemy piece we cant manipulate it to do things so we skip it
			{
				continue;
			}
			switch(GetType(getPiece(tempBoard,i,j)))
			{
				case 'K':
				{
					if(MakeMoveNoAppend(tempBoard,i,j,i-4,j,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i-4;
							rowD = j;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i+3,j,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i+3;
							rowD = j;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					for(int p = -1; p <=1; p++)//checking if we can move to any of the adjacent squares as the king and if we can, if we're still in check after moving. If we are then continue, but if we're out of check then return 1
					{
						for(int o = -1; o <=1; o++)
						{
							if(o !=0 || p != 0)
							{
								if(MakeMoveNoAppend(tempBoard,i,j,i+p,j+o,curTurnColor,myList))
								{
									tValue = SumBoard(tempBoard,curTurnColor);
									if(tValue>bestMoveValue)
									{
										bestMoveValue = tValue;
										colS = i;
										rowS = j;
										colD = i+p;
										rowD = j+o;
									}
									deleteBoard(tempBoard);
									tempBoard = copyBoard(myBoard);
								}
							}
						}
					}
					break;
				}
				case 'R':
				{
					for(int p = 0; p < 8; p++)
					{
						if(p != i)///checking all adjacent columns on the current row j
						{
							if(MakeMoveNoAppend(tempBoard,i, j, p, j,curTurnColor,myList))
							{
								tValue = SumBoard(tempBoard,curTurnColor);
								if(tValue>bestMoveValue)
								{
									bestMoveValue = tValue;
									colS = i;
									rowS = j;
									colD = p;
									rowD = j;
								}
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
						if(p != j)
						{
							if(MakeMoveNoAppend(tempBoard,i,j,i,p,curTurnColor,myList))
							{
								tValue = SumBoard(tempBoard,curTurnColor);
								if(tValue>bestMoveValue)
								{
									bestMoveValue = tValue;
									colS = i;
									rowS = j;
									colD = i;
									rowD = p;
								}
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
					}
					break;
				}
				case 'P':
				{
					int forward = curTurnColor == 'w' ? 1 : -1;

					if(MakeMoveNoAppend(tempBoard,i,j,i+1,j+forward,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i+1;
							rowD = j+forward;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i-1,j+forward,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i-1;
							rowD = j+forward;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i,j + 2*forward,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i;
							rowD = j+2*forward;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}

					break;
				}
				case 'B':
				{
					int startingCol = i<j ? 0 : i-j;
					int startingRow = i<j ? j-i : 0;
					int r = startingCol;
					int p;
					for(p = startingRow; p < 8 && r < 8; p++)
					{
						if(MakeMoveNoAppend(tempBoard,i,j,r,p,curTurnColor,myList))
						{
							tValue = SumBoard(tempBoard,curTurnColor);
							if(tValue>bestMoveValue)
							{
								bestMoveValue = tValue;
								colS = i;
								rowS = j;
								colD = r;
								rowD = p;
							}
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p >= 0 && r<8; p-- )
					{
						if(MakeMoveNoAppend(tempBoard,i,j,r,p,curTurnColor,myList))
						{
							tValue = SumBoard(tempBoard,curTurnColor);
							if(tValue>bestMoveValue)
							{
								bestMoveValue = tValue;
								colS = i;
								rowS = j;
								colD = r;
								rowD = p;
							}
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p < 8 && r>=0; p++ )
					{
						if(MakeMoveNoAppend(tempBoard,i,j,r,p,curTurnColor,myList))
						{
							tValue = SumBoard(tempBoard,curTurnColor);
							if(tValue>bestMoveValue)
							{
								bestMoveValue = tValue;
								colS = i;
								rowS = j;
								colD = r;
								rowD = p;
							}
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r--;
					}
					break;
				}
				case 'N':
				{
					if(MakeMoveNoAppend(tempBoard,i,j,i+2,j+1,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i+2;
							rowD = j+1;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i+1,j+2,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i+1;
							rowD = j+2;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i-2,j+1,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i+2;
							rowD = j+1;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i+1,j-2,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i+1;
							rowD = j-2;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i+2,j-1,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i+2;
							rowD = j-1;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i-1,j+2,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i-1;
							rowD = j+2;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i-2,j-1,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i-2;
							rowD = j-1;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveNoAppend(tempBoard,i,j,i-1,j-2,curTurnColor,myList))
					{
						tValue = SumBoard(tempBoard,curTurnColor);
						if(tValue>bestMoveValue)
						{
							bestMoveValue = tValue;
							colS = i;
							rowS = j;
							colD = i-1;
							rowD = j-2;
						}
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					break;
				}
				case 'Q'://just repeating code from bishop and rook
				{
					int startingCol = i<j ? 0 : i-j;
					int startingRow = i<j ? j-i : 0;
					int r = startingCol;
					int p;
					for(p = startingRow; p < 8 && r < 8; p++)
					{
						if(MakeMoveNoAppend(tempBoard,i,j,r,p,curTurnColor,myList))
						{
							tValue = SumBoard(tempBoard,curTurnColor);
							if(tValue>bestMoveValue)
							{
								bestMoveValue = tValue;
								colS = i;
								rowS = j;
								colD = r;
								rowD = p;
							}
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p >= 0 && r<8; p-- )
					{
						if(MakeMoveNoAppend(tempBoard,i,j,r,p,curTurnColor,myList))
						{
							tValue = SumBoard(tempBoard,curTurnColor);
							if(tValue>bestMoveValue)
							{
								bestMoveValue = tValue;
								colS = i;
								rowS = j;
								colD = r;
								rowD = p;
							}
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p < 8 && r>=0; p++ )
					{
						if(MakeMoveNoAppend(tempBoard,i,j,r,p,curTurnColor,myList))
						{
							tValue = SumBoard(tempBoard,curTurnColor);
							if(tValue>bestMoveValue)
							{
								bestMoveValue = tValue;
								colS = i;
								rowS = j;
								colD = r;
								rowD = p;
							}
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r--;
					}

					for(int q = 0; q < 8; q++)
					{
						if(q != i)///checking all adjacent columns on the current row j
						{
							if(MakeMoveNoAppend(tempBoard,i, j, q, j,curTurnColor,myList))
							{
								tValue = SumBoard(tempBoard,curTurnColor);
								if(tValue>bestMoveValue)
								{
									bestMoveValue = tValue;
									colS = i;
									rowS = j;
									colD = q;
									rowD = j;
								}
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
						if(q != j)
						{
							if(MakeMoveNoAppend(tempBoard,i,j,i,q,curTurnColor,myList))
							{
								tValue = SumBoard(tempBoard,curTurnColor);
								if(tValue>bestMoveValue)
								{
									bestMoveValue = tValue;
									colS = i;
									rowS = j;
									colD = i;
									rowD = q;
								}
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
					}
					break;
				}
			}
		}
	}
	char *ss = (char*)(malloc(sizeof(char)*2));
	char *dd = (char*)(malloc(sizeof(char)*2));
	ss[0] = colS + 'A';
	ss[1] = rowS + '1';
	dd[0] = colD + 'A';
	dd[1] = rowD + '1';
	MOVE *newMove = NewMove(getPiece(myBoard, colS, rowS), getPiece(myBoard,colD,rowD), ss, dd);
	return newMove;


}

// gets every single possible move on the board and stores them as children to root, all connected to one another by pointer links
void AllPossibilities(PIECE **myBoard, char curTurnColor, MLIST *myList, TREENODE *root)
{
	PIECE **tempBoard = copyBoard(myBoard);
	//int colS;
	//int rowS;
	//int colD;
	//int rowD;
	TREENODE *curNode;
	curNode = EmptyNode();
	SetChild(root,curNode);
	for(int i = 0 ; i < 8; i++)//nested loop that goes through entire board, looking for friendly pieces that could potentially move
	{
		for(int j = 0; j < 8; j++)
		{
			
			if(GetColor(getPiece(tempBoard,i,j)) != curTurnColor)//if its an enemy piece we cant manipulate it to do things so we skip it
			{
				continue;
			}
			switch(GetType(getPiece(tempBoard,i,j)))
			{
				case 'K':
				{
					//printf("Found a k\n");
					if(MakeMoveAppendNode(tempBoard,i,j,i-4,j,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i+3,j,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					for(int p = -1; p <=1; p++)//checking if we can move to any of the adjacent squares as the king and if we can, if we're still in check after moving. If we are then continue, but if we're out of check then return 1
					{
						for(int o = -1; o <=1; o++)
						{
							if(o !=0 || p != 0)
							{
								
								if(MakeMoveAppendNode(tempBoard,i,j,i+p,j+o,curTurnColor,myList,curNode))
								{
									TREENODE *newNodee = EmptyNode();
									SetNext(curNode,newNodee);
									curNode = newNodee;
									deleteBoard(tempBoard);
									tempBoard = copyBoard(myBoard);
								}
							}
						}
					}
					break;
				}
				case 'R':
				{
					//printf("Found a r\n");
					for(int p = 0; p < 8; p++)
					{
						if(p != i)///checking all adjacent columns on the current row j
						{
							
							if(MakeMoveAppendNode(tempBoard,i, j, p, j,curTurnColor,myList,curNode))
							{
								TREENODE *newNodee = EmptyNode();
								SetNext(curNode,newNodee);
								curNode = newNodee;
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
						if(p != j)
						{
							
							if(MakeMoveAppendNode(tempBoard,i,j,i,p,curTurnColor,myList,curNode))
							{
								TREENODE *newNodee = EmptyNode();
								SetNext(curNode,newNodee);
								curNode = newNodee;
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
					}
					break;
				}
				case 'P':
				{
					//printf("Found a p\n");
					int forward = ((curTurnColor == 'w') ? 1 : -1);

					
					if(MakeMoveAppendNode(tempBoard,i,j,i+1,j+forward,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i-1,j+forward,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i,j + forward,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					if(MakeMoveAppendNode(tempBoard,i,j,i,j + 2*forward,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}

					break;
				}
				case 'B':
				{
					//printf("Found a b\n");
					int startingCol = i<j ? 0 : i-j;
					int startingRow = i<j ? j-i : 0;
					int r = startingCol;
					int p;
					for(p = startingRow; p < 8 && r < 8; p++)
					{
						
						if(MakeMoveAppendNode(tempBoard,i,j,r,p,curTurnColor,myList,curNode))
						{
							TREENODE *newNodee = EmptyNode();
							SetNext(curNode,newNodee);
							curNode = newNodee;
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p >= 0 && r<8; p-- )
					{
						
						if(MakeMoveAppendNode(tempBoard,i,j,r,p,curTurnColor,myList,curNode))
						{
							TREENODE *newNodee = EmptyNode();
							SetNext(curNode,newNodee);
							curNode = newNodee;
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p < 8 && r>=0; p++ )
					{
						
						if(MakeMoveAppendNode(tempBoard,i,j,r,p,curTurnColor,myList,curNode))
						{
							TREENODE *newNodee = EmptyNode();
							SetNext(curNode,newNodee);
							curNode = newNodee;
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r--;
					}
					break;
				}
				case 'N':
				{
					//printf("Found a n\n");
					if(MakeMoveAppendNode(tempBoard,i,j,i+2,j+1,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i+1,j+2,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i-2,j+1,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i+1,j-2,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i+2,j-1,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i-1,j+2,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i-2,j-1,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					
					if(MakeMoveAppendNode(tempBoard,i,j,i-1,j-2,curTurnColor,myList,curNode))
					{
						TREENODE *newNodee = EmptyNode();
						SetNext(curNode,newNodee);
						curNode = newNodee;
						deleteBoard(tempBoard);
						tempBoard = copyBoard(myBoard);
					}
					break;
				}
				case 'Q'://just repeating code from bishop and rook
				{
					//printf("Found a q\n");
					int startingCol = i<j ? 0 : i-j;
					int startingRow = i<j ? j-i : 0;
					int r = startingCol;
					int p;
					for(p = startingRow; p < 8 && r < 8; p++)
					{
						
						if(MakeMoveAppendNode(tempBoard,i,j,r,p,curTurnColor,myList,curNode))
						{
							TREENODE *newNodee = EmptyNode();
							SetNext(curNode,newNodee);
							curNode = newNodee;
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p >= 0 && r<8; p-- )
					{
						
						if(MakeMoveAppendNode(tempBoard,i,j,r,p,curTurnColor,myList,curNode))
						{
							TREENODE *newNodee = EmptyNode();
							SetNext(curNode,newNodee);
							curNode = newNodee;
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r++;
					}
					r = startingCol;
					for(p = startingRow; p < 8 && r>=0; p++ )
					{
						
						if(MakeMoveAppendNode(tempBoard,i,j,r,p,curTurnColor,myList,curNode))
						{
							TREENODE *newNodee = EmptyNode();
							SetNext(curNode,newNodee);
							curNode = newNodee;
							deleteBoard(tempBoard);
							tempBoard = copyBoard(myBoard);
						}
						r--;
					}

					for(int q = 0; q < 8; q++)
					{
						if(q != i)///checking all adjacent columns on the current row j
						{
							
							if(MakeMoveAppendNode(tempBoard,i, j, q, j,curTurnColor,myList,curNode))
							{
								TREENODE *newNodee = EmptyNode();
								SetNext(curNode,newNodee);
								curNode = newNodee;
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
						if(q != j)
						{
							
							if(MakeMoveAppendNode(tempBoard,i,j,i,q,curTurnColor,myList,curNode))
							{
								TREENODE *newNodee = EmptyNode();
								SetNext(curNode,newNodee);
								curNode = newNodee;
								deleteBoard(tempBoard);
								tempBoard = copyBoard(myBoard);
							}
						}
					}
					break;
				}
			}
		}
	}

}

// make a move without appending it to myList, instead adds it to an empty node
int MakeMoveAppendNode(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor, MLIST *myList, TREENODE *blankNode)
{
	int isLeg = isLegal(myBoard,colSource,rowSource,colDestination,rowDestination,curTurnColor, myList);
	
	if(isLeg == 1)
	{
		PIECE *removedPiece = NULL;//tracking removed piece
		PIECE *movedPiece = getPiece(myBoard,colSource,rowSource);

		if(GetType(getPiece(myBoard,colSource,rowSource)) == 'K' && GetType(getPiece(myBoard,colDestination,rowDestination)) == 'R' && GetColor(getPiece(myBoard,colDestination,rowDestination)) == curTurnColor)//checking for castling
		{
			int directionToGo = (colDestination-colSource) > 0 ? 1 : -1;
			removedPiece = movePiece(myBoard,colSource, rowSource, colSource + directionToGo*2, rowDestination);//moving king 2 spaces towards rook. The removedPiece should be a blank square
			movePiece(myBoard,colDestination,rowDestination,colSource+directionToGo,rowDestination);//moving rook to space right next to the kin
			//AppendMove(myList, movedPiece, removedPiece, colSource, rowSource, colSource+directionToGo*2, rowDestination);
			//return 1;
		}
		else if(GetType(getPiece(myBoard,colSource,rowSource)) == 'P')
		{
			int enPassant = 0;  //variable to track whether we did en passant or not
			int forward = curTurnColor == 'w' ? 1 : -1;
			char enemyColor = curTurnColor=='w' ? 'b' : 'w';
			//REPEATING CODE FROM ISLEGALPAWN FUNCTION. THIS IS USED TO DETERMINE IF WE DO THE EXTRA STEP OF REMOVING THE PAWN AS PER EN PASSANT
			if(isEmpty(myBoard,colDestination,rowDestination) )//if the spot is empty
			{
				if(abs(colSource-colDestination) == 1 && (forward*(rowDestination-rowSource)) == 1 )//checking for en passant, this covers a diagonal move
				{
					if(GetType(getPiece(myBoard,colDestination,rowDestination-forward)) == 'P' && GetColor(getPiece(myBoard,colDestination,rowDestination-forward)) == enemyColor)//if the piece right behind destination is an enemy pawn we can capture it
					{
						if(myList->last->move->source[0] == ('A' + colDestination) && myList->last->move->source[1] == ('1'+rowDestination+forward))//checking if enemypawn was previously in space in front of the destination square. If it is then the move is en passant and is legal
						{
							movePiece(myBoard,colSource,rowSource,colDestination,rowDestination);
							removedPiece = movePiece(myBoard,colSource, rowSource, colDestination,rowDestination-forward);//remove the piece right behind the destination square to capture en passant
							//MOVE *newMove = NewMove(getPiece(myBoard,colSource,rowSource),removedPawn), 
							enPassant = 1;

						}
						else
						{
							//printf("No en passant, list contents: %c, %c\n", myList->last->move->source[0],myList->last->move->source[1]);
						}
					}
				}
			}
			if(enPassant != 1)//if en passant didnt happen
			{
				removedPiece = movePiece(myBoard,colSource,rowSource,colDestination,rowDestination);
			}

		}
		else
		{
			removedPiece = movePiece(myBoard,colSource,rowSource,colDestination,rowDestination);

		}
		//printf("Moved from %d%d to %d%d\n",colSource,rowSource, colDestination,rowDestination);
		char *ss = (char*)(malloc(sizeof(char)*2));
		char *dd = (char*)(malloc(sizeof(char)*2));
		ss[0] = colSource+'A';
		dd[0] = colDestination + 'A';
		ss[1] = rowSource+'1';
		dd[1] = rowDestination+'1';
		MOVE *newMove = NewMove(movedPiece,removedPiece,ss,dd);
		SetMove(blankNode, newMove);
		return 1;
	}
	else if (isLeg == 0)
	{
		//printf("Illegal going from %d%d to %d%d\n",colSource,rowSource,colDestination,rowDestination);
		return 0;
	}
	else
	{
		//printf("Uknown error\n");
		return 0;
	}
	//return 0;
}

// makes the first ai move using a small library of known chess moves 
int MakeOpeningMove(PIECE **myBoard, char curTurnColor, MLIST *myList)
{
	if(SicilianDefense(myBoard,curTurnColor,myList))
	{
		return 1;
	}
	if(QueensGambit(myBoard,curTurnColor,myList))
	{
		return 1;
	}
	if(DutchDefense(myBoard,curTurnColor,myList))
	{
		return 1;
	}
	if(EnglishOpening(myBoard,curTurnColor,myList))
	{
		return 1;
	}
	else
	{
		if(curTurnColor == 'w')
		{
			MakeMove(myBoard, 0, 1, 2, 2, curTurnColor, myList);
			return 1;
		}
		else
		{
			MakeMove(myBoard, 6, 7, 5, 5, curTurnColor, myList);
			return 1;
		}
	}



}

// sicilian defense opening move
int SicilianDefense(PIECE **myBoard, char curTurnColor, MLIST *myList)
{
	if(curTurnColor == 'w')
	{
		MakeMove(myBoard, 4, 1, 4, 3, curTurnColor, myList);
		return 1;
	}
	if(curTurnColor == 'b' && GetType(getPiece(myBoard,4,3)) == 'P')
	{
		MakeMove(myBoard, 2, 6, 2, 4, curTurnColor, myList);
		return 1;
	}
	else 
	{
		return 0;
	}
}

// queen's gambit opening move
int QueensGambit(PIECE **myBoard, char curTurnColor, MLIST *myList)
{
	if(curTurnColor == 'w')
	{
		MakeMove(myBoard, 3, 1, 3, 3, curTurnColor, myList);
		return 1;
	}
	if(curTurnColor == 'b' && GetType(getPiece(myBoard,2,3)) == 'P')
	{
		MakeMove(myBoard, 3, 6, 3, 4, curTurnColor, myList);
		return 1;
	}
	else
	{
		return 0;
	}
}

// english opening, opening move
int EnglishOpening(PIECE **myBoard, char curTurnColor, MLIST *myList)
{
	if(curTurnColor == 'w')
	{
		MakeMove(myBoard,2,1,2,3,curTurnColor,myList);
		return 1;
	}
	else
	{
		return 0;
	}
}

// dutch defense opening move
int DutchDefense(PIECE **myBoard, char curTurnColor, MLIST *myList)
{
	if(curTurnColor == 'b' && GetType(getPiece(myBoard,3,3)) == 'P')
	{
		MakeMove(myBoard,5,6,5,4,curTurnColor,myList);
		return 1;
	}
	else
	{
		return 0;
	}
}

// EOF //
