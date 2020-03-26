/******************************************************************
 *
 * dlsearch.c -- This file contains functions used for searching
 *               sorted lists for specified keys.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ******************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/******************************************************************
 *
 * dll_search -- This function searches a sorted list for a specified
 *               key.
 *
 ******************************************************************/

#ifdef __STDC__
void *dll_search(DL_LIST plist, void *target, void **data)
#else
void *dll_search(plist,target,data)
DL_LIST	plist;
void	*target;
void	**data;
#endif
{
	LIST	*list;
	NODE	*node;
	int	res;
	void	*retval;

	COVER("dlsearch.c",1);

	/* Validate parameters */
	if (plist == NULL)
	{
		COVER("dlsearch.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (list->last == NULL)
	{
		COVER("dlsearch.c",3);
		return NULL;
	}
	if (list->comp == NULL)
	{
		COVER("dlsearch.c",4);
		return NULL;
	}

	/* Perform sequential search for target */
	res = dll_locate(list,target,&node);
	if (res < 0)
	{
		/* Target is higher than highest key, overran list */
		COVER("dlsearch.c",5);
		list->current = NULL;
		list->nextOk = 1;
		retval = NULL;
	}
	else if (res > 0)
	{
		/* Target not found, but has a successor */
		COVER("dlsearch.c",6);
		list->current = node;
		list->nextOk = 1;
		retval = NULL;
	}
	else
	{
		/* Target was found */
		COVER("dlsearch.c",7);
		list->current = node;
		list->nextOk = 0;
		if (data != NULL)
		{
			COVER("dlsearch.c",8);
			*data = node->data;
		}
		retval = target;
	}
	list->changed = 0;
	return retval;
}

/*************** End of file **************/

