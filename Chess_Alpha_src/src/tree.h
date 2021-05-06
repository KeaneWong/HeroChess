#include <stdio.h>
#include <stdlib.h>
#include "move.h"

struct TreeNode{
	MOVE *potMove;//stands for potential move
	TREENODE *child;
	TREENODE *nextSibling;

	
};

typedef struct TreeNode TREENODE;

TREENODE *NewNode(MOVE *newMove);	//makes a new node, all data default to NULL

void SetChild(TREENODE *parent, TREENODE *newChild);	//sets the child of parent to newchild, deleting the previous one if there already was one present

TREENODE *GetChild(TREENODE *node);			//returns child, null if no child

TREENODE *GetNext(TreeNode *node);		//gets next sibling

void DeleteNode(TREENODE *nodeTBD);		//deletes node and only that node


void DeleteNodeRecursive(TREENODE *nodeTBD);		//recursively deletes node and all siblings and children









