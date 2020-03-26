/********************************************************************
 *
 * btdelrank.c -- This file contains functions necessary to perform
 *                deletion by rank from a B-tree.
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
 * bt_delNode -- This function performs a recursive descent of the
 *               tree until the key at the desired rank location is
 *               found.  If that key is found in a leaf node, it is
 *               removed; if not, its predecessor replaces it.  In
 *               any case, the tree is reorganized as necessary.
 *
 *               Note that there is another static function sharing
 *               this name in the btdelete.c file.  There is no
 *               interaction between the two.
 *
 ********************************************************************/

#ifdef __STDC__
static void *bt_delNode(BTREE tree, BTNODE *node, int rank, void **data)
#else
static void *bt_delNode(tree,node,rank,data)
BTREE	tree;
BTNODE	*node;
int	rank;
void	**data;
#endif
{
	void	*retval;
	int	i;
	int	acc;
	int	last;
	int	res;

	if (node->children == NULL)
	{
		/* rank < node->nkeys */
		COVER("btdelrank.c",1);
		if (data != NULL)
		{
			COVER("btdelrank.c",2);
			*data = node->data[rank];
		}
		retval = node->keys[rank];
		bt_delKey(node,rank);
	}
	else
	{
		/*
		 * Scan to find subtree containing node containing key of
		 * given rank
		 */
		COVER("btdelrank.c",3);
		acc = 0;
		last = 0;
		for (i = 0; acc += node->children[i]->tsize, acc < rank; i++)
		{
			COVER("btdelrank.c",4);
			acc++;		/* Count key in this node */
			last = acc;
		}

		if (acc == rank)
		{
			COVER("btdelrank.c",5);
			/* Key is contained in this node */
			if (data != NULL)
			{
				COVER("btdelrank.c",6);
				*data = node->data[i];
			}
			retval = node->keys[i];
			node->keys[i] = bt_delPred(tree,node->children[i],
			                           &node->data[i]);
		}
		else
		{
			/* Key is in the subtree rooted at the i'th child */
			COVER("btdelrank.c",7);
			retval = bt_delNode(tree,node->children[i],rank-last,
			                    data);
		}
		node->tsize--;

		/*
		 * If a child node was reorganized, rebalancing may be
		 * necessary
		 */
		if (node->children[i]->nkeys < (tree->order - 1) / 2)
		{
			COVER("btdelrank.c",8);
			res = bt_rotateRight(node,i - 1,tree->order);
			if (res == 0)
			{
				COVER("btdelrank.c",9);
				res = bt_rotateLeft(node,i,tree->order);
			}
			if (res == 0)
			{
				COVER("btdelrank.c",10);
				if (i >= node->nkeys)
				{
					COVER("btdelrank.c",11);
					i--;
				}
				bt_weld(tree,node,i);
			}
		}
	}
	return retval;
}

/********************************************************************
 *
 * bt_delRank -- This function deletes the key having the specified
 *               rank from a b-tree and reorganizes it as necessary.
 *               The deleted key is returned to the caller if it is
 *               found, NULL is returned otherwise.
 *
 ********************************************************************/

#ifdef __STDC__
void *bt_delRank(void *ptree, int rank, void **data)
#else
void	*bt_delRank(ptree,rank,data)
void	*ptree;
int	rank;
void	**data;
#endif
{
	BTNODE	*root;
	void	*retval;
	BTREE	tree;

	tree = (BTREE) ptree;

	/* Do no deletion if tree is empty */
	if (tree == NULL)
	{
		COVER("btdelrank.c",12);
		return NULL;
	}
	if (rank < 0)
	{
		COVER("btdelrank.c",13);
		return NULL;
	}
	if (rank >= tree->root->tsize)
	{
		COVER("btdelrank.c",14);
		return NULL;
	}
	COVER("btdelrank.c",15);
	root = tree->root;

	/* Delete the key */
	retval = bt_delNode(tree,root,rank,data);

	/*
	 * Delete the root if it is empty, yet its children are not.
	 * This happens after a weld on the last key in the root.
	 */
	if ((root->nkeys == 0) && (root->children != NULL))
	{
		COVER("btdelrank.c",16);
		tree->root = root->children[0];
		bt_free(root->keys);
		bt_free(root->data);
		bt_free(root->children);
		bt_free(root);
		tree->capacity -= tree->order - 1;
		tree->root->parent = NULL;
	}
	if (retval != NULL)
	{
		COVER("btdelrank.c",17);
		tree->currNode = NULL;
	}
	return retval;
}

/******** End of file ********/

