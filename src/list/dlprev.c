/***********************************************************************
 *
 * dlprev.c -- This file contains the dll_prev function.
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
 * dll_prev -- This function returns the previous key stored in the list.
 *             If the list is sorted, this key is the next lowest in
 *             the lexical order of keys stored in the tree.
 *
 ***********************************************************************/

#ifdef __STDC__
void *dll_prev(DL_LIST plist, void **data)
#else
void *dll_prev(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;

	COVER("dlprev.c",1);

	/* Validate parameters */
	list = (LIST*) plist;
	if (list == NULL)
	{
		COVER("dlprev.c",2);
		return NULL;
	}
	if (list->last == NULL)
	{
		COVER("dlprev.c",3);
		return NULL;
	}

	/* Require a search, first, or next */
	if (list->changed)
	{
		COVER("dlprev.c",4);
		return NULL;
	}

	/* Last search was for a key that was beyond the end of the list */
	if (list->current == NULL)
	{
		COVER("dlprev.c",5);
		return dll_last(plist,data);
	}

	/* Indicate error if list is overrun */
	if (list->current == list->last->next)
	{
		COVER("dlprev.c",6);
		list->nextOk = 1;
		return NULL;
	}

	/* Return next item in list */
	COVER("dlprev.c",7);
	list->current = list->current->prev;
	list->nextOk = 0;
	if (data != NULL)
	{
		COVER("dlprev.c",8);
		*data = list->current->data;
	}
	return list->current->key;
}

/************ End of file ************/

