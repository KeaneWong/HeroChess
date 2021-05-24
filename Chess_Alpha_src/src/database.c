/* database program */
// currently buggy; won't let password be inputted

#include <stdio.h>
#include <string.h>

/* typedef struct data
{
	char username[100];
	char password[100];
}record; */

int main(void)
{
	//int i, choice;
	char username[100];
	char password[100];
	FILE *fp1;
	//char oname[100];
	//record det;
	//int recsize;
	//char c;

	fp1 = fopen("record.txt", "r+");
	if(fp1 == NULL)
	{
		fp1 = fopen("record.txt", "a+");
		if(fp1 == NULL)
		{
			printf("error in opening file: \n");
			return -1;
		}
	}
	
	//recsize = sizeof(det);
	
	//fseek(fp1, 0, SEEK_END);
	printf("Enter username: ");
	scanf("%[^\n]", det.username);
	fprintf(fp1, "Username: %s\n", username);

	printf("Enter password: ");
	scanf("%[^\n]", det.password);
	fprintf(fp1, "Password: %s\n\n", password);

	fclose(fp1);
	return 0;
}
