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

int checkUser(char user[100])
{
	char line[301];
	char c;
	int count = 0;

	FILE *fp1 = fopen("record.txt", "r");
	if (fp1 == NULL)
	{
		printf("Error! File missing\n");
		exit (10);
	}

        while(!feof(fp1))
        {
		fgets(line, 300, fp1);
		
		for (c = fgetc(fp1); c != EOF; c = fgetc(fp1))
		{
			if(c == '\n')
			{
				if (strncmp(user, line, strlen(user)) == 0)
				{
					count += 1;
					printf("User exists");
					return count;;
				}
			}
		}
	}
	
	printf("User does not exist");
	return 0;
	
	fclose(fp1);
}

int checkPass(char user[100], char pass[100])
{
	int line;
	
	line = checkUser(user);

	if (line != 0)
	{
		FILE *fp1 = fopen("record.txt", "r");	
		if (fp1 == NULL)
		{
			printf("Error! File missing\n");
			exit(10);
		}
		
		while(!feof(fp1))
		{
			// look for password and return 1 if found
		}
	}
	
	else
		printf("User does not exist");

	return 0;
}

/* int changePass(char username[100], char newPass[100])
{
	char line[301];
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
