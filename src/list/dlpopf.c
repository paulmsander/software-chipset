/***********************************************************************
 *
 * dlpopf.c -- This file contains the dll_popf function.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***********************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/***********************************************************************
 *
 * dll_popf -- This function deletes an item from the front of a
 *             doubly-linked list.
 *
 ***********************************************************************/

#ifdef __STDC__
void *dll_popf(DL_LIST plist, void **data)
#else
void *dll_popf(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;
	NODE	*node;
	void	*retval;

	COVER("dlpopf.c",1);
	if (plist == NULL)
	{
		COVER("dlpopf.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (list->last == NULL)
	{
		COVER("dlpopf.c",3);
		return NULL;
	}

	node = list->last->next;
	retval = node->key;
	if (data != NULL)
	{
		COVER("dlpopf.c",4);
		*data = node->data;
	}
	if (node == list->last)
	{
		COVER("dlpopf.c",5);
		list->last = NULL;
	}
	else
	{
		COVER("dlpopf.c",6);
		dll_unlink(node);
	}
	dll_freeNode(node);
	list->size -= 1;
	dll_touch(list);
	return retval;
}

/*************** End of file ***************/

