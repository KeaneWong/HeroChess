/* database program */
// currently buggy; won't let password be inputted

#include <stdio.h>
#include <stdlib.h>

int appendUser(char username[100], char password[100])
{
	//char username[100];
	//char password[100];
	FILE *fp1;
	
	fp1 = fopen("record.txt", "a+");
	if(fp1 == NULL)
	{
		printf("error in opening file: \n");
		return -1;
	}
	
	//printf("Enter username: ");
	//scanf("%s", username);
	fprintf(fp1, "Username: %s\n", username);

	//printf("Enter password: ");
	//scanf("%s", password);
	fprintf(fp1, "Password: %s\n\n", password);

	fclose(fp1);
	return 0;
}
