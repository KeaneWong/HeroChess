/************************************************************************/
/* settings.c: player and game settings menu and handling for HeroChess */
/* 									*/
/* Modifications:							*/
/* Date			Author			Description		*/
/* 2021/05/01		Rachel Villamor		Initial Version		*/
/************************************************************************/

#include "settings.h"

/* user chooses which playes gets the white pieces */
int whitepnum(void)
{
	int wp;
	int done = 0;
	
	while (done == 0)
	{
		printf("Enter which player will have the white pieces (1 or 2):");
		scanf("%d", &wp);
		getchar();
		
		if ( wp == 1 || wp == 2)
		{
			printf("Player %d has the white pieces.\n", wp); 
			done = 1;
		}
		else
		{
			printf("Invalid input(s), Try Again!\n");
			done = 0;
		}
	}
	return wp;
}

/* black pieces are automatically assigned based off input from whitepnum() */
int blackpnum(int wp)
{
	int bp;
	printf("Player %d has the black pieces.\n", wp==1 ? (bp=2):(bp=1));
	return bp;
}
