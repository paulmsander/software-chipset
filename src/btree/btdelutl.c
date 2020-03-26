/********************************************************************
 *
 * btdelutl.c -- This file contains functions needed to delete a key
 *               from an in-memory B-tree.
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
 * bt_delKey -- This function deletes the specified key from the
 *              specified node.
 *
 ********************************************************************/

#ifdef __STDC__
void bt_delKey(BTNODE *node, int n)
#else
void bt_delKey(node,n)
BTNODE	*node;
int	n;
#endif
{
	int	i;

	COVER("btdelutl.c",1);
	for (i = n; i < node->nkeys - 1; i++)
	{
		COVER("btdelutl.c",2);
		node->keys[i] = node->keys[i+1];
		node->data[i] = node->data[i+1];
	}
	if (node->children != NULL)
	{
		/*
		 * This branch should never be taken, since the only places
		 * where keys are actually deleted are from leaf nodes.
		 */
		COVER("btdelutl.c",3);
		for (i = n; i < node->nkeys; i++)
		{
			COVER("btdelutl.c",4);
			node->children[i] = node->children[i+1];
		}
	}
	node->nkeys--;
	node->tsize--;
	return;
}

/********************************************************************
 *
 * bt_weld -- This function is the opposite of burst, above.  It joins
 *            two neighboring children of the given node, and lowers a
 *            key into the result.
 *
 ********************************************************************/

#ifdef __STDC__
void bt_weld(BTREE tree, BTNODE *node, int n)
#else
void bt_weld(tree,node,n)
BTREE	tree;
BTNODE	*node;
int	n;
#endif
{
	int	i;
	int	j;
	BTNODE	*left;
	BTNODE	*right;

	if (node->children == NULL)
	{
		/*
		 * This branch is never taken, because all functions that
		 * call bt_burst explicitly test for child nodes.
		 */
		COVER("btdelutl.c",5);
		return;
	}
	COVER("btdelutl.c",6);
	left = node->children[n];
	right = node->children[n+1];
	i = left->nkeys;
	left->keys[i] = node->keys[n];
	left->data[i] = node->data[n];
	for (i++, j = 0; j < right->nkeys; i++, j++)
	{
		COVER("btdelutl.c",7);
		left->keys[i] = right->keys[j];
		left->data[i] = right->data[j];
	}
	for (i = n + 1; i < node->nkeys; i++)
	{
		COVER("btdelutl.c",8);
		node->keys[i-1] = node->keys[i];
		node->data[i-1] = node->data[i];
		node->children[i] = node->children[i+1];
	}
	node->nkeys--;
	if (left->children != NULL)
	{
		COVER("btdelutl.c",9);
		for (i = left->nkeys + 1, j = 0; j <= right->nkeys; i++, j++)
		{
			COVER("btdelutl.c",10);
			left->children[i] = right->children[j];
			left->children[i]->parent = left;
		}
		bt_free(right->children);
	}
	left->nkeys += right->nkeys + 1;
	left->tsize += right->tsize + 1;
	bt_free(right->keys);
	bt_free(right->data);
	bt_free(right);
	tree->capacity -= tree->order - 1;
	return;
}

/********************************************************************
 *
 * bt_delPred -- This function searches a sub-tree, and deletes the
 *               highest key it finds, and returns it to its caller.
 *               If any node along the way  loses its b-tree'ness, the
 *               tree is reorganized after the deletion.
 *
 ********************************************************************/

#ifdef __STDC__
void *bt_delPred(BTREE tree, BTNODE *node, void **data)
#else
void *bt_delPred(tree,node,data)
BTREE	tree;
BTNODE	*node;
void	**data;
#endif
{
	BTNODE	*pnode;
	int	res;
	void	*retval;

	/*
	 * If at a leaf node, delete the highest key, otherwise
	 * call self recursively
	 */
	if (node->children == NULL)
	{
		COVER("btdelutl.c",11);
		if (data != NULL)
		{
			COVER("btdelutl.c",12);
			*data = node->data[node->nkeys - 1];
		}
		retval = node->keys[node->nkeys - 1];
		node->nkeys--;
	}
	else
	{
		COVER("btdelutl.c",13);
		pnode = node->children[node->nkeys];
		retval = bt_delPred(tree,pnode,data);

		/* Reorganize tree if node gets too empty */
		if (pnode->nkeys < (tree->order - 1) / 2)
		{
			COVER("btdelutl.c",14);
			res = bt_rotateRight(node,node->nkeys - 1,tree->order);
			if (res == 0)
			{
				COVER("btdelutl.c",15);
				bt_weld(tree,node,node->nkeys - 1);
			}
		}
	}
	node->tsize--;
	return retval;
}

/******** End of File ********/

