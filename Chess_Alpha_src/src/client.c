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
	    	printf("Enter a new username for HeroChess (6-8 characters, no spaces):\n")
	    	printf("(Suggestions: BlckWdw, FE_Man, THOR)\n")
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
	    else if (strcmp("WIN_ACHIEVED W",RecvBuf) == 0)
	    {
	    	printf("Checkmate; Player White Wins!\n");

	    }
	   	else if (strcmp("WIN_ACHIEVED B",RecvBuf) == 0)
	    {
	    	printf("Checkmate; Player Black Wins!\n");
	    	
	    }
	    else if (strcmp("INVALID_MOVE",RecvBuf) == 0)
	    {
	    	printf("Invalid move: Please enter a new move\n");
	    }
	    else if (strcmp("WIN_ACHIEVED",RecvBuf) == 0)
	    {
	    	
	    }
	    else if (strcmp("WIN_ACHIEVED",RecvBuf) == 0)
	    {
	    	
	    }
	    else if (strcmp("WIN_ACHIEVED",RecvBuf) == 0)
	    {
	    	
	    }
	    else if (strcmp("WIN_ACHIEVED",RecvBuf) == 0)
	    {
	    	
	    }
	    else
	    {

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













