/* Server Side of Login/Registration Handling */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

/* function declarations */
int register_login(void);
int reglog_menu(void);
int append_newuser(void);
int verify_exist(void);
int verify_passmatch(void);
int MakeServerSocket(uint16_t PortNo); 
void FatalError(const char *ErrorMsg);
void ProcessRequest(int DataSocketFD);
void ServerMainLoop(int ServSocketFD, ClientHandler HandleClient, TimeoutHandler HandleTimeout, int Timeout);

/* type definitions */
typedef void (*ClientHandler)(int DataSocketFD);
typedef void (*TimeoutHandler)(void);

/* main function */
//int main()
//{
//	char server_mssg[256] = "You have connected with the server!";

	/* create a socket */
//	int servsock;
//	servsock = socket(AF_INET, SOCK_STREAM, 0);

	/* define server address */
//	struct sockaddr_in server_address;
//	server_address.sin_family = AF_INET;
//	server_address.sin_port = htons(11923);
//	server_address.sin_addr.s_addr = INADDR_ANY;

	/* bind the socket to the server */
/*	bind(servsock, (struct sockadrr*) &server_address, sizeof(server_address));
*/
	/* listen to socket */
//	listen(servsock, 5); 

	/* means of accepting connections */
//	int clisock;
//	clisock = accept(servsock, NULL, NULL);	

	/* send data */
//	send(clisock, server_mssg, sizeof(server_mssg), 0);

	/* close the socket */
//	close(servsock);
		
//	return 0;
//} /* end of main function */


/*** main function *******************************************************/

int main(int argc, char *argv[])
{
    int ServSocketFD;	/* socket file descriptor for service */
    int PortNo;		/* port number */

    Program = argv[0];	/* publish program name (for diagnostics) */
#ifdef DEBUG
    printf("%s: Starting...\n", Program);
#endif
    if (argc < 2)
    {   fprintf(stderr, "Usage: %s port\n", Program);
	exit(10);
    }
    PortNo = atoi(argv[1]);	/* get the port number */
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
#ifdef DEBUG
    printf("%s: Creating the server socket...\n", Program);
#endif
    ServSocketFD = MakeServerSocket(PortNo);
    printf("%s: Providing current time at port %d...\n", Program, PortNo);
    ServerMainLoop(ServSocketFD, ProcessRequest,
			PrintCurrentTime, 250000);
    printf("\n%s: Shutting down.\n", Program);
    close(ServSocketFD);
    return 0;
}

/*** function definitions  ****************************************************/

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

int MakeServerSocket(		/* create a socket on this server */
	uint16_t PortNo)
{
    int ServSocketFD;
    struct sockaddr_in ServSocketName;

    /* create the socket */
    ServSocketFD = socket(PF_INET, SOCK_STREAM, 0);
    if (ServSocketFD < 0)
    {   FatalError("service socket creation failed");
    }
    /* bind the socket to this server */
    ServSocketName.sin_family = AF_INET;
    ServSocketName.sin_port = htons(PortNo);
    ServSocketName.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ServSocketFD, (struct sockaddr*)&ServSocketName,
		sizeof(ServSocketName)) < 0)
    {   FatalError("binding the server to a socket failed");
    }
    /* start listening to this socket */
    if (listen(ServSocketFD, 5) < 0)	/* max 5 clients in backlog */
    {   FatalError("listening on socket failed");
    }
    return ServSocketFD;
} /* end of MakeServerSocket */

void ProcessRequest(		/* process a login request by a client */
	int DataSocketFD)
{
    int  l, n;
    char RecvBuf[256];	/* message buffer for receiving a message */
    char SendBuf[256];	/* message buffer for sending a response */

    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0) 
    {   FatalError("reading from data socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received message: %s\n", Program, RecvBuf);
#endif
    if (0 == strcmp(RecvBuf, "TIME"))
    {   strncpy(SendBuf, "OK TIME: ", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClockBuffer, sizeof(SendBuf)-1-strlen(SendBuf));
    }
    else if (0 == strcmp(RecvBuf, "SHUTDOWN"))
    {   Shutdown = 1;
	strncpy(SendBuf, "OK SHUTDOWN", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
    }
    else
    {   strncpy(SendBuf, "ERROR unknown command ", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, RecvBuf, sizeof(SendBuf)-1-strlen(SendBuf));
    }
    l = strlen(SendBuf);
#ifdef DEBUG
    printf("%s: Sending response: %s.\n", Program, SendBuf);
#endif
    n = write(DataSocketFD, SendBuf, l);
    if (n < 0)
    {   FatalError("writing to data socket failed");
    }
} /* end of ProcessRequest */

void ServerMainLoop(		/* simple server main loop */
	int ServSocketFD,		/* server socket to wait on */
	ClientHandler HandleClient,	/* client handler to call */
	TimeoutHandler HandleTimeout,	/* timeout handler to call */
	int Timeout)			/* timeout in micro seconds */
{
    int DataSocketFD;	/* socket for a new client */
    socklen_t ClientLen;
    struct sockaddr_in
	ClientAddress;	/* client address we connect with */
    fd_set ActiveFDs;	/* socket file descriptors to select from */
    fd_set ReadFDs;	/* socket file descriptors ready to read from */
    struct timeval TimeVal;
    int res, i;

    FD_ZERO(&ActiveFDs);		/* set of active sockets */
    FD_SET(ServSocketFD, &ActiveFDs);	/* server socket is active */
    while(!Shutdown)
    {   ReadFDs = ActiveFDs;
	TimeVal.tv_sec  = Timeout / 1000000;	/* seconds */
	TimeVal.tv_usec = Timeout % 1000000;	/* microseconds */
	/* block until input arrives on active sockets or until timeout */
	res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, &TimeVal);
	if (res < 0)
	{   FatalError("wait for input or timeout (select) failed");
	}
	if (res == 0)	/* timeout occurred */
	{
#ifdef DEBUG
	    printf("%s: Handling timeout...\n", Program);
#endif
	    HandleTimeout();
	}
	else		/* some FDs have data ready to read */
	{   for(i=0; i<FD_SETSIZE; i++)
	    {   if (FD_ISSET(i, &ReadFDs))
		{   if (i == ServSocketFD)
		    {	/* connection request on server socket */
#ifdef DEBUG
			printf("%s: Accepting new client %d...\n", Program, i);
#endif
			ClientLen = sizeof(ClientAddress);
			DataSocketFD = accept(ServSocketFD,
				(struct sockaddr*)&ClientAddress, &ClientLen);
			if (DataSocketFD < 0)
			{   FatalError("data socket creation (accept) failed");
			}
#ifdef DEBUG
			printf("%s: Client %d connected from %s:%hu.\n",
				Program, i,
				inet_ntoa(ClientAddress.sin_addr),
				ntohs(ClientAddress.sin_port));
#endif
			FD_SET(DataSocketFD, &ActiveFDs);
		    }
		    else
		    {   /* active communication with a client */
#ifdef DEBUG
			printf("%s: Dealing with client %d...\n", Program, i);
#endif
			HandleClient(i);
#ifdef DEBUG
			printf("%s: Closing client %d connection.\n", Program, i);
#endif
			close(i);
			FD_CLR(i, &ActiveFDs);
		    }
		}
	    }
	}
    }
} /* end of ServerMainLoop */

/**********************************************************************************/

/* login/registration function loop */
int register_login(void)
{
	int opt; 
	/* hardcoded registered username & password */
	//char reguser[20] = "antH3r0";
	//char regpass[20] = "5upeReater!";

	char user[20];
	char pass[20];
	
	int exit = 0;
	while( exit == 0 )
	{
		/* login and registration menu prints until user chooses
 		to exit or continues to game portion of program */
		opt = reglog_menu();
		switch(opt) {
			case 1: 
			{
				int length = strlen(user);
				int flag = 1;

				/* user must enter a username that follows the guidelines */
				while (flag == 1) {
				printf("Enter a unique username(6-8 characters): "); 
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
					} 
				}

				/* username is sent to server for verification and appending */
				/* in server: */
				// verify_user(char user) {
				//	read through database, use strcmp to 
				//	find for any matches, if none, notify client of success
				//	otherwise, prompt user to try again
				// }
				// append_user(){
				// }

				printf("Enter a password(8 characters, must contain one number and special character(4, @, !, *): ");
				scanf("%s", pass);	
				length = strlen(pass);
					if (length < 6)
					{
						printf("Password too short! Must be at least 8 characters\n");
						flag = 1;
					}

					else if ((length >= 6) || (length <= 8))
					{
						flag = 0;
					} 
				}

				/* password is sent to server for verification and appending */
				/* in server: */
				// verify_passmatch(char user) {
				//	read through database, use strcmp to 
				//	find for any matches, if none, notify client of success
				//	otherwise, prompt user to try again
				// }
				// append_user(){
				// }
			}
			
			case 2:
			{
				printf("Username: ");
				printf("Password: ");
			}
			
			case 3:
			{
				printf("Goodbye!\n");
				exit=1;
			}	
		}
	}

	return 0;
}

/* function definitions */
int reglog_menu(void)
{
	int opt;
	printf("Please select 1 or 2\n");
	printf("\t1. New user\n");
	printf("\t2. Returning user\n");
	printf("\t3. Exit\n");
	
	scanf("%d", &opt);
	getchar();

	return opt;
} /* end of reglog_menu() */

int append_newuser(void)
{
	int status = 0;
	return status;	
} /* end of append_newuser() */

int append_name()
{
	int status = 0;
	return status; 	
} /* end of append_name() */

int append_pass()
{
	int status = 0;
	return status;
} /* end of append_pass() */

int verify_exist()
{
	int status = 0;
	return status;
} /* end of verify_exist() */

int verify_passmatch()
{
	int status = 0;
	return status;
} /* end of verify_passmatch() */

