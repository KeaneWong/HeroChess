/* main.c: file containing main function and print menu function */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piece.h"
#include "board.h"
#include "game.h"
#include "movelist.h"
#include "settings.h"
#include "replay.h"
#include "ai.h"
#define INPUT_BUFFER 20
// print menu function declaration
int mainmenu(void);
int convertColumn(char a);
int convertRow(char b);
void undo(PIECE **board, MLIST *myList);
void unitTest();
void gameTest();
// main function
int main(void){
	#ifdef DEBUG
	unitTest(); 
   	gameTest();
	#else
	PIECE **board = makeBoard();
	initializeBoard(board);
	MLIST *myList = NewMoveList();

				///MAIN PROGRAM: NON-DEBUG MODE
	char str[INPUT_BUFFER];//input buffer

	// welcome message prints once at the start of the first game
	printf("Welcome to HeroChess v1.0\n");

	// default settings: white - player 1, black - player 2
	int wp = 1;
	int bp = 2;

	// main menu keeps printing after each game until user decides to exit
	int exit = 0;
	while(exit == 0)
	{
		/* print board here? */
		int option = mainmenu();
		switch(option)
		{
			case 1:
			{
				/* HvH function*/
				/* print moves log? */
				int won = 1;
				char curTurnColor = 'w';

				while(won!=2)
				{
					printBoard(board);
					printf("To quit the game at any point, enter Q or q.\n");	
					printf("Player %d pick your piece: \n", curTurnColor=='w' ? wp:bp);
					fgets(str,INPUT_BUFFER,stdin);
					int column1;
					int row1;
					column1 = convertColumn(str[0]);
					row1 = convertRow(str[1]);
					
					if(column1 < 0 || row1 < 0)
					{
						continue;
					}

					printf("Where would you like to move this piece?\n");
					fgets(str,INPUT_BUFFER,stdin);
					int column2;
					int row2;
					column2 = convertColumn(str[0]);
					row2 = convertRow(str[1]);
					
					int success = MakeMove(board,column1, row1, column2, row2,curTurnColor,myList);
					if(success == 0)//signifies error
					{
						printf("Error. Try again\n");
						
					}
					else if (success == 1)
					{
						//printf("Successful move. \n");
						if(isChecked(board,((curTurnColor == 'w') ? 'b' : 'w')) )//checking if the opponent is in check. 
						{
							if(isCheckmate(board, ((curTurnColor == 'w') ? 'b' : 'w'), myList ))//if the opponent is in check we check for checkmate
							{
								printf("Checkmate. Winner is player %d!\n", curTurnColor=='w' ? wp:bp);
								won = 2;
							}
							else
							{
								printf("%c Player is in check.\n",((curTurnColor == 'w') ? 'b' : 'w'));	//
							}
						}
						if(won!=2)
						{
							//printf("Flipping color\n");
							curTurnColor = (curTurnColor == 'w') ? 'b' : 'w';//flipping turn color while the game still goes on
						}
					}
				}
				char o;
				printf("Do you want to save the replay of the game? (Y/N):");
				o = getchar();
				if(o == 'Y' || o == 'y'){
					replay(myList);
				}
				break;
				break;
			}
			case 2:
			{
				int won = 1;
				char curTurnColor = 'w';
				int firstTurn = 1;
				char u;
				while(won!=2)
				{
					printBoard(board);
					printf("To quit the game at any point, enter Q or q.\n");	
					printf("Player white pick your piece: \n");
					scanf("%[^\n]%*c", str);
					//fgets(str,INPUT_BUFFER,stdin);
					int column1;
					int row1;
					column1 = convertColumn(str[0]);
					row1 = convertRow(str[1]);

					if(column1 < 0 || row1 < 0)
					{
						continue;
					}

					printf("Where would you like to move this piece?\n");
					fgets(str,INPUT_BUFFER,stdin);
					int column2;
					int row2;
					column2 = convertColumn(str[0]);
					row2 = convertRow(str[1]);
					
					int success = MakeMove(board,column1, row1, column2, row2,curTurnColor,myList);
					if(success == 0)
					{
						printf("Error. Try again\n");
						
					}
					else if (success == 1)
					{
						if(isChecked(board,'b'))
						{
							if(isCheckmate(board, 'b', myList))
							{
								printf("Checkmate. Winner is Human\n");
								won = 2;
							}
							else
							{
								printf("Human Player is in check.\n");	
							}
						}
						printBoard(board);
						if(won!=2)
						{
							/*ai turn*/
							int aisuccess;
							curTurnColor = (curTurnColor == 'w' ? 'b' : 'w') ; 
							
							//MOVE *highesteval;
							if(firstTurn)
							{
								printf("Opening move\n");
								aisuccess = MakeOpeningMove(board, curTurnColor, myList);
								firstTurn = 0;
							}
							else
							{
								printf("Doing AI move\n");
								aisuccess = GetAITurn(board,curTurnColor,myList, 2);
							}
							if(aisuccess == 0)
							{
								printf("Error. Try again\n");

							}
							else if (aisuccess == 1)
							{
								if(isChecked(board,curTurnColor == 'w' ? 'b' : 'w'))
								{
									if(isCheckmate(board, curTurnColor == 'w' ? 'b' : 'w', myList))
									{
										printBoard(board);
										printf("Checkmate. Winner is AI\n");
										won = 2;
									}
									else
									{
										printf("AI Player is in check.\n");	
									}
								}
								
								if(won!=2)
								{
									curTurnColor = (curTurnColor == 'b') ? 'w' : 'b';//flipping turn color while the game still goes on
								}
							}
						
						}
					}
					if(GetLength(myList)>2){
  						printBoard(board);
  						printf("Do you want to undo the last move? (Y/N)");
  						scanf("%[^\n]%*c", &u);
  						if(u == 'y' || u == 'Y'){
  							undo(board, myList);	
  						}
  					}
				}
				char o;
				printf("Do you want to save the replay of the game? (Y/N):");
				o = getchar();
				if(o == 'Y' || o == 'y'){
					replay(myList);
				}
				break;
			}
			case 3:
			{
				/* settings function */
				
				int option = 0;
				int done = 0;	
				
				/* settings menu keeps printing until user decides to go back to the main menu or makes changes */
				while (done == 0)
				{
					printf("Welcome to Settings!\n");
					printf("1. Change Player Colors\n");
					//printf("2. Change Timer Settings\n");
					printf("2. Go Back to Main Menu\n");
					scanf("%d", &option);
					getchar();
				
					switch(option)
					{
						case 1:
						{
							wp = whitepnum();
							bp = blackpnum(wp);
							done = 1;
							break;
						}
						
						//case 2:
						//{
						//	selection();
						//	done = 1;
						//	break;
						//}
						
						case 2:
						{
							done = 1;
							break;
						}
		
					}
				
				}
				break;
			}
			case 4:
			{
				printf("Thanks for playing. Exiting game...\n");
				exit=1;
				break;
			}
		}
		
	}
	#endif

	/* free memory of structs? */
}

// print menu function definition
int mainmenu()
{
	int select = 0;
	printf("1. Start New Game (Human v. Human)\n");
	printf("2. Start New Game (Human v. AI)\n");
	printf("3. Game Settings\n");
	printf("4. Exit Game\n");
	printf("Choose Option: ");
	scanf("%d",&select);
	getchar();
	return select;
}

int convertColumn(char a)
{
	int column1;
	if( a == 'Q' || a == 'q' )
	{
		printf("Quitting game... Thanks for playing!\n");
		exit(0);	
	}
	else if((a>'H' && a < 'a') || a  <'A' || a > 'h')
	{
		printf("Error: Out of bounds column option\n");
		column1 = -1;
	}
	else
	{
		column1 = (a >='A' && a <= 'H') ? (a-'A') : (a-'a');
	}
	return column1;
}
int convertRow(char b)
{
	return b-'1';
}

void undo(PIECE **board, MLIST *l){
	int i = 0;
	int cs, rs, cd ,rd;
	MOVE *m = NULL;
	PIECE p;
	for(i = 0; i < 2; i++){
		m = RemoveLastMove(l);
	    cs = getColS(m);
	    rs = getRowS(m);
	    cd = getColD(m);
	    rd = getRowD(m);
		p = GetRemovedPiece(m);
	    placePiece(board, &p, cs, rs);
		p = GetPiece(m);
	    placePiece(board, &p, cd, rd);
	}	
}

void unitTest(){
	printf("Testing piece.c...\n\n");
	
	printf("Creating a White Pawn\n");
	PIECE *p = NewPiece('P', 'w');
	printf("Color: %c Type: %c\n\n", GetColor(p), GetType(p));
	
	printf("Creating a black Queen\n");
	PIECE *q = NewPiece('Q', 'b');
	printf("Color: %c Type: %c\n\n", GetColor(q), GetType(q));
	
	printf("Creating a blank space\n");
	PIECE b = makeBlank();
	printf("Color: %c Type: %c\n\n", GetColor(&b), GetType(&b));
	
	printf("Setting the White Pawn to White Bishop\n");
	SetType(p, 'B');
	printf("Color: %c Type: %c\n\n", GetColor(p), GetType(p));

	printf("----------------------------------------------------\n");

	printf("testing board.c...\n");
    PIECE **testBoard = makeBoard();
    printf("Creating a new board...\n");
    int i = 0, j = 0;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			PIECE e = makeBlank();
			placePiece(testBoard, &e, i, j);
		}
	}
	printBoard(testBoard);
	printf("Placing Pieces\n");
	placePiece(testBoard, p, 3, 3);
	placePiece(testBoard, p, 1, 6);
	placePiece(testBoard, q, 7, 2);	
	printBoard(testBoard);	
	
	printf("\nChecking for empty squares...\n");
	printf("Square H3 is %s\n", isEmpty(testBoard, 7, 2) ? "Empty" : "Not empty" );	
	printf("Square A1 is %s\n", isEmpty(testBoard, 1, 1) ? "Empty" : "Not empty" );
	
	printf("\nMoving pieces...\n");
	printf("Moving White Bishop in D4 to E5\n");
	movePiece(testBoard, 3, 3, 4, 4);
	printBoard(testBoard);
	
	printf("\nRemoving a piece from board\n");
	removePiece(testBoard, 4, 4);
	printBoard(testBoard);

	printf("---------------------------------------------------\n");
	printf("\n\nTesting move and movelist...\n\n");
	printf("Generating new moves and a movelist\n");
	MLIST *l = NewMoveList();
	AppendMove(l, p, q, 1, 1, 1, 2);
	AppendMove(l, &b, p, 5, 3, 2, 1);
	AppendMove(l, q, p, 7, 6, 3, 4);
	printf("Move list\n");
	PrintMoveList(l);

	printf("\nRemoving the last move\n");
	RemoveLastMove(l);
	PrintMoveList(l);

	printf("\nEvaluating moves...\n");
	printf("Piece moved / source / destination\n");
	MOVE *t = RemoveFirstMove(l);
	PrintMove(t);

}

void gameTest(){
	printf("System Test...\n");
	PIECE **testBoard = makeBoard();
	initializeBoard(testBoard);
	printBoard(testBoard);
	MLIST *testList = NewMoveList();
	MakeMove(testBoard, 4, 1, 4, 3,'w',testList);
	printBoard(testBoard);
	printf("-----------------------------------\n");
	MakeMove(testBoard, 4, 6, 4, 4,'b',testList);
	printBoard(testBoard);
	printf("-----------------------------------\n");
	MakeMove(testBoard, 5, 0, 2, 3,'w',testList);
	printBoard(testBoard);
	printf("-----------------------------------\n");
	MakeMove(testBoard, 1, 7, 2, 5,'b',testList);
	printBoard(testBoard);
	printf("-----------------------------------\n");
	MakeMove(testBoard, 3, 0, 7, 4,'w',testList);
	printf("-----------------------------------\n");
	printBoard(testBoard);
	MakeMove(testBoard, 3, 6, 3, 5,'b',testList);
	printf("-----------------------------------\n");
	printBoard(testBoard);
	MakeMove(testBoard, 2, 3, 5, 5,'w',testList);
	printf("-----------------------------------\n");
	printBoard(testBoard);
	
	
	if(isChecked(testBoard, 'b') && isCheckmate(testBoard, 'b', testList)){
		printf("Checkmate. Winner is player white!");
	}
	replay(testList);
}

