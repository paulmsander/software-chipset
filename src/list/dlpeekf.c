/*********************************************************************
 *
 * dlpeekf.c -- This file contains the dll_peekf function.
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
 * dll_peekf -- This function returns the key and data of the item
 *              at the head of a doubly linked list.  It behaves
 *              similarly to dll_first, except that subsequent calls
 *              to dll_next and dll_prev are not affected.
 *
 *********************************************************************/

#ifdef __STDC__
void *dll_peekf(DL_LIST plist, void **data)
#else
void *dll_peekf(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;
	NODE	*node;

	COVER("dlpeekf.c",1);
	if (plist == NULL)
	{
		COVER("dlpeekf.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (list->last == NULL)
	{
		COVER("dlpeekf.c",3);
		return NULL;
	}

	node = list->last->next;
	if (data != NULL)
	{
		COVER("dlpeekf.c",4);
		*data = node->data;
	}
	COVER("dlpeekf.c",5);
	return node->key;
}

/**************** End of file ***************/

