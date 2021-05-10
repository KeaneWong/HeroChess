/************************************************************************/
/* 		HeroChess V1.0 by The Avengineers			*/
/* 		EECS 22L - University of California, Irvine		*/
/*									*/
/* main.c: contains main game function and print menu function		*/
/*									*/
/* Modifications:							*/
/* Date (YYYY/MM/DD)	Author			Description		*/
/* 2021/04/17		Paul Lee		Initial Version		*/
/************************************************************************/

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
// main function
int main(void){
	PIECE **board = makeBoard();
	initializeBoard(board);
	MLIST *myList = NewMoveList();

	#ifndef DEBUG				///MAIN PROGRAM: NON-DEBUG MODE
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
						checkForPromotion(board);
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
				printf("Replay: \n");
				replay(myList);
				break;
			}
			case 2:
			{
				int won = 1;
				char curTurnColor = 'w';
				int turncount = 0;
				while(won!=2)
				{
					printBoard(board);	
					printf("Player white pick your piece: \n");
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
					if(success == 0)
					{
						printf("Error. Try again\n");
						
					}
					else if (success == 1)
					{
						checkForPromotion(board);
						if(isChecked(board,'w'))
						{
							if(isCheckmate(board, 'w', myList))
							{
								printf("Checkmate. Winner is Human\n");
								won = 2;
							}
							else
							{
								printf("Human Player is in check.\n");	
							}
						}
						if(won!=2)
						{
							/*ai turn*/
							int aisuccess;
							curTurnColor = 'b'; 
							
							if(turncount == 0){
								aisuccess = MakeOpeningMove(board, curTurnColor, myList);
							}
							else{
									
							}
							
							
							if(aisuccess == 0)
							{
								printf("Error. Try again\n");

							}
							else if (aisuccess == 1)
							{
								if(isChecked(board,'b'))
								{
									if(isCheckmate(board, curTurnColor, myList))
									{
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
					turncount++;
				}
				printf("Replay: \n");	
				replay(myList);
				break;
				/* HvH func */
				/* print moves log? */
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


	#ifdef DEBUG
	printf("Hello World\n");

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
	if((a>'H' && a < 'a') || a  <'A' || a > 'h')
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



