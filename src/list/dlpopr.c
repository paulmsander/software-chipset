/***********************************************************************
 *
 * dlpopr.c -- This file contains the dll_popr function.
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
 * dll_popr -- This function deletes an item from the rear of a
 *             doubly-linked list.
 *
 ***********************************************************************/

#ifdef __STDC__
void *dll_popr(DL_LIST plist, void **data)
#else
void *dll_popr(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;
	NODE	*node;
	void	*retval;

	COVER("dlpopr.c",1);
	if (plist == NULL)
	{
		COVER("dlpopr.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (list->last == NULL)
	{
		COVER("dlpopr.c",3);
		return NULL;
	}

	COVER("dlpopr.c",4);
	list->last = list->last->prev;
	return dll_popf(plist,data);
}

/*************** End of file ***************/

