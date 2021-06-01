/* database program */
// currently buggy; doesn't verify user correctly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int appendUser(char username[100], char password[100]);
int checkUser(char user[100]);
int checkPass(int lineNum, char user[100], char pass[100]);

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
	char c = getc(fp1);
	int count = 0;

	FILE *fp1 = fopen("record.txt", "r");
	if (fp1 == NULL)
	{
		printf("Error! File missing\n");
		exit (10);
	}

        while(fgets(line, 300, fp1) != NULL)
        {	
	//	while(c != EOF)
	//	{
	//		if(c != '\n')
	//		{		
				if (strcmp(line, user) != NULL)
				{
					printf("User exists line %d\n", count);
					count += 1;
					break;
	//				return count;
				}

				else
				{
					printf("User does not exist");
					return 0;
				}
	//		}
	//	}
	}
	
	fclose(fp1);
}

int checkPass(int lineNum, char user[100], char pass[100])
{
	char line[301];
	int count;

	lineNum = checkUser(user);

	FILE *fp1 = fopen("record.txt", "r");	
	if (fp1 == NULL)
	{
		printf("Error! File missing\n");
		exit(10);
	}
	
	while(fgets(line, 300, fp1) != NULL)
	{
		if (count == (lineNum + 1))
		{
			if (strcmp(pass, line) == 0)	
			{
				printf("Welcome");
				return 1;
			}

			else
			{
				printf("Password incorrect");
				return -1;
			}				
		}
		
		else 
		{
			count++;
		}
	}

	fclose(fp1);
}

int main()
{
	char user[100], pass[100];
	
	printf("Username: ");
	scanf("%s", user);
	checkUser(user);
	
	printf("Password: ");
	scanf("%s", pass);
	checkPass(checkUser(user), user, pass);

//	FILE *fp1 = fopen("record.txt", "r");
//	char c;
//	int count = 0;
//	for (c = getc(fp1); c != EOF; c = getc(fp1))
//	{
//		if (c == '\n')
//			count = count + 1;
//	}
//	printf("Number of lines in file: %d", count);
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
