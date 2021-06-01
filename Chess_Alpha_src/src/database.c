/* database program */
// currently buggy; doesn't verify user correctly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int appendUser(char username[100], char password[100]);
int checkUser(char user[100]);
int checkPass(char user[100], char pass[100]);

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
	int lineNum = 1;
	
	FILE *fp1 = fopen("record.txt", "r");
	if (fp1 == NULL)
	{
		printf("Error! File missing\n");
		exit (10);
	}

        while(fgets(line, 300, fp1) != NULL)
        {	
	
		if (strstr(line, user) != NULL)
		{
			//printf("User exists line %d\n", lineNum);
			return lineNum;
		}
		
		lineNum++;
	}

	if (lineNum < 1)
	{
		return 0;
	}

	fclose(fp1);
}

int checkPass(char user[100], char pass[100])
{
	char line[301];
	int lineNum;
	int passLine = 1;
	
	FILE *fp1 = fopen("record.txt", "r");	
	if (fp1 == NULL)
	{
		printf("Error! File missing\n");
		exit(10);
	}

	lineNum = checkUser(user);
	//lineNum = lineNum + 1;
	//printf("%d", lineNum);
	
	while(fgets(line, 300, fp1) != NULL)
	{
		if ((strstr(line, pass) != NULL) && (passLine == (lineNum + 1)))
		{
		
			//printf("Welcome line %d\n", passLine);
			return passLine;
		}	
	
		passLine++;					
	}

	if (passLine == 0)
	{
		return 0;
	}
	fclose(fp1);
}

int main()
{
	char user[100], pass[100];
	int name, match;
	
	printf("Username: ");
	scanf("%s", user);
	name = checkUser(user);
	
	if (name >= 1)
	{
		printf("Password: ");
		scanf("%s", pass);
		match = checkPass(user, pass);
		
		if (match == name + 1)
		{
			printf("Welcome back!\n");
		}

		else
		{
			printf("Wrong password...\n");
		}
	}
	
	else
	{
		printf("User does not exist\n");
	}

	return 0;
} 
/* 
int changePass(char username[100], char newPass[100])
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
