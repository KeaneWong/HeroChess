#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include "move.h"


typedef struct TreeNode TREENODE;
struct TreeNode{
	MOVE *potMove;//stands for potential move
	TREENODE *child;
	TREENODE *nextSibling;

	
};



TREENODE *NewNode(MOVE *newMove);	//makes a new node, all data default to NULL

TREENODE *EmptyNode();

int isEmptyNode(TREENODE *node);

void SetChild(TREENODE *parent, TREENODE *newChild);	//sets the child of parent to newchild, deleting the previous one if there already was one present

TREENODE *GetChild(TREENODE *node);			//returns child, null if no child

void SetNext(TREENODE *node, TREENODE *newSibling);

TREENODE *GetNext(TREENODE *node);		//gets next sibling

MOVE *GetNodeMove(TREENODE *node);

void SetMove(TREENODE *node, MOVE *newMove);

void DeleteNode(TREENODE *nodeTBD);		//deletes node and only that node

void DeleteNodeRecursive(TREENODE *nodeTBD);		//recursively deletes node and all siblings and children

void PrintAcross(TREENODE *node);

void PrintAll(TREENODE *node);






#endif