#ifndef BOARD_H
#define BOARD_H
#define size 8

#include <assert.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "piece.h"

// initializes the game board
PIECE **makeBoard();

// deletes the board, freeing the memory and deallocating the array
void deleteBoard(PIECE **myBoard);

//
PIECE **copyBoard(PIECE **myBoard);

// returns piece at position colrow
PIECE *getPiece(PIECE **myBoard, int col, int row);

// places the piece specified at colrow, returning 0 if successful and 1 if not successful
void placePiece(PIECE **myBoard, PIECE *p, int col, int row);

// removes and returns piece from specified colrow and fills the spot with null; returns null if empty
PIECE removePiece(PIECE **myBoard, int col, int row);

// returns colrow destination from piece being moved and makes source blank
PIECE *movePiece(PIECE** myBoard, int colSource, int rowSource, int colDestination,int rowDestination);

// prints board to terminal
void printBoard(PIECE** myBoard);

// prints board to replay text file
void printReplayBoard(PIECE** myBoard, FILE* fptr);

// places black and white pieces to initialized board
void initializeBoard(PIECE** myBoard);

// returns 1 if selected source is empty and 0 if it is not empty
int isEmpty(PIECE **myBoard, int col, int row);

// checks if pawn reached the opposite end of the board and asks user type of piece they want to promote to
void checkForPromotion(PIECE **myBoard);

#endif

// EOF //
