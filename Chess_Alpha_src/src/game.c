#include <stdio.h>
#include <stdlib.h>
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
	if(colSource == colDestination && rowSource == rowDestination)
	{
		printf("Error: Destination same as beginning\n");
		return 0;
	}
	if(isEmpty(myBoard,colSource,rowSource) == 1)
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
	if(GetType(getPiece(myBoard,colSource,rowSource)) != 'K' )//castling
	{
		if(GetColor(getPiece(myBoard,colSource,rowSource)) == GetColor(getPiece(myBoard,colDestination,rowDestination)) )
		{
			printf("Error: Destination square contains a friendly piece. Illegal move\n");
			//printf("%c %d %d",GetColor(getPiece(myBoard,colSource,rowSource)),colSource,rowSource);
			//printf("%c %d %d",GetColor(getPiece(myBoard,colDestination,rowDestination)),colDestination,rowDestination);
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
	printf("Error: Invalid type present \n");
	return 0;


}

int isLegalPawn(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{

	//char enemyColor = curTurnColor=='w' ? 'b' : 'w';//determines enemy color
	int forward;
	if(GetColor(getPiece(myBoard,colSource, rowSource)) == 'w')
	{
		forward = 1;//because white is in the front row, numbered starting from 0, we need a forward multiplier to determine which was is direction for our chosen piece
	}
	else
	{
		forward = -1;
	}
	if(isEmpty(myBoard,colDestination,rowDestination) )//if the spot is empty
	{
		if(colSource == colDestination && (forward*(rowDestination-rowSource) == 1))//checking if pawn is moving only forward
		{
			return 1;
		}
		if(colSource == colDestination && (forward*(rowDestination-rowSource) == 2))//covers a 2 square jump 
		{
			if((curTurnColor == 'w' && rowSource == 1 ) || (curTurnColor == 'b' && rowSource == 6 ))//checks if the pawn is in initial position
			{
				if(isEmpty(myBoard,colDestination,rowSource+forward) )//if the spot one spot forward from the pawn is empty, then it is legal
				{
					return 1;
				}
			}
		}

	}
	else //if the spot has a piece in it. We've already checked if the piece there is friendly or not, so by this point itll always be an enemy piece
	{
		if ((rowDestination-rowSource == 1 || rowSource-rowDestination ==1) && (forward*(colDestination-colSource) == 1))//checks for a diagonal capture
		{
			return 1;
		}	
	}
	return 0;//if it didnt get caught by any of the above then its invalid
}

int isLegalKnight(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{
	if( (abs(rowSource - rowDestination) == 1 && abs(colSource-colDestination) == 2) || (abs(rowSource - rowDestination) == 2 && abs(colSource-colDestination) == 1) )//we only need to check if the knight's new position is an l shape and thats it
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isLegalRook(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{
	int directionToGo;

	if(rowSource == rowDestination)
	{
		directionToGo = colDestination-colSource > 0 ? 1 : -1;//if destination is greater than source, we need to go forward and if its less than or behind source, we go backwards
		for(int i = colSource+directionToGo; i != colDestination; i+= directionToGo)//starts at one square towards destination and repeatedly checks for empty spaces between then and here
		{
			if(!isEmpty(myBoard,i,rowSource))
			{
				return 0;
			}
		}
		return 1;//if there were all empty spaces then the path is clear and its legal
	}
	else if (colSource == colDestination)
	{
		directionToGo = rowDestination-rowSource > 0 ? 1 : -1;//if destination is greater than source, we need to go forward and if its less than or behind source, we go backwards
		for(int i = rowSource+directionToGo; i != rowDestination; i+= directionToGo)//starts at one square towards destination and repeatedly checks for empty spaces between then and here
		{
			if(isEmpty(myBoard,colSource,i))
			{
				return 0;
			}
		}
		return 1;//if there were all empty spaces then the path is clear and its legal
	}
	else 
	{
		return 0;
	}
}

int isLegalBishop(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{
	int directionToGoX;
	int directionToGoY;
	if(abs(rowSource-rowDestination) == abs(colSource - colDestination))//checking to see if the diagonal is proportional, 1:1
	{
		directionToGoX = colDestination-colSource > 0 ? 1 : -1;//direction the X axis moves, or by column
		directionToGoY = rowDestination-rowSource > 0 ? 1 : -1;//direction the Y axis moves, or by row
		int j = rowSource+directionToGoY;
		for(int i = colSource+directionToGoX; i != colDestination; i+= directionToGoX)//starts at one square towards destination and repeatedly checks for empty spaces between then and here
		{
			if(isEmpty(myBoard,i,j))
			{
				return 0;
			}
			j+=directionToGoY;
		}
		return 1;//if there were all empty spaces then the path is clear and its legal
	}

	else 
	{
		return 0;
	}
}

int isLegalQueen(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)//this function is just a combination of rook and bishop
{
	int directionToGo; //the straight move direction check
	int directionToGoX; //x and y directional checks
	int directionToGoY;
	if(rowSource == rowDestination)
	{
		directionToGo = colDestination-colSource > 0 ? 1 : -1;//if destination is greater than source, we need to go forward and if its less than or behind source, we go backwards
		for(int i = colSource+directionToGo; i != colDestination; i+= directionToGo)//starts at one square towards destination and repeatedly checks for empty spaces between then and here
		{
			if(isEmpty(myBoard,i,rowSource))
			{
				return 0;
			}
		}
		return 1;//if there were all empty spaces then the path is clear and its legal
	}
	else if (colSource == colDestination)
	{
		directionToGo = rowDestination-rowSource > 0 ? 1 : -1;//if destination is greater than source, we need to go forward and if its less than or behind source, we go backwards
		for(int i = rowSource+directionToGo; i != rowDestination; i+= directionToGo)//starts at one square towards destination and repeatedly checks for empty spaces between then and here
		{
			if(isEmpty(myBoard,colSource,i))
			{
				return 0;
			}
		}
		return 1;//if there were all empty spaces then the path is clear and its legal
	}
	if(abs(rowSource-rowDestination) == abs(colSource - colDestination))//checking to see if the diagonal is proportional, 1:1
	{
		directionToGoX = colDestination-colSource > 0 ? 1 : -1;//direction the X axis moves, or by column
		directionToGoY = rowDestination-rowSource > 0 ? 1 : -1;//direction the Y axis moves, or by row
		int j = rowSource+directionToGoY;
		for(int i = colSource+directionToGoX; i != colDestination; i+= directionToGoX)//starts at one square towards destination and repeatedly checks for empty spaces between then and here
		{
			if(isEmpty(myBoard,i,j))
			{
				return 0;
			}
			j+=directionToGoY;
		}
		return 1;//if there were all empty spaces then the path is clear and its legal
	}
	else 
	{
		return 0;
	}
}

int isLegalKing(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{
	if(GetColor(getPiece(myBoard,colDestination,rowDestination)) == curTurnColor && GetType(getPiece(myBoard,colDestination,rowDestination)) == 'R')//if other piece is a friendly rook
	{
		if(curTurnColor == 'w')
		{
			if(colSource == 4 && rowSource == 0 && rowDestination == 0 && (colDestination == 0 || colDestination == 7))//king and rook has to be in a hardcoded starting position
			{
				int forward = (colDestination-colSource) > 0 ? 1 : -1;
				for(int i = colSource + forward; i != colDestination; i+=forward)
				{
					if(!isEmpty(myBoard,i,rowSource)) //if theres any pieces between the king and rook then it cant castle
					{
						return 0;
					}
				}
				return 1;//if it made it past all the checks then it is legal move
			}
			else
			{
				return 0;
			}
		}
		else if(curTurnColor == 'b')
		{
			if(colSource == 3 && rowSource == 7 && rowDestination == 7 && (colDestination == 0 || colDestination == 7))
			{
				int forward = (colDestination-colSource) > 0 ? 1 : -1;
				for(int i = colSource + forward; i != colDestination; i+=forward)
				{
					if(!isEmpty(myBoard,i,rowSource)) //if theres any pieces between the king and rook then it cant castle
					{
						return 0;
					}
				}
				return 1;//if it made it past all the checks then it is legal move
			}
			else
			{
				return 0;
			}
			
		}
		else
		{
			printf("Invalid color \n");
			return 0;
		}
	}
	else if(abs(rowDestination-rowSource) <= 1 && abs(colDestination-colSource) <=1 )//ensures the king is only moving in a single square around it
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int MakeMove(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{
	int isLeg = isLegal(myBoard,colSource,rowSource,colDestination,rowDestination,curTurnColor);
	//char sPiece = GetType(getPiece(myBoard,colSource,rowSource));
	//char dPiece = GetType(getPiece(myBoard,colDestination,rowDestination));
	if(isLeg == 1)
	{
		if(GetType(getPiece(myBoard,colSource,rowSource)) == 'K' && GetType(getPiece(myBoard,colDestination,rowDestination)) == 'R' && GetColor(getPiece(myBoard,colDestination,rowDestination)) == curTurnColor)//checking for castling
		{
			int directionToGo = (colDestination-colSource) > 0 ? 1 : -1;
			PIECE *tempTBD = movePiece(myBoard,colSource, rowSource, colSource + directionToGo*2, rowDestination);//moving king 2 spaces towards rook
			PIECE *tempTBD2 = movePiece(myBoard,colDestination,rowDestination,colSource-directionToGo,rowDestination);//moving rook to space right next to the king
			free(tempTBD); //TO BE IMPLEMENTED: Currently causing an error: Pointer freed was not allocated. Unusual. Needs to be fixed to prevent memory leaks
			free(tempTBD2);//TO BE IMPLEMENTED: Currently causing an error: Pointer freed was not allocated. Unusual. Needs to be fixed to prevent memory leaks
			return 1;
		}
		else if(GetType(getPiece(myBoard,colSource,rowSource)) == 'P')
		{
			//en passant implementation
		}
		else
		{
			PIECE *tempTBD = movePiece(myBoard,colSource,rowSource,colDestination,rowDestination);
			//free(tempTBD); //TO BE IMPLEMENTED: Currently causing an error: Pointer freed was not allocated. Unusual. Needs to be fixed to prevent memory leaks
			return 1;
		}
	}
	else if (isLeg == 0)
	{
		return 0;
	}
	else
	{
		printf("Uknown error\n");
		return 0;
	}
	return 0;
}



int Castle(PIECE** myBoard, int colSource, int rowSource, int colDestination, int rowDestination, char curTurnColor)
{
	return 0;
}

int isChecked(PIECE **myBoard, char curTurnColor){
	return 0;
}

int isCheckmate(PIECE **myBoard, char curTurnColor){
	return 0;
}
