/**********************************************************************
 *
 * dllast.c -- This file contains the dll_last function.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 **********************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/**********************************************************************
 *
 * dll_last-- This function returns the last key stored in the list.
 *            If the list is sorted, the key returned is the highest
 *            key in the lexical order of those keys stored in the list.
 *
 **********************************************************************/

#ifdef __STDC__
void *dll_last(DL_LIST plist, void **data)
#else
void *dll_last(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;

	COVER("dllast.c",1);
	list = (LIST*) plist;
	if (list == NULL)
	{
		COVER("dllast.c",2);
		return NULL;
	}
	if (list->last == NULL)
	{
		COVER("dllast.c",3);
		return NULL;
	}
	COVER("dllast.c",4);
	list->current = list->last;
	list->nextOk = 0;
	list->changed = 0;
	if (data != NULL)
	{
		COVER("dllast.c",5);
		*data = list->current->data;
	}
	return list->current->key;
}

/************ End of file **************/

