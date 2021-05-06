#include "tree.h"



TREENODE *NewNode(MOVE *newMove)
{
	TREENODE *newnode = (TREENODE*)malloc(sizeof(TREENODE));
	if (!newnode)
	{ 
		perror("Out of memory! Aborting...\n");
		exit(10);
	} /* fi */
	newnode->potMove = newMove;
	newnode->child = NULL;
	newnode->nextSibling = NULL;
	return newnode;
}

void SetChild(TREENODE *parent, TREENODE *newChild)
{
	if(parent->child != NULL)//if there is already a child to the node we delete it and overwrite it
	{
		DeleteNode(parent->child);
	}
	parent->child = newChild;

}

TREENODE *GetChild(TREENODE *node)
{
	return node->child;
}

TREENODE *GetNext(TreeNode *node)
{
	return node->nextSibling;
}

void DeleteNode(TREENODE *nodeTBD)
{
	free(nodeTBD);
}



void DeleteNodeRecursive(TREENODE *nodeTBD)
{
	if(nodeTBD == NULL)
	{
		return;
	}
	DeleteNodeRecursive(GetNext(nodeTBD));
	DeleteNodeRecursive(GetChild(nodeTBD));
	DeleteNode(nodeTBD);
	

}
