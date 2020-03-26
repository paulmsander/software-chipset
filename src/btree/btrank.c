/********************************************************************
 *
 * btrank.c -- This file contains functions needed to locate a
 *             key given its rank location.
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
 * bt_locRank -- This function performs a recursive descent of the
 *               tree until the key at the desired rank location is
 *               found.
 *
 *               Note that "node" is an in-out parameter.  As input,
 *               it is the current node to be searched.  As output,
 *               it is the node where the key was actually found.
 *               It is used to mark the updated current node stored
 *               in the root so that bt_next and bt_prev will work
 *               later.
 *
 ********************************************************************/

#ifdef __STDC__
static void *bt_locRank(BTNODE **node, int rank, void **data)
#else
static void *bt_locRank(node,rank,data)
BTNODE	**node;
int	rank;
void	**data;
#endif
{
	void	*retval;
	int	i;
	int	acc;
	int	last;

	COVER("btrank.c",1);
	if ((*node)->children == NULL)
	{
		COVER("btrank.c",2);
		/* rank < (*node)->nkeys */
		(*node)->currKey = rank;
		retval = (*node)->keys[rank];
		if (data != NULL)
		{
			COVER("btrank.c",3);
			*data = (*node)->data[rank];
		}
		COVER("btrank.c",4);
	}
	else
	{
		/*
		 * Scan to find subtree containing node containing key of
		 * given rank
		 */
		COVER("btrank.c",5);
		acc = 0;
		last = 0;
		for (i = 0; acc += (*node)->children[i]->tsize, acc < rank; i++)
		{
			COVER("btrank.c",6);
			acc++;		/* Count key in this node */
			last = acc;
		}
		COVER("btrank.c",7);

		(*node)->currKey = i;
		if (acc == rank)
		{
			COVER("btrank.c",8);
			/* Key is contained in this node */
			if (data != NULL) *data = (*node)->data[i];
			retval = (*node)->keys[i];
		}
		else
		{
			COVER("btrank.c",9);
			/* Key is in the subtree rooted at the i'th child */
			*node = (*node)->children[i];
			retval = bt_locRank(node, rank - last,data);
		}
		COVER("btrank.c",10);
	}
	COVER("btrank.c",11);
	return retval;
}

/********************************************************************
 *
 * bt_rank -- This function locates a key within a tree that has
 *            the given rank number.  NULL is returned if the
 *            rank is out of range; rank is zero-based.
 *
 *******************************************************************/

#ifdef __STDC__
void *bt_rank(void *ptree, int rank, void *data)
#else
void *bt_rank(ptree,rank,data)
void	*ptree;
int	rank;
void	*data;
#endif
{
	void	*retval;
	BTREE	tree;

	tree = (BTREE) ptree;
	if (tree == NULL)
	{
		COVER("btrank.c",12);
		retval = NULL;
	}
	else if (rank < 0)
	{
		COVER("btrank.c",13);
		retval = NULL;
	}
	else if (rank >= tree->root->tsize)
	{
		COVER("btrank.c",14);
		retval = NULL;
	}
	else
	{
		COVER("btrank.c",15);
		tree->currNode = tree->root;
		retval = bt_locRank(&tree->currNode,rank,data);
		tree->nextOk = 1;
	}
	return retval;
}

/********* End of file ************/

