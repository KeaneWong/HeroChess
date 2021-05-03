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
/* adds delay when timer is counting down */
void delay(int ms);

/* counts down from time inputted by user */
int timer(void);

/* prints timer to terminal */
int printTime(void);

/* asks user if timer is enabled or disabled */
int selection(void);

#endif
