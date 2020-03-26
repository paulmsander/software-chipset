/********************************************************************
 *
 * btutil.c -- This function contains utility functions that are
 *             used for many features of an in-memory B-tree
 *             implementation.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ********************************************************************/

#define __BTUTIL_C__
#include <stdio.h>
#include "btpriv.h"


/********************************************************************
 *
 * bt_searchNode -- This function searches a node for a key.  If the key
 *                  is found, its index in the node's key array is
 *                  returned, along with a flag indicating that the key
 *                  was found.  If the key is not found, the index of the
 *                  next higher key in the key array is returned, along
 *                  with a "not found" indication.
 *
 ********************************************************************/

#ifdef __STDC__
int bt_searchNode(BTNODE *node, void *target, int (*comp)(), int *eq)
#else
int bt_searchNode(node,target,comp,eq)
BTNODE	*node;		/* Node to be searched */
void	*target;	/* Key to search for */
int	(*comp)();	/* strcmp()-like comparison function */
int	*eq;		/* 0 if not found, non-zero otherwise */
#endif
{
	int	i;
	int	res;
	int	hi;
	int	lo;

	res = -1;

	/*
	 * Perform linear search of node contains 7 keys or less,
	 * otherwise perform binary search
	 */
	COVER("btutil.c",1);
	if (node->nkeys <= 7)
	{
		COVER("btutil.c",2);
		for (i = 0; i < node->nkeys; i++)
		{
			res = (*comp)(node->keys[i],target);
			if (res >= 0)
			{
				COVER("btutil.c",3);
				break;
			}
		}
		COVER("btutil.c",4);
	}
	else
	{
		COVER("btutil.c",5);
		lo = 0;
		hi = node->nkeys - 1;
		while ((lo <= hi) && (res != 0))
		{
			i = (lo + hi) / 2;
			res = (*comp)(node->keys[i],target);
			if (res < 0)
			{
				COVER("btutil.c",6);
				lo = i + 1;
			}
			else if (res > 0)
			{
				COVER("btutil.c",7);
				hi = i - 1;
			}
			COVER("btutil.c",8);
		}
		if (res < 0)
		{
			COVER("btutil.c",9);
			i++;
		}
		COVER("btutil.c",10);
	}
	COVER("btutil.c",11);
	*eq = (res == 0);	/* Indicate successful search */
	node->currKey = i + *eq - 1;
	return i;
}

/******************************************************************
 *
 * bt_rotateRight -- Given a node and an index into its key array, this
 *                   function rotates the node right at the specified
 *                   key.  This is used during insertion and deletion to
 *                   keep the tree balanced.  The return value is 0 if
 *                   the function fails, i.e. the node on the left
 *                   cannot lose keys, the node on the right cannot
 *                   gain keys, or the specified node is a leaf; 1 is
 *                   returned if successful.
 *
 ******************************************************************/

#ifdef __STDC__
int bt_rotateRight(BTNODE *node,int n,int order)
#else
int bt_rotateRight(node,n,order)
BTNODE	*node;
int	n;
int	order;
#endif
{
	int	i;
	BTNODE	*right;
	BTNODE	*left;

	/* Test parameters */
	if (n >= node->nkeys)
	{
		/*
		 * This branch is never taken because callers test this
		 * condition.
		 */
		COVER("btutil.c",12);
		return 0;
	}
	if (n < 0)
	{
		COVER("btutil.c",13);
		return 0;
	}
	COVER("btutil.c",14);

	/* Point to children */
	left = node->children[n];
	right = node->children[n+1];

	/* Return FALSE if rotation is not possible */
	if (left == NULL)
	{
		/*
		 * This branch is never taken, because the callers insure
		 * that this node has children.
		 */
		COVER("btutil.c",15);
		return 0;
	}
	if (left->nkeys <= order/2)
	{
		COVER("btutil.c",16);
		return 0;
	}
	if (right->nkeys >= order - 1)
	{
		/*
		 * Coverage analysis was unable to stimulate this branch,
		 * but inspection indicates that it is correct.
		 */
		COVER("btutil.c",17);
		return 0;
	}
	COVER("btutil.c",18);

	/* Shift the right child's keys */
	for (i = right->nkeys; i > 0; i--)
	{
		right->keys[i] = right->keys[i - 1];
		right->data[i] = right->data[i - 1];
	}

	/* Rotate keys */
	right->keys[0] = node->keys[n];
	right->data[0] = node->data[n];
	node->keys[n] = left->keys[left->nkeys - 1];
	node->data[n] = left->data[left->nkeys - 1];
	left->keys[left->nkeys - 1] = NULL;
	left->data[left->nkeys - 1] = NULL;

	if (right->children != NULL)
	{
		COVER("btutil.c",19);
		/* Shift the right child's children */
		for (i = right->nkeys; i >= 0; i--)
		{
			right->children[i + 1] = right->children[i];
		}

		/* Rotate children */
		right->children[0] = left->children[left->nkeys];
		right->children[0]->parent = right;
		left->children[left->nkeys] = NULL;
		right->tsize += right->children[0]->tsize;
		left->tsize -= right->children[0]->tsize;
	}
	COVER("btutil.c",20);

	/* Update key count and return TRUE */
	right->nkeys++;
	right->tsize++;
	left->nkeys--;
	left->tsize--;
	return 1;
}

/******************************************************************
 *
 * bt_rotateLeft -- Given a node and an index into its key array, this
 *                  function rotates the node left at the specified
 *                  key.  This is used during insertion and deletion to
 *                  keep the tree balanced.  The return value is 0 if
 *                  the function fails, i.e. the node on the right
 *                  cannot lose keys, the node on the left cannot
 *                  gain keys, or the specified node is a leaf; 1 is
 *                  returned when successful.
 *
 ******************************************************************/

#ifdef __STDC__
int bt_rotateLeft(BTNODE *node, int n, int order)
#else
int bt_rotateLeft(node,n,order)
BTNODE	*node;
int	n;
int	order;
#endif
{
	int	i;
	BTNODE	*right;
	BTNODE	*left;

	/* Test parameters */
	if (n < 0)
	{
		/*
		 * This branch is never taken because callers test for this
		 * condition.
		 */
		COVER("btutil.c",21);
		return 0;
	}
	if (n >= node->nkeys)
	{
		COVER("btutil.c",22);
		return 0;
	}
	COVER("btutil.c",23);

	/* Point to children */
	right = node->children[n+1];
	left = node->children[n];

	/* Return FALSE if rotation is not possible */
	if (left == NULL)
	{
		/*
		 * This branch is never taken, because the callers insure
		 * that this node has children.
		 */
		COVER("btutil.c",24);
		return 0;
	}
	if (right->nkeys <= order/2)
	{
		COVER("btutil.c",25);
		return 0;
	}
	if (left->nkeys >= order - 1)
	{
		/*
		 * Coverage analysis was unable to stimulate this branch,
		 * but inspection indicates that it is correct.
		 */
		COVER("btutil.c",26);
		return 0;
	}
	COVER("btutil.c",27);

	/* Rotate keys */
	left->keys[left->nkeys] = node->keys[n];
	left->data[left->nkeys] = node->data[n];
	node->keys[n] = right->keys[0];
	node->data[n] = right->data[0];

	/* Update key counts */
	left->nkeys ++;
	right->nkeys --;
	left->tsize ++;
	right->tsize --;

	/* Shift the right child's keys */
	for (i = 0; i < right->nkeys; i++)
	{
		right->keys[i] = right->keys[i+1];
		right->data[i] = right->data[i+1];
	}
	right->keys[i] = NULL;
	right->data[i] = NULL;

	if (left->children != NULL)
	{
		COVER("btutil.c",28);
		left->tsize += right->children[0]->tsize;
		right->tsize -= right->children[0]->tsize;

		/* Rotate children */
		left->children[left->nkeys] = right->children[0];
		left->children[left->nkeys]->parent = left;

		/* Shift the right child's children */
		for (i = 0; i <= right->nkeys; i++)
		{
			right->children[i] = right->children[i+1];
		}
		right->children[i] = NULL;
	}
	COVER("btutil.c",29);

	/* Return TRUE */
	return 1;
}

/*********** End of file ************/

