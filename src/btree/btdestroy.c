/********************************************************************
 *
 * btdestroy.c -- This function contains functions needed to deallocate
 *                an in-memory B-tree in its entirety.
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
 * bt_freeNode -- This function frees a node in a b-tree.  It is
 *                provided with functions that free each key and its
 *                related data in the node also.  The free_key and
 *                free_data functions have the following interface:
 *
 *			void free_stuff(keyOrData,info)
 *			void *keyOrData;
 *			void *info;
 *
 *              If NULL is passed as the free_stuff function, the node
 *              is freed, but no action is taken for the keys or data.
 *
 *              The info parameter is used for passing information from
 *              the client to the free_stuff function.
 *
 *              The free_data function is always called before the
 *              free_key function.
 *
 ********************************************************************/

#ifdef __STDC__
static void bt_freeNode(BTNODE *node, void (*free_key)(void*,void*),
                        void (*free_data)(void*,void*), void *info)
#else
static void bt_freeNode(node,free_key,free_data,info)
BTNODE	*node;
void	(*free_key)();
void	(*free_data)();
void	*info;
#endif
{
	int	i;

	if (node->children != NULL)
	{
		COVER("btdestroy.c",1);
		for (i = 0; i <= node->nkeys; i++)
		{
			COVER("btdestroy.c",2);
			bt_freeNode(node->children[i],free_key,free_data,info);
		}
		bt_free(node->children);
	}
	for (i = 0; i < node->nkeys; i++)
	{
		COVER("btdestroy.c",3);
		if (free_data != NULL)
		{
			COVER("btdestroy.c",4);
			(*free_data)(node->data[i],info);
		}
		if (free_key != NULL)
		{
			COVER("btdestroy.c",5);
			(*free_key)(node->keys[i],info);
		}
	}
	COVER("btdestroy.c",6);
	bt_free(node->keys);
	bt_free(node->data);
	bt_free(node);
	return;
}

/********************************************************************
 *
 * bt_destroy -- This function frees a b-tree structure.  It is also
 *               passed functions that free the keys and data contained
 *               by the tree.  The free_key and free_data functions have the
 *               same calling protocol their counterparts passed to bt_freeNode
 *               above.
 *
 ********************************************************************/

#ifdef __STDC__
void bt_destroy(void *ptree, void (*free_key)(void*,void*),
                void (*free_data)(void*,void*), void *info)
#else
void bt_destroy(ptree,free_key,free_data,info)
void	*ptree;
void	(*free_key)();
void	(*free_data)();
void	*info;
#endif
{
	BTREE	tree;

	COVER("btdestroy.c",7);
	if (ptree != NULL)
	{
		COVER("btdestroy.c",8);
		tree = (BTREE) ptree;
		bt_freeNode(tree->root,free_key,free_data,info);
		bt_free(tree);
	}
	return;
}

/************ End of file ***********/

