/* database program */

#include <stdio.h>
#include <string.h>

typedef struct data
{
	char username[100];
	char password[100];
}record;

int main(void)
{
	int i, choice;
	FILE *fp1, *fp2;
	char oname[100];
	record det;
	int recsize;
	char c;

	fp1 = fopen("record.txt", "r+");
	if(fp1 == NULL)
	{
		fp1 = fopen("record.txt", "w+");
		if(fp1 == NULL)
		{
			printf("error in opening file: \n");
			return -1;
		}
	}
	
	recsize = sizeof(det);
	
	fseek(fp1, 0, SEEK_END);
	printf("Enter username: ");
	scanf("%[^\n]", det.username);
	printf("Enter password: ");
	scanf("%[^\n]", det.password);
	fwrite(&det, recsize, 1, fp1);
}
