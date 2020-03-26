/**********************************************************************
 *
 * dlfirst.c -- This file contains the dll_first function.
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
 * dll_first -- This function returns the first key stored in the list.
 *              If the list is sorted, the key returned is the lowest
 *              key in the lexical order of those keys stored in the list.
 *
 **********************************************************************/

#ifdef __STDC__
void *dll_first(DL_LIST plist, void **data)
#else
void *dll_first(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;

	COVER("dlfirst.c",1);
	list = (LIST*) plist;
	if (list == NULL)
	{
		COVER("dlfirst.c",2);
		return NULL;
	}
	if (list->last == NULL)
	{
		COVER("dlfirst.c",3);
		return NULL;
	}
	COVER("dlfirst.c",4);
	list->current = list->last->next;
	list->nextOk = 0;
	list->changed = 0;
	if (data != NULL)
	{
		COVER("dlfirst.c",5);
		*data = list->current->data;
	}
	COVER("dlfirst.c",6);
	return list->current->key;
}

/************ End of file **************/

