/****************************************************************
 *
 * bttraverse.c -- This file contains functions needed to
 *                 traverse an in-memory B-tree, passing each
 *                 item stored there to a callback function.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ****************************************************************/

#include <stdio.h>
#include "btpriv.h"

/****************************************************************
 *
 * bt_visit -- This function is used while traversing a b-tree.
 *             It is called once for each node.  It calls some
 *             specified function once for each key in its
 *             key array, and calls itself once for each child
 *             in its child array.
 *
 ****************************************************************/

#ifdef __STDC__
static void bt_visit(BTNODE *node, void (*fn)(void*, void*, void*), void *parms)
#else
static void bt_visit(node,fn,parms)
BTNODE	*node;
void	(*fn)();
void	*parms;
#endif
{
	int	i;

	if (node == NULL)
	{
		/* Should never happen */
		COVER("bttraverse.c",1);
		return;
	}
	COVER("bttraverse.c",2);
	for (i = 0; i < node->nkeys; i++)
	{
		if (node->children != NULL)
		{
			COVER("bttraverse.c",3);
			bt_visit(node->children[i],fn,parms);
		}
		COVER("bttraverse.c",4);
		(*fn)(node->keys[i],parms,node->data[i]);
	}
	COVER("bttraverse.c",5);
	if (node->children != NULL)
	{
		COVER("bttraverse.c",6);
		bt_visit(node->children[i],fn,parms);
	}
	COVER("bttraverse.c",7);
	return;
}

/****************************************************************
 *
 * bt_traverse -- This function traverses a b-tree, calling some
 *                specified function once for each key stored in
 *                it.  The specified function has the following
 *                protocol:
 *
 *			void fn(key,parms)
 *			void *key;
 *			void *parms;
 *                      void *data;
 *
 *                where key is a pointer to a key stored in the
 *                btree, parms is the parameter structure passed by
 *                the caller, and data is the secondary data stored
 *                with the key.
 *
 *                The nodes are visited in descending order, if
 *                the comp function passed to bt_new is
 *                strcmp-like.
 *
 ****************************************************************/

#ifdef __STDC__
void bt_traverse(void *ptree, void (*fn)(void*, void*, void*), void *parms)
#else
void bt_traverse(ptree,fn,parms)
void	*ptree;
void	(*fn)();
void	*parms;
#endif
{
	BTREE	tree;

	COVER("bttraverse.c",8);
	tree = (BTREE) ptree;
	if ((tree != NULL) && (fn != NULL))
	{
		COVER("bttraverse.c",9);
		bt_visit(tree->root,fn,parms);
	}
	return;
}

/********* End of file *********/

