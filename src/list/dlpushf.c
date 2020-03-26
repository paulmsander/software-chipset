/*********************************************************************
 *
 * dlpushf.c -- This file contains the dll_pushf function.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *********************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/*********************************************************************
 *
 * dll_pushf -- This function pushes an item onto the front of an
 *              unordered doubly-linked list.
 *
 *********************************************************************/

#ifdef __STDC__
void *dll_pushf(DL_LIST plist, void *key, void *data)
#else
void *dll_pushf(plist,key,data)
DL_LIST	plist;
void	*key;
void	*data;
#endif
{
	LIST	*list;
	NODE	*node;

	COVER("dlpushf.c",1);
	if (plist == NULL)
	{
		COVER("dlpushf.c",2);
		return NULL;
	}
	list = (LIST*) plist;

	node = dll_newNode(key,data);
	if (node == NULL)
	{
		COVER("dlpushf.c",3);
		return NULL;
	}

	if (list->last != NULL)
	{
		COVER("dlpushf.c",4);
		dll_store(list->last,node);
	}
	else
	{
		COVER("dlpushf.c",5);
		list->last = node;
		node->next = node;
		node->prev = node;
	}
	list->size += 1;
	dll_touch(list);
	return key;
}

/*************** End of file ****************/

