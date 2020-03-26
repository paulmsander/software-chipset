/********************************************************************
 *
 * btdelete.c -- This file contains functions needed to delete a key
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
 * bt_delNode -- This function searches a sub-tree for a key, and
 *               deletes the key.  If the key is found in a leaf node,
 *               it is simply removed and returned to the caller;
 *               otherwise, it is swapped with its predecessor, and
 *               the returned to the caller.  If any node loses its
 *               b-tree'ness, the tree is reorganized.  If the key is
 *               not found, NULL is returned.
 *
 *               Note that there is another static function sharing
 *               this name in the btdelrank.c file.  There is no
 *               interaction between the two.
 *
 ********************************************************************/

#ifdef __STDC__
static void *bt_delNode(BTREE tree, BTNODE *node, void *key, void **data)
#else
static void *bt_delNode(tree,node,key,data)
BTREE	tree;
BTNODE	*node;
void	*key;
void	**data;
#endif
{
	int	i;
	int	res;
	void	*retval;

	/* Key not found */
	if (node == NULL)
	{
		/* This branch is never taken. */
		COVER("btdelete.c",1);
		return NULL;
	}

	/* Search for key, descend tree until found or find leaf */
	i = bt_searchNode(node,key,tree->comp,&res);
	if (res == 0)
	{
		COVER("btdelete.c",2);
		if (node->children == NULL)
		{
			/* Key was not found */
			COVER("btdelete.c",3);
			return NULL;
		}
		COVER("btdelete.c",4);
		retval = bt_delNode(tree,node->children[i],key,data);
		if (retval)
		{
			COVER("btdelete.c",5);
			node->tsize--;
		}
	}
	else
	{
		COVER("btdelete.c",6);
		/* Return the deleted node to caller */
		if (data != NULL)
		{
			COVER("btdelete.c",7);
			*data = node->data[i];
		}
		retval = node->keys[i];

		if (node->children == NULL)
		{
			/* Delete from leaf */
			COVER("btdelete.c",8);
			bt_delKey(node,i);
		}
		else
		{
			/* Swap with predecessor */
			COVER("btdelete.c",9);
			node->keys[i] = bt_delPred(tree,node->children[i],
			                           &node->data[i]);
			node->tsize--;
		}
	}

	/* If a child node was reorganized, rebalancing may be necessary */
	if ((node->children != NULL) &&
	    (node->children[i]->nkeys < (tree->order - 1) / 2))
	{
		COVER("btdelete.c",10);
		res = bt_rotateRight(node,i - 1,tree->order);
		if (res == 0)
		{
			COVER("btdelete.c",11);
			res = bt_rotateLeft(node,i,tree->order);
		}
		if (res == 0)
		{
			COVER("btdelete.c",12);
			if (i >= node->nkeys)
			{
				COVER("btdelete.c",13);
				i--;
			}
			bt_weld(tree,node,i);
		}
	}
	return retval;
}

/********************************************************************
 *
 * bt_delete -- This function deletes the specified key from a
 *              b-tree and reorganizes it as necessary.  The deleted
 *              key is returned to the caller if it is found, NULL
 *              is returned otherwise.
 *
 ********************************************************************/

#ifdef __STDC__
void *bt_delete(void *ptree, void *key, void **data)
#else
void	*bt_delete(ptree,key,data)
void	*ptree;
void	*key;
void	**data;
#endif
{
	BTNODE	*root;
	void	*retval;
	BTREE	tree;

	tree = (BTREE) ptree;

	/* Check parameters */
	if (ptree == NULL)
	{
		COVER("btdelete.c",14);
		return NULL;
	}

	if (key == NULL)
	{
		COVER("btdelete.c",15);
		return NULL;
	}

	/* Do no deletion if tree is empty */
	root = tree->root;
	if (root->nkeys == 0)
	{
		COVER("btdelete.c",16);
		return NULL;
	}

	/* Delete the key */
	retval = bt_delNode(tree,root,key,data);

	/*
	 * Delete the root if it is empty, yet its children are not.
	 * This happens after a weld on the last key in the root.
	 */
	COVER("btdelete.c",16);
	if ((root->nkeys == 0) && (root->children != NULL))
	{
		COVER("btdelete.c",17);
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
		COVER("btdelete.c",18);
		tree->currNode = NULL;
	}
	return retval;
}

/************ End of file ***************/

