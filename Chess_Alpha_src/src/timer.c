#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

int min = 0, sec = 0, flag = 0;

void delay(int ms);
int timer();
int printTime();
int selection();

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

int main()
{
	selection();
	timer();
}
