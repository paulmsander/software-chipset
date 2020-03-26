/***********************************************************************
 *
 * btnew.c -- This file contains functions to create a new in-memory
 *            B-tree.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***********************************************************************/

#include <stdio.h>
#include "btpriv.h"

/***********************************************************************
 *
 * bt_new -- Given a BT_SETUP structure, this function creates an empty
 *           B-tree structure.
 *
 ***********************************************************************/

#ifdef __STDC__
void	*bt_new(void *psetup)
#else
void	*bt_new(psetup)
void	*psetup;
#endif
{
	BTREE		tree;
	BT_SETUP	*setup;
	int		i;
	int		order;

	/* Validate parameters */
	setup = (BT_SETUP*) psetup;
	if (setup == NULL)
	{
		COVER("btnew.c",1);
		return (void *) NULL;
	}
	COVER("btnew.c",2);
	order = setup->order;

	/* Allocate the handle */
	tree = (BTREE) bt_malloc(sizeof(struct btree));
	if (tree != NULL)
	{
		/* Allocate the root */
		tree->root = (BTNODE*) bt_malloc(sizeof(struct btnode));
		if (tree->root != NULL)
		{
			/* Initialize root */
			tree->order = order;
			tree->comp = setup->comp;
			tree->data = setup->data;
			tree->root->nkeys = 0;
			tree->root->children = NULL;

			/* Allocate key array */
			tree->root->keys =
				(void**)bt_malloc((order - 1) * sizeof(void*));
			if (tree->root->keys != NULL)
			{
				tree->root->data = (void**)bt_malloc(
				                  (order - 1) * sizeof(void*));
				if (tree->root->data != NULL)
				{
					/* Initialize keys */
					for (i = 0; i < order - 1; i++)
					{
						tree->root->keys[i] = NULL;
						tree->root->data[i] = NULL;
					}
					tree->root->nkeys = 0;
					tree->root->parent = NULL;
					tree->root->tsize = 0;
					tree->capacity = order - 1;
					tree->currNode = NULL;
					return (void *) tree;
				}
				/* Failed to allocate data, free keys */
				bt_free(tree->root->keys);
			}

			/* Failed to allocate keys, free tree */
			bt_free(tree->root);
		}
		/* Failed to allocate root, free handle */
		bt_free(tree);
	}
	/* Failed to allocate handle, return null (error) */
	return (void *) NULL;
}

/***********************************************************************
 *
 * bt_setup -- This function allocates a B-tree setup structure, and
 *             returns it to the caller.  The parameters are the order
 *             (max number of children per node) of the tree, and a
 *             pointer to a comparison function for keys.  The setup
 *             structure is then passed to bt_new() when a new tree
 *             is created.
 *
 ***********************************************************************/

#ifdef __STDC__
void *bt_setup(int order, int (*comp)(void*,void*), void *data)
#else
void *bt_setup(order,comp,data)
int	order;
int	(*comp)();
void	*data;
#endif
{
	BT_SETUP	*retval;

	if (comp == NULL)
	{
		COVER("btnew.c",3);
		return (void *) NULL;
	}
	if (order < 3)
	{
		COVER("btnew.c",4);
		return (void *) NULL;
	}
	COVER("btnew.c",5);
	retval = (BT_SETUP*) bt_malloc(sizeof(BT_SETUP));
	if (retval != NULL)
	{
		retval->order = order;
		retval->comp = (COMPFN) comp;
		retval->data = data;
	}
	return (void*) retval;
}

/***********************************************************************
 *
 * bt_freeSetup -- This function frees a B-tree setup structure.
 *
 ***********************************************************************/

#ifdef __STDC__
void bt_freeSetup(void *setup)
#else
void bt_freeSetup(setup)
void	*setup;
#endif
{
	COVER("btnew.c",6);
	if (setup != NULL)
	{
		bt_free(setup);
	}
	return;
}

/********** End of file **********/

