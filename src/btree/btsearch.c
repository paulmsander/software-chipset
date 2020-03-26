/********************************************************************
 * btsearch -- This file contains functions needed to locate an
 *             item in an in-memory B-tree.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ********************************************************************/

#include <stdio.h>
#include "btpriv.h"

/***********************************************************************
 *
 * bt_locate -- This function performs a recursive-descent search of
 *              a sub-tree for a key.  The key is returned if found,
 *              or NULL otherwise.
 *
 ***********************************************************************/

#ifdef __STDC__
static void *bt_locate(BTREE tree, BTNODE *node, void *target, int (*comp)(),
                       void **data)
#else
static void *bt_locate(tree,node,target,comp,data)
BTREE	tree;
BTNODE	*node;
void	*target;
int	(*comp)();
void	**data;
#endif
{
	int	res;
	int	i;
	int	eq;

	COVER("btsearch.c",1);
	i = bt_searchNode(node,target,comp,&eq);
	node->currKey = i;
	if (eq)
	{
		COVER("btsearch.c",2);
		tree->currNode = node;
		tree->nextOk = 1;
		if (data != NULL)
		{
			COVER("btsearch.c",3);
			*data = node->data[i];
		}
		COVER("btsearch.c",4);
		return node->keys[i];
	}
	else if (node->children == NULL)
	{
		COVER("btsearch.c",5);
		tree->currNode = node;
		tree->nextOk = 0;
		return NULL;
	}
	else
	{
		COVER("btsearch.c",6);
		return bt_locate(tree,node->children[i],target,comp,data);
	}
}

/***********************************************************************
 *
 * bt_search -- This function searches a tree for a specified key.  The
 *              key is returned if found, or NULL if not.
 *
 ***********************************************************************/

#ifdef __STDC__
void *bt_search(void *ptree, void *target, void **data)
#else
void *bt_search(ptree,target,data)
void	*ptree;
void	*target;
void	**data;
#endif
{
	BTREE	tree;

	tree = (BTREE) ptree;
	if (tree == NULL)
	{
		COVER("btsearch.c",7);
		return NULL;
	}
	if (target == NULL)
	{
		COVER("btsearch.c",8);
		return NULL;
	}
	COVER("btsearch.c",9);
	return bt_locate(tree,tree->root,target,tree->comp,data);
}

/*********** End of file ************/

