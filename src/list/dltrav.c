/******************************************************************
 *
 * dltrav.c -- This file contains functions used for traversing
 *             linked lists.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ******************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/******************************************************************
 *
 * dll_traverse -- This function traverses a linked list, calling
 *                 a client-provided visitation function once for
 *                 each node stored there.  If the list is sorted,
 *                 the nodes are visited in the lexical order of
 *                 the keys.  If the list is unsorted, the nodes
 *                 are visited in the order in which dll_first and
 *                 dll_next visits them.
 *
 *                 The interface for the visitation function follows:
 *
 *			void fn(key,parms,data)
 *			void	*key;
 *			void	*parms;
 *			void	*data;
 *
 *                 where "key" is the key stored in the node, "parms"
 *                 is an arbitrary client-specified pointer passed
 *                 to dll_traverse, and "data" is the data pointer
 *                 stored in the node.
 *
 ******************************************************************/

#ifdef __STDC__
void	dll_traverse(DL_LIST plist, void (*fn)(void*,void*,void*), void *parms)
#else
void	dll_traverse(plist,fn,parms)
DL_LIST	plist;
void	(*fn)();
void	*parms;
#endif
{
	LIST	*list;
	NODE	*node;

	COVER("dltrav.c",1);
	list = (LIST*) plist;
	if (list == NULL)
	{
		COVER("dltrav.c",2);
		return;
	}
	if (list->last == NULL)
	{
		COVER("dltrav.c",3);
		return;
	}
	if (fn == NULL)
	{
		COVER("dltrav.c",4);
		return;
	}

	node = list->last->next;
	do
	{
		COVER("dltrav.c",5);
		(*fn)(node->key,parms,node->data);
		node = node->next;
	} while (node != list->last->next);
	COVER("dltrav.c",6);
	return;
}

/************** End of file **************/

