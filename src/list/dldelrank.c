/*******************************************************************
 *
 * dldelrank.c -- This file contains functions to delete from a
 *                list, given an item's rank.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *******************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/*******************************************************************
 *
 * dll_delRank -- This function deletes a node by rank from a list.
 *
 *******************************************************************/

#ifdef __STDC__
void *dll_delRank(DL_LIST plist, int rank, void **data)
#else
void *dll_delRank(plist,rank,data)
DL_LIST	plist;
int	rank;
void	**data;
#endif
{
	LIST	*list;
	NODE	*this;
	int	res;
	void	*retval;

	COVER("dldelrank.c",1);

	/* Validate list parameter */
	if (plist == NULL)
	{
		COVER("dldelrank.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (list->last == NULL)
	{
		COVER("dldelrank.c",3);
		return NULL;
	}
	if (rank < 0)
	{
		COVER("dldelrank.c",4);
		return NULL;
	}
	if (rank >= list->size)
	{
		COVER("dldelrank.c",5);
		return NULL;
	}

	/* Find the node with the given rank */
	COVER("dldelrank.c",6);
	this = dll_locRank(list,rank);

	/* Unlink and free node if found */
	if (this != NULL)
	{
		COVER("dldelrank.c",7);
		retval = this->key;
		if (data != NULL)
		{
			COVER("dldelrank.c",8);
			*data = this->data;
		}
		dll_unlink(this);

		/* Special consideration if this is the tail of the list */
		if (this == list->last)
		{
			if (this->prev != this)
			{
				COVER("dldelrank.c",9);
				list->last = this->prev;
			}
			else
			{
				COVER("dldelrank.c",10);
				list->last = NULL;
			}
		}
		COVER("dldelrank.c",11);
		dll_freeNode(this);
		list->size -= 1;
		dll_touch(list);
	}
	else
	{
		/*
		 * Earlier tests on rank prevent this code from being
		 * reached.
		 */
		COVER("dldelrank.c",12);
		retval = NULL;
	}
	return retval;
}

/************** End of file **************/

