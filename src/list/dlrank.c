/************************************************************************
 *
 * dlrank.c -- This file contains the dll_rank function.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ************************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/************************************************************************
 *
 * dll_rank -- This function returns the specified item stored in the list,
 *             as specified by rank .
 *
 ************************************************************************/

#ifdef __STDC__
void *dll_rank(DL_LIST plist, int rank, void **data)
#else
void *dll_rank(plist,rank,data)
DL_LIST	plist;
int	rank;
void	**data;
#endif
{
	LIST	*list;
	NODE	*node;
	void	*retval;

	COVER("dlrank.c",1);
	if (plist == NULL)
	{
		COVER("dlrank.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (rank < 0)
	{
		COVER("dlrank.c",3);
		return NULL;
	}
	if (rank >= list->size)
	{
		COVER("dlrank.c",4);
		return NULL;
	}

	node = dll_locRank(list,rank);
	list->nextOk = 0;
	list->current = node;
	list->changed = 0;
	if (node != NULL)
	{
		COVER("dlrank.c",5);
		if (data != NULL) *data = node->data;
		retval = node->key;
	}
	else
	{
		/*
		 * This code is never reached because earlier tests on rank
		 * insure that a node is found.
		 */
		COVER("dlrank.c",6);
		retval = NULL;
	}
	return retval;
}

/************ End of file ***********/

