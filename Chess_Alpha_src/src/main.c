/* main.c: file containing main function and print menu function */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piece.h"
#include "board.h"
#include "game.h"
#define INPUT_BUFFER 20
// print menu function declaration
int mainmenu(void);
int convertColumn(char a);
int convertRow(char b);
// main function
int main(void){
	PIECE **board = makeBoard();
	initializeBoard(board);
	char str[INPUT_BUFFER];//input buffer

	// welcome message prints once at the start of the first game
	printf("Welcome to HeroChess v1.0\n");

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
					printf("Player %d pick your piece: \n", curTurnColor=='w' ? 1:2);
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
					int success = MakeMove(board,column1, row1, column2, row2,curTurnColor);
					if(success == 0)//signifies error
					{
						printf("Error. Try again\n");
						
					}
					else if (success == 1)
					{
						//printf("Successful move. \n");
						if(isChecked(board,((curTurnColor == 'w') ? 'b' : 'w')) )//checking if the opponent is in check. 
						{
							if(isCheckmate(board, ((curTurnColor == 'w') ? 'b' : 'w')) )//if the opponent is in check we check for checkmate
							{
								printf("Checkmate. Winner is player %d!", curTurnColor=='w' ? 1:2);
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
				break;
			}
			case 2:
			{

			
				/* HvH func */
				/* print moves log? */
				break;
			}
			case 3:
			{
				/* player settings func */
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
