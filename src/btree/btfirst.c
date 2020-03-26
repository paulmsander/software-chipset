/********************************************************************
 *
 * btfirst.c -- This file contains functions to locate the key
 *              falling first in the lexical order of items stored
 *              in an in-memory B-tree.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ********************************************************************/

#include <stdio.h>
#include "btpriv.h"

/********************************************************************
 *
 * bt_first -- This function returns the key that appears first in
 *             the lexical order of the items stored in the tree.
 *             NULL is returned if the tree is empty.
 *
 *******************************************************************/

#ifdef __STDC__
void *bt_first(void *ptree, void **data)
#else
void *bt_first(ptree,data)
void	*ptree;
void	**data;
#endif
{
	BTNODE	*node;
	BTREE	tree;

	tree = (BTREE) ptree;
	if (tree == NULL)
	{
		COVER("btfirst.c",1);
		return NULL;
	} 
	node = tree->root;
	if (node->nkeys == 0)
	{
		COVER("btfirst.c",2);
		return NULL;
	}
	while (node->children != NULL)
	{
		COVER("btfirst.c",3);
		node->currKey = 0;
		node = node->children[0];
	}
	COVER("btfirst.c",4);
	node->currKey = 0;
	tree->currNode = node;
	tree->nextOk = 1;
	if (data != NULL)
	{
		COVER("btfirst.c",5);
		*data = node->data[0];
	}
	return node->keys[0];
}

/*********** End of file ************/

