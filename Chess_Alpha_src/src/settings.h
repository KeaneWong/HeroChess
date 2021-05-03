/**************************************************************************/
/*  settings.h: declarations of functions in settings.c                   */
/*                                                                        */
/* Modifications:                                                         */
/* Date         Author                        Description                 */
/* 2021/05/02   Irania Mazariegos             Added timer functions       */
/* 2021/05/01   Rachel Villamor               Initial Version             */
/**************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <assert.h>
#include <time.h>

/* player color handling */
/* user chooses which playes gets the white pieces */
int whitepnum(void);

/* black pieces are automatically assigned based off input from whitepnum() */
int blackpnum(int wp);

/* timer handling */
/* */
void delay(int ms);

/* */
int timer(void);

/* */
int printTime(void);

/* */
int selection(void);

#endif
