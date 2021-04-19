/* main.c: file containing main function and print menu function */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piece.h"
#include "board.h"

// print menu function declaration
int mainmenu(void);

// main function
int main(void){
	PIECE **board = makeBoard();
	PIECE *p = NewPiece('P', 'w');
	placePiece(board, p, 0, 0);

	// welcome message prints once at the start of the first game
	printf("Welcome to HeroChess v1.0");

	// main menu keeps printing after each game until user decides to exit
	int exit = 0;
	while(exit == 0)
	{
		/* print board here? */
		int option = mainmenu();
		switch(option)
		{
			case 1:
				/* HvH func */
				/* print moves log? */
				break;
			case 2:
				/* HvH func */
				/* print moves log? */
				break;
			case 3:
				/* player settings func */
				break;
			case 4:
				printf("Thanks for playing. Exiting game...\n");
				exit=1;
				break;
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
