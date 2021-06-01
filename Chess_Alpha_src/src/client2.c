/* Client Side of Login/Registration Handling */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

/* #define DEBUG */	/* be very verbose */

void FatalError(const char *Program, const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!", stderr);
    exit(20);
} /* end of FatalError */

int main(int argc, char *argv[])
{
	int l, n;
	int SocketFD,	/* socket file descriptor */
	PortNo;		/* port number */
	struct sockaddr_in
	ServerAddress;	/* server address we connect with */
	struct hostent
	*Server;	/* server host */
	char SendBuf[256];	/* message buffer for sending a message */
	char RecvBuf[256];	/* message buffer for receiving a response */

	printf("%s: Starting...\n", argv[0]);
	if (argc < 3)
	{   fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
	exit(10);
	}
	#ifdef DEBUG
	printf("%s: Looking up host %s on the network...\n", argv[0], argv[1]);
	#endif
	Server = gethostbyname(argv[1]);
	if (Server == NULL)
	{   fprintf(stderr, "%s: no such host named '%s'\n", argv[0], argv[1]);
	exit(10);
	}
	PortNo = atoi(argv[2]);
	#ifdef DEBUG
	printf("%s: Using port %d...\n", argv[0], PortNo);
	#endif
	if (PortNo <= 2000)
	{   fprintf(stderr, "%s: invalid port number %d, should be greater 2000\n",
		argv[0], PortNo);
	exit(10);
	}
	#ifdef DEBUG
	printf("%s: Creating a socket...\n", argv[0]);
	#endif
	SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFD < 0)
	{   FatalError(argv[0], "socket creation failed");
	}
	#ifdef DEBUG
	printf("%s: Preparing the server address...\n", argv[0]);
	#endif
	memset(&ServerAddress, 0, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(PortNo);
	memcpy(&ServerAddress.sin_addr.s_addr,
		Server->h_addr_list[0], Server->h_length);
	printf("%s: Connecting to the server...\n", argv[0]);
	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		sizeof(ServerAddress)) < 0)
	{   FatalError(argv[0], "connecting to server failed");
	}

	/***************** Main Login/Registration Menu *****************/ 
	do{ printf("%s: Please select 1 or 2\n"
		"         1. New User\n"
		"         2. Returning User\n"
		"         3. Exit\n"
		"Your Selection: ", argv[0]);
	fgets(SendBuf, sizeof(SendBuf), stdin);
	l = strlen(SendBuf);
	if (SendBuf[l-1] == '\n')
	{   SendBuf[--l] = 0;
	}
	if (l)
	{
		printf("%s: Sending message '%s'...\n", argv[0], SendBuf);
		n = write(SocketFD, SendBuf, l);
		if (n < 0)
		{   FatalError(argv[0], "writing to socket failed");
		}
		#ifdef DEBUG
		printf("%s: Waiting for response...\n", argv[0]);
		#endif
		n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		if (n < 0) 
		{   FatalError(argv[0], "reading from socket failed");
		}
		RecvBuf[n] = 0;
		printf("%s: Received response: %s\n", argv[0], RecvBuf);
	}
	} while( (0 != strcmp("Welcome, nice to meet you!", RecvBuf)) && (0 != strcmp("Welcome!", RecvBuf)) && (0 != strcmp("server shutdown", RecvBuf)) );

	

	/***************** New User *****************/
	if( 0 == strcmp("Welcome, nice to meet you!", RecvBuf) )
	{
		/*char user[256];
		char pass[256];
		
		
		int length = strlen(user);
		int flag = 1;

		while (flag == 1) 
		{
			printf("Enter a unique username: ");
			scanf("%s", user);	
			length = strlen(user);

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
				memcpy(SendBuf, user, sizeof(SendBuf));
			}
	 
		}*/
		
		printf("%s: Enter a unique username: ", argv[0]);
		fgets(SendBuf, sizeof(SendBuf), stdin);
		l = strlen(SendBuf);
		if (SendBuf[l-1] == '\n')
		{   SendBuf[--l] = 0;
		}
		if (l)
		{
			printf("%s: Sending message '%s'...\n", argv[0], SendBuf);
			n = write(SocketFD, SendBuf, l);
			if (n < 0)
			{   FatalError(argv[0], "writing to socket failed");
			}
			#ifdef DEBUG
			printf("%s: Waiting for response...\n", argv[0]);
			#endif
			n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
			if (n < 0) 
			{   FatalError(argv[0], "reading from socket failed");
			}
			RecvBuf[n] = 0;
			printf("%s: Received response: %s\n", argv[0], RecvBuf);
		}
		
	}
	
		printf("%s: Enter a password: ", argv[0]);
		fgets(SendBuf, sizeof(SendBuf), stdin);
		l = strlen(SendBuf);
		if (SendBuf[l-1] == '\n')
		{   SendBuf[--l] = 0;
		}
		if (l)
		{
			printf("%s: Sending message '%s'...\n", argv[0], SendBuf);
			n = write(SocketFD, SendBuf, l);
			if (n < 0)
			{   FatalError(argv[0], "writing to socket failed");
			}
			#ifdef DEBUG
			printf("%s: Waiting for response...\n", argv[0]);
			#endif
			n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
			if (n < 0) 
			{   FatalError(argv[0], "reading from socket failed");
			}
			RecvBuf[n] = 0;
			printf("%s: Received response: %s\n", argv[0], RecvBuf);
		}

	/***************** Returning User *****************/
	else if( 0 == strcmp("Welcome!", RecvBuf) )
	{
		/*char user[50];
		char pass[50];
		
		
		int length = strlen(user);
		int flag = 1;

		while (flag == 1) 
		{
			printf("Username: ");
			scanf("%s", user);
			
			printf("Password: ");
			scanf("%s", pass);
		}*/
		
		printf("%s: Enter your username: ", argv[0]);
		fgets(SendBuf, sizeof(SendBuf), stdin);
		l = strlen(SendBuf);
		if (SendBuf[l-1] == '\n')
		{   SendBuf[--l] = 0;
		}
		if (l)
		{
			printf("%s: Sending message '%s'...\n", argv[0], SendBuf);
			n = write(SocketFD, SendBuf, l);
			if (n < 0)
			{   FatalError(argv[0], "writing to socket failed");
			}
			#ifdef DEBUG
			printf("%s: Waiting for response...\n", argv[0]);
			#endif
			n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
			if (n < 0) 
			{   FatalError(argv[0], "reading from socket failed");
			}
			RecvBuf[n] = 0;
			printf("%s: Received response: %s\n", argv[0], RecvBuf);
		}

		/*printf("%s: Enter your password: ", argv[0]);
		fgets(SendBuf, sizeof(SendBuf), stdin);
		l = strlen(SendBuf);
		if (SendBuf[l-1] == '\n')
		{   SendBuf[--l] = 0;
		}
		if (l)
		{
			printf("%s: Sending message '%s'...\n", argv[0], SendBuf);
			n = write(SocketFD, SendBuf, l);
			if (n < 0)
			{   FatalError(argv[0], "writing to socket failed");
			}
			#ifdef DEBUG
			printf("%s: Waiting for response...\n", argv[0]);
			#endif
			n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
			if (n < 0) 
			{   FatalError(argv[0], "reading from socket failed");
			}
			RecvBuf[n] = 0;
			printf("%s: Received response: %s\n", argv[0], RecvBuf);
		}	*/
	}

	/***************** Closing the Socket *****************/
	else if( 0 == strcmp("server shutdown", RecvBuf) )
	{
		printf("%s: Exiting...\n", argv[0]);
		close(SocketFD);
	}

	return 0;
}



/* EOF client2.c */

