/***********************************************************************
 *
 * dlnext.c -- This file contains the dll_next function.
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
 * dll_next -- This function returns the next key stored in the list.
 *             If the list is sorted, this key is the next highest in
 *             the lexical order of keys stored in the tree.
 *
 ***********************************************************************/

#ifdef __STDC__
void *dll_next(DL_LIST plist, void **data)
#else
void *dll_next(plist,data)
DL_LIST	plist;
void	**data;
#endif
{
	LIST	*list;

	COVER("dlnext.c",1);

	/* Validate parameters */
	list = (LIST*) plist;
	if (list == NULL)
	{
		COVER("dlnext.c",2);
		return NULL;
	}
	if (list->last == NULL)
	{
		COVER("dlnext.c",3);
		return NULL;
	}

	/* Require a search, first, or next */
	if (list->changed)
	{
		COVER("dlnext.c",4);
		return NULL;
	}

	/* If no search was done, return first item in list */
	if ((list->current == NULL) && (! list->nextOk))
	{
		/*
		 * This is never reached.  This condition is met only after
		 * the linked list has been changed, in which case the test
		 * above causes this function to fail.
		 */
		COVER("dlnext.c",5);
		return dll_first(plist,data);
	}

	/* Indicate error if list is overrun */
	if (((list->current == list->last) && (! list->nextOk)) ||
	    (list->current == NULL))
	{
		COVER("dlnext.c",6);
		list->current = NULL;
		list->nextOk = 1;
		return NULL;
	}
	COVER("dlnext.c",7);

	/* Return next item in list */
	if (! list->nextOk)
	{
		COVER("dlnext.c",8);
		list->current = list->current->next;
	}
	COVER("dlnext.c",9);
	list->nextOk = 0;
	if (data != NULL)
	{
		COVER("dlnext.c",10);
		*data = list->current->data;
	}
	return list->current->key;
}

/************ End of file ************/

