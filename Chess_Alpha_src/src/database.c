/* database program */
// currently buggy; won't let password be inputted

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int appendUser(char username[100], char password[100]);
int checkUser(char user[100], char pass[100]);

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

int checkUser(char user[100], char pass[100])
{
	char line[301];
	int found = 0;

	FILE *fp1 = fopen("record.txt", "r");
	if (fp1 == NULL)
	{
		printf("Error! File missing\n");
		exit (10);
	}

        while(!feof(fp1))
        {
                fgets(line, 300, fp1);
		
		if(strncmp(user, line, strlen(user)) == 0)
		{
			if (strncmp(pass, line, strlen(pass)) == 0)
			{
				printf("User exists");
				found = 1;
			}
		
			else 
			{
				printf("Password is incorrect");
			}
		}
	}
	
	printf("User does not exist");
	return found;
	
	fclose(fp1);
}

/* int changePass(char username[100], char newPass[100])
{
	char oldPass[100];
	int found;
	
	FILE *fp1 = fopen("record.txt", "r");
	if (fp1 == NULL)
	{
		printf("Error! File missing\n");
		exit (10);
	}

        while(!feof(fp1))
        {
                fgets(line, 300, fp1);
		
		if(strncmp(user, line, strlen(user)) == 0)
		{
			
		}
		
	} 
} */

// EOF //
