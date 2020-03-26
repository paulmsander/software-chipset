/********************************************************************
 *
 * bt_last.c -- This file contains functions needed to find the
 *              key that is highest in the lexical order of keys
 *              stored in an in-memory B-tree.
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
 * bt_last -- This function returns the key that appears last in
 *            the lexical order of the items stored in the tree.
 *            NULL is returned if the tree is empty.
 *
 *******************************************************************/

#ifdef __STDC__
void *bt_last(void *ptree, void **data)
#else
void *bt_last(ptree,data)
void	*ptree;
void	**data;
#endif
{
	BTREE	tree;
	BTNODE	*node;

	tree = (BTREE) ptree;
	if (tree == NULL)
	{
		COVER("bt_last.c",1);
		return NULL;
	}
	node = tree->root;
	if (node->nkeys == 0)
	{
		COVER("bt_last.c",2);
		return NULL;
	}
	COVER("bt_last.c",3);
	while (node->children != NULL)
	{
		COVER("bt_last.c",4);
		node->currKey = node->nkeys;
		node = node->children[node->nkeys];
	}
	COVER("bt_last.c",5);
	node->currKey = node->nkeys - 1;
	tree->currNode = node;
	tree->nextOk = 1;
	if (data != NULL)
	{
		COVER("bt_last.c",6);
		*data = node->data[node->nkeys - 1];
	}
	return node->keys[node->nkeys - 1];
}

/************ End of file *************/

