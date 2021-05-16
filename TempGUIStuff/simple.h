/***********************************************************
*
*A simple GTK example
*simple.h: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#ifndef _SIMPLE_H
#define _SIMPLE_H


#define MAX_MSGLEN  100 
#define SQUARE_SIZE 80 
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  800
#define BOARD_HEIGHT 800
#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 850

enum GRID
{
	BLACK = 0,
	WHITE = 1,
	BKING,
	BQUEEN,
	BROOK,
	BKNIGHT,
	BBISHOP,
	BPAWN,
	WKING,
	WQUEEN,
	WROOK,
	WKNIGHT,
	WBISHOP,
	WPAWN
};


#endif
