#include <stdio.h>
#include <string.h>

int register_login();

int register_login()
{
	int opt;
	printf("Please select 1 or 2\n");
	printf("\t1. New user\n");
	printf("\t2. Returning user\n");
	
	scanf("%d", &opt);
	getchar();

	return opt;
}

int main()
{
	int opt = register_login();
	
	char user[15];
	char pass[9];
	
	switch(opt) {
	case 1: 
	{
		int length = strlen(user);
		int flag = 1;

		while (flag == 1) {
		printf("Enter a unique username(6-8 characters): ");
		scanf("%s", user);	

			if (length > 8)
			{
				printf("Username too long! Must be 6-8 characters\n");		
				flag = 1;
			}
		
			else if (length < 6)
			{
				printf("Username too short! Must be 6-8 characters\n");
				flag = 1;
			}

			else if ((length >= 6) || (length <= 8))
			{
				flag = 0;
			} 
		}

		printf("Enter a password(8 characters, must contain one number and special character , 4, @, !, *): ");
		scanf("%s", pass);
	}
	
	case 2:
	{
		printf("Username: ");
		printf("Password: ");
	}
	
	}

	return 0;
}
