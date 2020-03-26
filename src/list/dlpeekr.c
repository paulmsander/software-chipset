/*********************************************************************
 *
 * dlpeekr.c -- This file contains the dll_peekr function.
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
 * dll_peekr -- This function returns the key and data of the item
 *              at the end of a doubly linked list.  It behaves
 *              similarly to dll_last, except that subsequent calls
 *              to dll_next and dll_prev are not affected.
 *
 *********************************************************************/

#ifdef __STDC__
void *dll_peekr(DL_LIST plist, void**data)
#else
void *dll_peekr(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;
	NODE	*node;

	COVER("dlpeekr.c",1);
	if (plist == NULL)
	{
		COVER("dlpeekr.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (list->last == NULL)
	{
		COVER("dlpeekr.c",3);
		return NULL;
	}

	node = list->last;
	if (data != NULL)
	{
		COVER("dlpeekr.c",4);
		*data = node->data;
	}
	COVER("dlpeekr.c",5);
	return node->key;
}

/**************** End of file ***************/

