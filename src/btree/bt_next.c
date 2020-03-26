/********************************************************************
 *
 * bt_next.c -- This file contains functions needed to scan an in-memory
 *              B-tree in ascending order.
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
 * bt_next -- This function returns the key that appears next in
 *            the lexical order of the items stored in the tree,
 *            after the last bt_search, bt_next, bt_prev, bt_last,
 *            or bt_first.  NULL is returned if the tree is empty, an
 *            insertion or deletion invalidated the state of the
 *            tree, or the last item in the tree was already visited.
 *
 *******************************************************************/

#ifdef __STDC__
void *bt_next(void *ptree, void **data)
#else
void *bt_next(ptree,data)
void	*ptree;
void	**data;
#endif
{
	BTNODE	*node;
	int	key;
	BTREE	tree;

	COVER("bt_next.c",1);

	/* Return if error, or insertion/deletion invalidated state */
	tree = (BTREE) ptree;
	if (tree == NULL)
	{
		COVER("bt_next.c",2);
		return NULL;
	}
	if (tree->currNode == NULL)
	{
		COVER("bt_next.c",3);
		return NULL;
	}

	/* Set up temporaries */
	node = tree->currNode;
	key = node->currKey;

	/* Return if we've overrun the tree */
	if (key >= node->nkeys)
	{
		COVER("bt_next.c",4);
		return NULL;
	}

	/*
	 * Bump current key in current node, compensating for unsuccessful
	 * search
	 */
	if (tree->nextOk)
	{
		COVER("bt_next.c",5);
		key++;
	}
	tree->nextOk = 1;

	/* If node has children, return leftmost key of next child */
	if (node->children != NULL)
	{
		COVER("bt_next.c",6);
		node->currKey = key;
		node = node->children[key];
		while (node->children != NULL)
		{
			COVER("bt_next.c",7);
			node->currKey = 0;
			node = node->children[0];
		}
		node->currKey = 0;
		tree->currNode = node;
		if (data != NULL)
		{
			COVER("bt_next.c",8);
			*data = node->data[0];
		}
		return node->keys[0];
	}

	/* Leaf node, return next key */
	if (key < node->nkeys)
	{
		COVER("bt_next.c",9);
		node->currKey = key;
		if (data != NULL)
		{
			COVER("bt_next.c",10);
			*data = node->data[key];
		}
		return node->keys[key];
	}

	/* Already visited rightmost key of leaf, go back to parent */
	COVER("bt_next.c",11);
	while ((node->parent != NULL) && (key >= node->nkeys))
	{
		COVER("bt_next.c",12);
		node = node->parent;
		key = node->currKey;
	}

	COVER("bt_next.c",13);
	/* Return NULL after last key in tree */
	if (key >= node->nkeys)
	{
		COVER("bt_next.c",14);
		tree->currNode = node;
		node->currKey = key;
		return NULL;
	}

	/* Return next key in parent */
	COVER("bt_next.c",15);
	tree->currNode = node;
	if (data != NULL)
	{
		COVER("bt_next.c",16);
		*data = node->data[key];
	}
	return node->keys[key];
}

/*********** End of file ***********/

