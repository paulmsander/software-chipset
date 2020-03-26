/*********************************************************************
 *
 * btdump.c -- This function contains functions needed to display
 *             the contents of an in-memory B-tree, passing each key
 *             to a callback function.  This file contains non-portable
 *             code that is intended to help debug the B-tree
 *             implementation.  Also, all pointers are displayed
 *             surrounded by "X", so that an automated test program
 *             can filter out machine-dependent pointer values.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *********************************************************************/

#include <stdio.h>
#include "btpriv.h"

/*********************************************************************
 *
 * bt_dumpNode -- This function displays the contents of a node and
 *                then recursively displays its children.  Note
 *                that this function assumes that a pointer to a node
 *                is the same size as an integer.
 *
 *********************************************************************/

#ifdef __STDC__
static void bt_dumpNode(BTNODE *node, void (*key_dump)(void*,void*,void*),
                        void *info)
#else
static void bt_dumpNode(node,key_dump,info)
BTNODE	*node;
void	(*key_dump)();
void	*info;
#endif
{
	int	i;

	if (node == NULL)
	{
		printf("ERROR:  null node pointer\n");
		return;
	}
	printf("%08x: %d keys (keys %08x, children %08x, data %08x),\n",
	       (int) node,node->nkeys,node->keys,node->children,node->data);
	printf("currKey = %d, parent = %08x, tsize = %d\n",
	       node->currKey,(int) node->parent,node->tsize);
	printf("--------\n");
	for (i = 0; i < node->nkeys; i++)
	{
		if (node->children != NULL)
		{
			printf("    %08x\n",(int)(node->children[i]));
		}
		else
		{
			printf("    %08x\n",0);
		}
		if (key_dump != NULL)
		{
			printf("        ");
			(*key_dump)(node->keys[i],node->data[i],info);
		}
	}
	if (node->children != NULL)
	{
		printf("    %08x\n",(int)(node->children[i]));
		for (i = 0; i <= node->nkeys; i++)
		{
			bt_dumpNode(node->children[i],key_dump,info);
		}
	}
	else
	{
		printf("    %08x\n",0);
	}

	fflush(stdout);
	return;
}

/*********************************************************************
 *
 * bt_dump -- This function displays the contents of a B-tree.  The
 *            caller passes in a function that displays the contents
 *            of one of the keys stored in the tree.  The calling
 *            protocol for this function is:
 *
 *                       key_dump(key,data,info)
 *                       void *key;
 *                       void *data;
 *                       void *info;
 *
 *            If key_dump is NULL, no action is taken.  This is useful
 *            if the structure of the tree is desired without including
 *            its contents.
 *
 *********************************************************************/

#ifdef __STDC__
void bt_dump(void *ptree, void (*key_dump)(void*,void*,void*), void *info)
#else
void bt_dump(ptree,key_dump,info)
void	*ptree;
void	(*key_dump)();
void	*info;
#endif
{
	BTREE	tree;

	tree = (BTREE) ptree;
	printf("B-tree dump  %x:\n\n",(int)ptree);
	printf("order = %d\n",tree->order);
	printf("capacity = %d\n",tree->capacity);
	printf("contains %d keys\n",tree->root->tsize);
	printf("efficiency is %d per cent\n",
	       (tree->root->tsize*100)/tree->capacity);
	printf("handle at %08x\n",(int)tree);
	printf("root  = %08x\n",(int) tree->root);
	printf("currNode  = %08x\n",(int) tree->currNode);
	printf("nextOk = %d\n",tree->nextOk);
	printf("data = %x\n",(int)(tree->data));
	printf("\n");
	bt_dumpNode(tree->root,key_dump,info);
	return;
}

/******** End of file *********/

