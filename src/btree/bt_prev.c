/********************************************************************
 *
 * btprev.c -- This file contains functions needed to scan an in-memory
 *             B-tree in descending order.
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
 * bt_prev -- This function returns the next key that appears
 *            earlier in the lexical order of the items stored in
 *            the tree, after the last bt_search, bt_next, bt_prev, or
 *            bt_last.  NULL is returned if the tree is empty, an
 *            insertion or deletion invalidated the state of the
 *            tree, or the next item in the tree was already visited.
 *
 *******************************************************************/

#ifdef __STDC__
void *bt_prev(void *ptree, void **data)
#else
void *bt_prev(ptree,data)
void	*ptree;
void	**data;
#endif
{
	BTNODE	*node;
	int	key;
	BTREE	tree;

	/* Return if error, or insertion/deletion invalidated state */
	tree = (BTREE) ptree;
	if (tree == NULL)
	{
		COVER("bt_prev.c",1);
		return NULL;
	}
	if (tree->currNode == NULL)
	{
		COVER("bt_prev.c",2);
		return NULL;
	}
	COVER("bt_prev.c",3);
	tree->nextOk = 1;

	/* Set up temporaries */
	node = tree->currNode;
	key = node->currKey;

	/* Return if we've overrun the tree */
	if (key < 0)
	{
		COVER("bt_prev.c",4);
		return NULL;
	}

	/*
	 * If node has children, return rightmost key of previous
	 * child
	 */
	if (node->children != NULL)
	{
		COVER("bt_prev.c",5);
		node = node->children[key];
		while (node->children != NULL)
		{
			COVER("bt_prev.c",6);
			node->currKey = node->nkeys;
			node = node->children[node->nkeys];
		}
		node->currKey = node->nkeys - 1;
		tree->currNode = node;
		if (data != NULL)
		{
			COVER("bt_prev.c",7);
			*data = node->data[node->currKey];
		}
		return node->keys[node->currKey];
	}

	/* Leaf node, return previous key */
	COVER("bt_prev.c",8);
	key--;
	if (key >= 0)
	{
		COVER("bt_prev.c",9);
		node->currKey = key;
		if (data != NULL)
		{
			COVER("bt_prev.c",10);
			*data = node->data[key];
		}
		COVER("bt_prev.c",11);
		return node->keys[key];
	}

	/* Already visited leftmost key of node, go back to parent */
	COVER("bt_prev.c",12);
	while ((node->parent != NULL) && (key < 0))
	{
		COVER("bt_prev.c",13);
		node = node->parent;
		key = node->currKey - 1;
	}

	/* Return NULL after last key in tree */
	if (key < 0)
	{
		COVER("bt_prev.c",14);
		node->currKey = -1;
		tree->currNode = node;
		return NULL;
	}

	/* Return next key in parent */
	COVER("bt_prev.c",15);
	node->currKey = key;
	tree->currNode = node;
	if (data != NULL)
	{
		COVER("bt_prev.c",16);
		*data = node->data[key];
	}
	return node->keys[key];
}

/*********** End of file ***********/

