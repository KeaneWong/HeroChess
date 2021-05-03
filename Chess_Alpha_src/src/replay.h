#ifndef REPLAY_H
#define REPLAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "piece.h"
#include "move.h"
#include "movelist.h"
#include "board.h"


void replay(MLIST *l);

void printFormat(FILE *fptr, char *fname);

#endif
