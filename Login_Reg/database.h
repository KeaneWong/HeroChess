/************************************************************************/
/* 		HeroChess V2.0 by The Avengineers			*/
/* 		EECS 22L - University of California, Irvine		*/
/*									*/
/* database.h: contains declarations of functions related to database	*/
/*				handling				*/
/*									*/
/* Modifications:							*/
/* Date (YYYY/MM/DD)	Author			Description		*/
/* 2021/06/03		Rachel Villamor		Initial Version		*/
/************************************************************************/

#ifndef DATABASE_H
#define DATABASE_H
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

int appendUser(char username[100], char password[100]);
int checkUser(char user[100]);
int checkPass(char user[100], char pass[100]);

#endif

/* EOF */
