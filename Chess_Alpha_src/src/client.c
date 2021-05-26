/* ClockClient.c: simple interactive TCP/IP client for ClockServer
 * Author: Rainer Doemer, 2/16/15 (updated 2/20/17)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

#include "game.h"
#include "board.h"

/* #define DEBUG */	/* be verbose */

/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */
	= NULL;

/*** global functions ****************************************************/

void FatalError(		/* print error diagnostics and abort */
	const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
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

    Program = argv[0];	/* publish program name (for diagnostics) */
#ifdef DEBUG
    printf("%s: Starting...\n", argv[0]);
#endif
    
    //Code used to verify proper host and port number, as well as initialize socketaddress 

    if (argc < 3)
    {   fprintf(stderr, "Usage: %s hostname port\n", Program);
	exit(10);
    }
    Server = gethostbyname(argv[1]);
    if (Server == NULL)
    {   fprintf(stderr, "%s: no such host named '%s'\n", Program, argv[1]);
        exit(10);
    }
    PortNo = atoi(argv[2]);
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PortNo);
    ServerAddress.sin_addr = *(struct in_addr*)Server->h_addr_list[0];
	
    //


    do
    {	
	if (1)
	{   SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	    if (SocketFD < 0)
	    {   FatalError("socket creation failed");
	    }
	    printf("%s: Connecting to the server at port %d...\n",
			Program, PortNo);
	    if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
			sizeof(ServerAddress)) < 0)
	    {   FatalError("connecting to server failed");
	    }
	   
#ifdef DEBUG
	    printf("%s: Waiting for response...\n", Program);
#endif
	    n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
	    if (n < 0) 
	    {   FatalError("reading from socket failed\n");
	    }
	    RecvBuf[n] = 0;
	    printf("%s: Received response: %s\n", Program, RecvBuf);
	    //SECTION TO INTERPRET RESPONSE
	    //-------------------------------------------------------------------

	    if(strcmp("FIRST MENU", RecvBuf) == 0)
	    {
	    	printf("Please select 1 or 2:\n");
	    	printf("\t 1. New user\n");
	    	printf("\t 2. Returning user\n");
	    	fgets(SendBuf, sizeof(SendBuf), stdin);
			l = strlen(SendBuf);
			if (SendBuf[l-1] == '\n')
			{   SendBuf[--l] = 0;	//is this meant to be an escape sequence?
			}
			printf("%s: Sending message '%s'...\n", Program, SendBuf);
	    	n = write(SocketFD, SendBuf, l);
	    	if (n < 0)
	    	{   FatalError("writing to socket failed");
	    	}

	    }
	    else if(strcmp("NEW_USERNAME", RecvBuf) == 0)
	    {
	    	printf("Welcome, nice to meet you! \n");
	    	printf("Enter a new username for HeroChess (6-8 characters, no spaces):\n");
	    	printf("(Suggestions: BlckWdw, FE_Man, THOR)\n");
	    	fgets(SendBuf, sizeof(SendBuf), stdin);
			l = strlen(SendBuf);
			if (SendBuf[l-1] == '\n')
			{   SendBuf[--l] = 0;	//is this meant to be an escape sequence?
			}
			printf("%s: Sending password '%s'...\n", Program, SendBuf);
	    	n = write(SocketFD, SendBuf, l);
	    	if (n < 0)
	    	{   FatalError("writing to socket failed");
	    	}
	    }
	   	else if(strcmp("NEW_PASSWORD", RecvBuf) == 0)
	    {
	    	printf("Enter a password(8 characters, must contain one number and special character , 4, @, !, *):\n");
	    	fgets(SendBuf, sizeof(SendBuf), stdin);
			l = strlen(SendBuf);
			if (SendBuf[l-1] == '\n')
			{   SendBuf[--l] = 0;	//is this meant to be an escape sequence?
			}
			printf("%s: Sending password '%s'...\n", Program, SendBuf);
	    	n = write(SocketFD, SendBuf, l);
	    	if (n < 0)
	    	{   FatalError("writing to socket failed");
	    	}
	    }
	    else if (strcmp("REQUESTING_USERNAME",RecvBuf) == 0)
	    {
			printf("Welcome, back! \n");
	    	printf("Enter your username:\n");
	    	fgets(SendBuf, sizeof(SendBuf), stdin);
			l = strlen(SendBuf);
			if (SendBuf[l-1] == '\n')
			{   SendBuf[--l] = 0;	//is this meant to be an escape sequence?
			}
			printf("%s: Sending username '%s'...\n", Program, SendBuf);
	    	n = write(SocketFD, SendBuf, l);
	    	if (n < 0)
	    	{   FatalError("writing to socket failed");
	    	}
	    }
	    else if(strcmp("REQUESTING_PASSWORD", RecvBuf) == 0)
	    {
	    	printf("Enter your password:\n");
	  
	    	fgets(SendBuf, sizeof(SendBuf), stdin);
			l = strlen(SendBuf);
			if (SendBuf[l-1] == '\n')
			{   SendBuf[--l] = 0;	//is this meant to be an escape sequence?
			}
			printf("%s: Sending password '%s'...\n", Program, SendBuf);
	    	n = write(SocketFD, SendBuf, l);
	    	if (n < 0)
	    	{   FatalError("writing to socket failed");
	    	}
	    }
	    else if(strcmp("INVALID_USERNAME", RecvBuf) == 0)
	    {
	    	printf("Error: Invalid username. Please try again\n");
	    	
	    }
	    else if(strcmp("INVALID_PASSWORD", RecvBuf) == 0)
	    {
	    	printf("Error: Invalid password. Please try again\n");
	    	
	    }
	    else if (strcmp("REQUESTING_MOVE"),RecvBuf) == 0)
	    {
	    	printf("Your move:\n");
	    	fgets(SendBuf, sizeof(SendBuf), stdin);
			l = strlen(SendBuf);
			if (SendBuf[l-1] == '\n')
			{   SendBuf[--l] = 0;	//is this meant to be an escape sequence?
			}
			printf("%s: Sending move '%s'...\n", Program, SendBuf);
	    	n = write(SocketFD, SendBuf, l);
	    	if (n < 0)
	    	{   FatalError("writing to socket failed");
	    	}
	    }
	    else if (strcmp("INVALID_MOVE",RecvBuf) == 0)
	    {
	    	printf("Invalid move: Please enter a new move\n");
	    }
	    else if (strcmp("WIN_ACHIEVED B",RecvBuf) == 0)
	    {
	    	printf("Checkmate; Player Black Wins!\n");
	    	
	    }
	    else if (strcmp("WIN_ACHIEVED W",RecvBuf) == 0)
	    {
	    	printf("Checkmate; Player White Wins!\n");
	    }
	    else if (strcmp("PRINT_BOARD",RecvBuf) == 0)
	    {
	    	PIECE **myBoard;
	    	//code to read in board data into myBoard
	    	n = read(SocketFD, myBoard, sizeof(PIECE*) * 64);
	    }
	    else if (strcmp("SUCCESSFUL_MOVE_CHECK_W",RecvBuf) == 0)
	    {
	    	printf("White player is in check\n");
	    }
	    else if (strcmp("SUCCESSFUL_MOVE_CHECK_B",RecvBuf) == 0)
	    {
	    	printf("Black player is in check\n");
	    }
	    else
	    {
	    	printf("Message from Server: %s\n", RecvBuf);//else, print the displayed message
	    }



	    //------------------------------------------------------------------
	    //END OF SECTION TO INTERPRET RESPONSE

#ifdef DEBUG
	    printf("%s: Closing the connection...\n", Program);
#endif


	    close(SocketFD);
	}
    } while(0 != strcmp("SHUTDOWN", SendBuf));
    printf("%s: Exiting...\n", Program);
    return 0;
}
























/* EOF ClockClient.c */













