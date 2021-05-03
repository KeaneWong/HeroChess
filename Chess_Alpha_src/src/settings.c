/************************************************************************/
/* settings.c: player and game settings menu and handling for HeroChess */
/* 									*/
/* Modifications:							*/
/* Date			Author			Description		*/
/* 2021/05/02		Irania Mazariegos	Added timer functions	*/
/* 2021/05/01		Rachel Villamor		Initial Version		*/
/************************************************************************/

#include "settings.h"

int min = 0, sec = 0, flag = 0;

/* player color handling */
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

/* timer handling */
void delay(int ms)
{
	clock_t timeDelay = ms + clock();
	while (timeDelay > clock());
}

int timer()
{
	while (flag == 0)
	{
		if (sec != 0)
		{
			sec--;
			delay(1000);
		}

		if (sec == 0 && min != 0)
		{
			sec = 59;
			delay(1000);
			min--;
		}

		if (sec == 0 && min == 0)
		{
			flag = 1;
			exit(10);
		}
		
		printTime();
		delay(1000);
	}
	return 0;
}

int printTime()
{	
	printf("\r%d:%d\n", min, sec);
	
	return 0;
}

int selection()
{
	printf("Please enter the minutes: ");
	scanf("%d", &min);

	printf("Please enter the seconds: ");
	scanf("%d", &sec);

	printf("Enter 0 to start: ");
	scanf("%d", &flag);

	return 0;
}
