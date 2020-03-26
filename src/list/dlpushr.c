/*********************************************************************
 *
 * dlpushr.c -- This file contains the dll_pushr function.
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
 * dll_pushr -- This function pushes an item onto the rear of an
 *              unordered doubly-linked list.
 *
 *********************************************************************/

#ifdef __STDC__
void *dll_pushr(DL_LIST plist, void *key, void *data)
#else
void *dll_pushr(plist,key,data)
DL_LIST	plist;
void	*key;
void	*data;
#endif
{
	LIST	*list;
	NODE	*node;

	COVER("dlpushr.c",1);
	if (plist == NULL)
	{
		COVER("dlpushr.c",1);
		return NULL;
	}
	list = (LIST*) plist;

	node = dll_newNode(key,data);
	if (node == NULL)
	{
		COVER("dlpushr.c",2);
		return NULL;
	}
	if (list->last != NULL)
	{
		COVER("dlpushr.c",3);
		dll_store(list->last,node);
	}
	else
	{
		COVER("dlpushr.c",4);
		node->next = node;
		node->prev = node;
	}
	list->last = node;
	list->size += 1;
	dll_touch(list);
	return key;
}

/*************** End of file ****************/

