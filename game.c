#include "game.h"
#include "piece.h"
#include "board.h"

int isLegal(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{
	if( colDestination < 0 || colDestination > 7 || rowDestination < 0 || rowDestination > 7 )
	{
		printf("Error: Out of bounds destination\n");
		return 0;
	}
	if(colSource < 0 || colSource > 7 || rowSource < 0 || rowSource > 7 )
	{
		printf("Error: Out of bounds destination\n");
		return 0;
	}
	if(getPiece(myBoard,colSource,rowSource) == NULL)
	{
		//if there isnt anything at the selected source then it automatically fails
		printf("Error: No piece at selected location\n");
		return 0;
	}
	if(GetColor(getPiece(myBoard,colSource,rowSource)) != curTurnColor)
	{
		printf("Error: Opponent's piece selected! It is currently player %c's turn.\n",curTurnColor);
		return 0;
	}
	if(GetType(getPiece(myBoard,colSource,rowSource)) != 'R' || GetType(getPiece(myBoard,colSource,rowSource)) != 'K' )
	{
		if(GetColor(getPiece(myBoard,colSource,rowSource)) == GetColor(getPiece(myBoard,colDestination,rowDestination)) )
		{
			printf("Error: Destination square contains a friendly piece. Illegal move\n");
			return 0;
		}
	}

	switch(GetType(getPiece(myBoard,colSource,rowSource)))
	{
		case 'P': 
		{
			if(isLegalPawn(myBoard,colSource,rowSource,colDestination,rowDestination, curTurnColor))//we create a temporary array to test the move and see if it opens up to a check
			{
				PIECE **tempBoard = makeBoard();
				memcpy(tempBoard, myBoard,sizeof(PIECE)*8*8);//copying array
				movePiece(tempBoard,colSource,rowSource,colDestination,rowDestination);
				if(!isChecked(tempBoard, curTurnColor))//if its not checked
				{
					deleteBoard(tempBoard);
					return 1;//return a success marker
				}
				else
				{
					printf("Error: This move leaves friendly king open to check\n");
					deleteBoard(tempBoard);
					return 0;
				}
			}
			else
			{
				printf("Error: Illegal move.\n");
				return 0;
			}
			break;
		}
		case 'R': 
		{
			if(isLegalRook(myBoard,colSource,rowSource,colDestination,rowDestination, curTurnColor))
			{
				PIECE **tempBoard = makeBoard();
				memcpy(tempBoard, myBoard,sizeof(PIECE)*8*8);//copying array
				movePiece(tempBoard,colSource,rowSource,colDestination,rowDestination);
				if(!isChecked(tempBoard, curTurnColor))//if its not checked
				{
					deleteBoard(tempBoard);
					return 1;//return a success marker
				}
				else
				{
					printf("Error: This move leaves friendly king open to check\n");
					deleteBoard(tempBoard);
					return 0;
				}
			}
			else
			{
				printf("Error: Illegal move.\n");
				return 0;
			}
			break;
		}
		case 'N': 
		{
			if(isLegalKnight(myBoard,colSource,rowSource,colDestination,rowDestination, curTurnColor))
			{
				PIECE **tempBoard = makeBoard();
				memcpy(tempBoard, myBoard,sizeof(PIECE)*8*8);//copying array
				movePiece(tempBoard,colSource,rowSource,colDestination,rowDestination);
				if(!isChecked(tempBoard, curTurnColor))//if its not checked
				{
					deleteBoard(tempBoard);
					return 1;//return a success marker
				}
				else
				{
					printf("Error: This move leaves friendly king open to check\n");
					deleteBoard(tempBoard);
					return 0;
				}
			}
			else
			{
				printf("Error: Illegal move.\n");
				return 0;
			}
			break;
		}
		case 'B': 
		{
			if(isLegalBishop(myBoard,colSource,rowSource,colDestination,rowDestination, curTurnColor))
			{
				PIECE **tempBoard = makeBoard();
				memcpy(tempBoard, myBoard,sizeof(PIECE)*8*8);//copying array
				movePiece(tempBoard,colSource,rowSource,colDestination,rowDestination);
				if(!isChecked(tempBoard, curTurnColor))//if its not checked
				{
					deleteBoard(tempBoard);
					return 1;//return a success marker
				}
				else
				{
					printf("Error: This move leaves friendly king open to check\n");
					deleteBoard(tempBoard);
					return 0;
				}
			}
			else
			{
				printf("Error: Illegal move.\n");
				return 0;
			}
			break;
		}
		case 'K': 
		{
			if(isLegalKing(myBoard,colSource,rowSource,colDestination,rowDestination, curTurnColor)) //in the event of castling, we need to do a special checl
			{
				PIECE **tempBoard = makeBoard();
				memcpy(tempBoard, myBoard,sizeof(PIECE)*8*8);//copying array
				if(GetType(getPiece(myBoard,colDestination,rowDestination)) == 'R')//this checks for castling. If we're castling we need to do a special maneuver
				{
					int distance = colDestination - colSource;
					//distance = distance>0 ? distance : -1*distance;//ensure distance is positive
					if(distance<0)
					{
						movePiece(tempBoard, colSource, rowSource, colSource-2, rowSource);
						movePiece(tempBoard, colDestination, rowDestination, colDestination + (distance-1),rowDestination);
					}
					else
					{
						movePiece(tempBoard, colSource, rowSource, colSource+2, rowSource);
						movePiece(tempBoard, colDestination, rowDestination, colDestination - (distance-1),rowDestination);
					}
				}
				else
				{
					movePiece(tempBoard, colSource, rowSource, colDestination,rowDestination);
				}
				if(!isChecked(tempBoard, curTurnColor))
				{
					deleteBoard(tempBoard);
					return 1;//return a success marker
				}
				else
				{
					printf("Error: This move leaves friendly king open to check\n");
					deleteBoard(tempBoard);
					return 0;
				}
			}
			else
			{
				printf("Error: Illegal move.\n");
				return 0;
			}
			break;
		}
		case 'Q': 
		{
			if(isLegalQueen(myBoard,colSource,rowSource,colDestination,rowDestination, curTurnColor))
			{
				PIECE **tempBoard = makeBoard();
				memcpy(tempBoard, myBoard,sizeof(PIECE)*8*8);//copying array
				movePiece(tempBoard,colSource,rowSource,colDestination,rowDestination);
				if(!isChecked(tempBoard, curTurnColor))//if its not checked
				{
					deleteBoard(tempBoard);
					return 1;//return a success marker
				}
				else
				{
					printf("Error: This move leaves friendly king open to check\n");
					deleteBoard(tempBoard);
					return 0;
				}
			}
			else
			{
				printf("Error: Illegal move.\n");
				return 0;
			}
			break;
		}
	}


}

int isLegalPawn(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{

}

int isLegalKnight(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor){
}

int isLegalRook(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor){
}

int isLegalBishop(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor){
}

int isLegalQueen(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor){
}

int isLegalKing(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor){
}

int makeMove(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor){
}

int Castle(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{

}

int isChecked(PIECE **myBoard, char curTurnColor){

}

int isCheckmate(PIECE **myBoard, char curTurnColor){
}
