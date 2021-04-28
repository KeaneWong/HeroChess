#include "movelist.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <assert.h>


/* allocate a new move entry */ 
static MENTRY *NewMoveEntry(MOVE *m){
    MENTRY *e; 
	e = malloc(sizeof(MENTRY)); 
	if (! e){ 
		perror("Out of memory! Aborting..."); 
		exit(10); 
	} /* fi */ 

	e->list = NULL; 
	e->next = NULL; 
	e->prev = NULL; 
	e->move = m; 
	return e; 
} 
/* end of NewMoveEntry */

static MOVE *DeleteMoveEntry(MENTRY *e){
  MOVE *m; 
	assert(e); 
	m = e->move; 
	free(e); 
	return m; 
} /* end of DeleteMoveEntry */

/* allocate a new move list */ 
MLIST *NewMoveList(void){
	MLIST *l; 
	l = malloc(sizeof(MLIST)); 
	if (!l){ 
		perror("Out of memory! Aborting..."); 
		exit(10); 
	} /* fi */ 
	
	l->length = 0; 
	l->first = NULL; 
	l->last = NULL; 
	return l;
}

/* delete a move list (and all entries) */ 
void DeleteMoveList(MLIST *l){
	MENTRY *e, *n; 
	MOVE *m;
	assert(l); 
	e = l->first; 
	while(e){ 
		n = e->next; 
		m = DeleteMoveEntry(e); 
		DeleteMove(m); 
		e = n; 
	} 
	free(l);
}

void AppendMove(MLIST *l, MOVE *m){
	MENTRY *e = NULL; 
	assert(l); 
	assert(m); 
	e = NewMoveEntry(m); 
	if (l->last){ 
		e->list = l; 
		e->next = NULL; 
		e->prev = l->last; 
		l->last->next = e; 
		l->last = e; 
	} 
	else { 
		e->list = l; 
		e->next = NULL; 
		e->prev = NULL; 
		l->first = e; 
		l->last = e; 
	} 
	l->length++;
	
}

MOVE *RemoveLastMove(MLIST *l){
	MENTRY *e = NULL; 
	assert(l); 
	if (l->last){ 
		e = l->last; 
		l->last = e->prev; 
		if (l->last){ 
			l->last->next = NULL;
		}		 
		else{ 
			assert(l->first == e); 
			l->first = NULL; 
		}		 
		l->length--; 
		return DeleteMoveEntry(e); 
	} 
	else { 
		return(NULL); 
	} 
}

MOVE *RemoveFirstMove(MLIST *l) {
	MENTRY *e = NULL; 
	assert(l); 
	if (l->first) {
		e = l->first; 
		l->first = e->next; 
		if (l->first) 
		{ l->first->prev = NULL; } 
		else 
		{ assert(l->last == e); l->last = NULL; } 
		l->length--; 
		return DeleteMoveEntry(e); } 
	else 
	{ return(NULL); } 
}

/* print a student list */
void PrintMoveList(MLIST *l){
	MENTRY *e;
	assert(l);
	e = l->first;
	while(e){
		PrintMove(e->move);
		e = e->next;
	}
} /* end of PrintStudentList */


