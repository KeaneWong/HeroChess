/* ClockServer.c: simple TCP/IP server example with timeout support
 * Author: Rainer Doemer, 2/17/15
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <assert.h>
#include "piece.h"
#include "board.h"
#include "game.h"
#include "movelist.h"
#include "settings.h"
#include "replay.h"
#include "ai.h"


//this is a struct that describes a game, 
//including its associated movelist, board, and whose turn it is
struct FullGame
{
    PIECE **myBoard;
    MLIST *myList;
    char curTurnColor;
    int player_fd_1;
    int player_fd_2;
    int isAI;//a datamember that determines if this particular game is being done with an AI, instead of a human
};
typedef struct FullGame FullGame;

void InitializeGame(FullGame *myGame)
{
    myGame->myBoard = makeBoard();
    initializeBoard(myGame->myBoard);
    myGame->myList = NewMoveList();
    myGame->curTurnColor = 'w';
    myGame->player_fd_1 = -1;//signals an empty player fd socket
    myGame->player_fd_2 = -1;
}

FullGame *NewGame()
{
    FullGame *myGame;
    myGame = (FullGame*)malloc(sizeof(FullGame));
    if(!myGame)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    return myGame;
}
/* #define DEBUG */ /* be verbose */

/*** type definitions ****************************************************/

typedef void (*ClientHandler)(int DataSocketFD, FullGame *myGame);
typedef void (*TimeoutHandler)(void);

/*** global variables ****************************************************/

const char *Program /* program name for descriptive diagnostics */
    = NULL;
int Shutdown        /* keep running until Shutdown == 1 */
    = 0;
char ClockBuffer[26]    /* current time in printable format */
    = "";

/*** global functions ****************************************************/


void RemoveChar( char str[], char t )
{
  int i,j;
  for(i=0; i<strlen(str); i++)
  {
    if (str[i]==t) 
      for (j=i; j<strlen(str); j++)
      {
        str[j]=str[j+1];   
      } 
  }
}


void FatalError(        /* print error diagnostics and abort */
    const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
    exit(20);
} /* end of FatalError */

int MakeServerSocket(       /* create a socket on this server */
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
    if (listen(ServSocketFD, 5) < 0)    /* max 5 clients in backlog */
    {   FatalError("listening on socket failed");
    }
    return ServSocketFD;
} /* end of MakeServerSocket */

void PrintCurrentTime(void) /*  print/update the current real time */
{
    time_t CurrentTime; /* seconds since 1970 (see 'man 2 time') */
    char   *TimeString; /* printable time string (see 'man ctime') */
    char   Wheel,
       *WheelChars = "|/-\\";
    static int WheelIndex = 0;

    CurrentTime = time(NULL);   /* get current real time (in seconds) */
    TimeString = ctime(&CurrentTime);   /* convert to printable format */
    strncpy(ClockBuffer, TimeString, 25);
    ClockBuffer[24] = 0;    /* remove unwanted '/n' at the end */
    WheelIndex = (WheelIndex+1) % 4;
    Wheel = WheelChars[WheelIndex];
    printf("\rClock: %s %c",    /* print from beginning of current line */
    ClockBuffer, Wheel);    /* print time plus a rotating wheel */
    fflush(stdout);
} /* end of PrintCurrentTime */

void ProcessRequest(        /* process a game request by a client */
    int DataSocketFD, FullGame *myGame)
{
    int l, n;
    char RecvBuf[256];  /* message buffer for receiving a message */
    char SendBuf[256];  /* message buffer for sending a response */

    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0) 
    {   FatalError("reading from data socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received message: %s\n", Program, RecvBuf);
#endif


    if (RecvBuf[0] == '+')
    {   
        //this just checks if the request is occuring during another player's turn
        if((myGame->curTurnColor == 'w' && DataSocketFD != myGame->player_fd_1 )
            || (myGame->curTurnColor == 'b' && DataSocketFD !=myGame->player_fd_2))
        {
            strncpy(SendBuf,"Not currently your turn!",sizeof(SendBuf)-1);

        }
        else//if it isnt, we continue on
        {
        RemoveChar(RecvBuf, RecvBuf[0]);//removing protocol character
        char curTurnColor = myGame->curTurnColor;//setting turn color to the one stored in myGame
        char enemyTurnColor = (curTurnColor=='w' ? 'b' : 'w');//enemy's color
        int colS = RecvBuf[0]-'A';
        int rowS = RecvBuf[1]-'1';
        int colD = RecvBuf[2]-'A';
        int rowD = RecvBuf[3]-'1';
        PIECE **board = myGame->myBoard;
        MLIST *myList = myGame->myList;
        if(!MakeMove(board,colS,rowS,colD,rowD,curTurnColor,myList))
        {
            strncpy(SendBuf,"INVALID_MOVE",sizeof(SendBuf)-1);
        }
        else
        {
            if(isChecked(board,enemyTurnColor))
            {
                if(isCheckmate(board,enemyTurnColor,myList))
                {

                    strncpy(SendBuf,"WIN_ACHIEVED ",sizeof(SendBuf)-1);
                    char winningChar = curTurnColor - 32;//this just ascii shifts the char to uppercase
                    SendBuf[13] = winningChar;

                }
                else
                {
                    strncpy(SendBuf,"SUCCESSFUL_MOVE_CHECK_",sizeof(SendBuf)-1);
                    char checkedChar = enemyTurnColor-32;
                    SendBuf[22] = checkedChar;
                }
            }
            myGame->curTurnColor = enemyTurnColor;//flipping turn color

        
          strncpy(SendBuf, "MOVE FUNCTION EXECUTED", sizeof(SendBuf)-1);
        }
        }
        SendBuf[sizeof(SendBuf)-1] = 0;
        strncat(SendBuf, ClockBuffer, sizeof(SendBuf)-1-strlen(SendBuf));
        
    }

    else if (RecvBuf[0] == '/')
    {
        RemoveChar(RecvBuf, RecvBuf[0]);
        strncpy(SendBuf, "FIRST LOGIN FUNCTION EXECUTED", sizeof(SendBuf)-1);
        SendBuf[sizeof(SendBuf)-1] = 0;
        strncat(SendBuf, ClockBuffer, sizeof(SendBuf)-1-strlen(SendBuf));
    }

    /* Modification for chess*/   
        


    l = strlen(SendBuf);
#ifdef DEBUG
    printf("%s: Sending response: %s.\n", Program, SendBuf);
#endif
    n = write(DataSocketFD, SendBuf, l);
    if (n < 0)
    {   FatalError("writing to data socket failed");
    }
    


} /* end of ProcessRequest */

void ServerMainLoop(        /* simple server main loop */
    int ServSocketFD,       /* server socket to wait on */
    ClientHandler HandleClient, /* client handler to call */
    TimeoutHandler HandleTimeout,   /* timeout handler to call */
    int Timeout)            /* timeout in micro seconds */
{
    int DataSocketFD;   /* socket for a new client */
    socklen_t ClientLen;
    struct sockaddr_in
    ClientAddress;  /* client address we connect with */
    fd_set ActiveFDs;   /* socket file descriptors to select from */
    fd_set ReadFDs; /* socket file descriptors ready to read from */
    struct timeval TimeVal;
    int res, i;

    FD_ZERO(&ActiveFDs);        /* set of active sockets */
    FD_SET(ServSocketFD, &ActiveFDs);   /* server socket is active */
    //INITIALIZING GAME BOARD: CURRENTLY ONLY ACCEPTING 2 USERS
    FullGame *myGame = NULL;
    myGame = NewGame();
    InitializeGame(myGame);
    //END OF GAME BOARD INITAILIZATION SEQUENCE

    while(!Shutdown)
    {   ReadFDs = ActiveFDs;
    TimeVal.tv_sec  = Timeout / 1000000;    /* seconds */
    TimeVal.tv_usec = Timeout % 1000000;    /* microseconds */
    

    //CODE TO HANDLE THE GAME
    if(myGame->player_fd_1 != -1 && myGame->player_fd_2 != -1)//checking if theres one player in each FD, i.e at least two players logged in
    {
        int curTurnFD;
        if(myGame->curTurnColor == 'w')
        {
            curTurnFD = myGame->player_fd_1;
        }
        else
        {
            curTurnFD = myGame->player_fd_2;
        }

        int n = write(curTurnFD,"PRINT_BOARD",11);
        if(n<0)
        {FatalError("Writing to data socket failed");
        }
         n = write(curTurnFD,"REQUESTING_MOVE",15);
        if(n<0)
        {FatalError("writing to data socket failed");
        }

    }

    //ALL CODE AFTER THIS IS HANDLING THE CLIENT'S RESPONSE
    /* block until input arrives on active sockets or until timeout */
    res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, &TimeVal);
    if (res < 0)
    {   FatalError("wait for input or timeout (select) failed");
    }
    if (res == 0)   /* timeout occurred */
    {
#ifdef DEBUG
        printf("%s: Handling timeout...\n", Program);
#endif
        HandleTimeout();
    }
    else        /* some FDs have data ready to read */
    {   for(i=0; i<FD_SETSIZE; i++)
        {   if (FD_ISSET(i, &ReadFDs))
        {   if (i == ServSocketFD)
            {   /* connection request on server socket */
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

                //CODE TO ADD NEW USER TO AVAILABLE GAME BOARD
                //This code adds the new client to the first available file descriptor
                if(myGame->player_fd_1 == -1)
                {
                    myGame->player_fd_1 = DataSocketFD;
                }
                else if (myGame->player_fd_2 == -1)
                {
                    myGame->player_fd_2 = DataSocketFD;
                }
                //END OF CODE TO ADD NEW USER TO AVAILABLE GAME BOARD FD's

            }
            else
            {   /* active communication with a client */
#ifdef DEBUG
            printf("%s: Dealing with client %d...\n", Program, i);
#endif
            HandleClient(i, myGame);
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

/*** main function *******************************************************/

int main(int argc, char *argv[])
{
    int ServSocketFD;   /* socket file descriptor for service */
    int PortNo;     /* port number */

    Program = argv[0];  /* publish program name (for diagnostics) */
#ifdef DEBUG
    printf("%s: Starting...\n", Program);
#endif
    if (argc < 2)
    {   fprintf(stderr, "Usage: %s port\n", Program);
    exit(10);
    }
    PortNo = atoi(argv[1]); /* get the port number */
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




































/* EOF ClockServer.c */
