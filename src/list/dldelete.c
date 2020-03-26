/*******************************************************************
 *
 * dldelete.c -- This file contains functions to delete from a
 *               sorted list.
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
 * dll_delete -- This function deletes a node by key from a sorted
 *               list.
 *
 *******************************************************************/

#ifdef __STDC__
void *dll_delete(DL_LIST plist, void *key, void **data)
#else
void *dll_delete(plist,key,data)
DL_LIST	plist;
void	*key;
void	**data;
#endif
{
	LIST	*list;
	NODE	*this;
	int	res;
	void	*retval;

	COVER("dldelete.c",1);

	/* Validate list parameter */
	if (plist == NULL)
	{
		COVER("dldelete.c",2);
		return NULL;
	}
	list = (LIST*) plist;
	if (list->last == NULL)
	{
		COVER("dldelete.c",3);
		return NULL;
	}
	if (list->comp == NULL)
	{
		COVER("dldelete.c",4);
		return NULL;
	}

	/* Perform sequential search for node */
	COVER("dldelete.c",5);
	res = dll_locate(list,key,&this);

	/* Unlink and free node if found */
	if (res == 0)
	{
		COVER("dldelete.c",6);
		retval = this->key;
		if (data != NULL)
		{
			COVER("dldelete.c",7);
			*data = this->data;
		}
		COVER("dldelete.c",8);
		dll_unlink(this);

		/* Special consideration if this is the tail of the list */
		if (this == list->last)
		{
			if (this->prev != this)
			{
				COVER("dldelete.c",9);
				list->last = this->prev;
			}
			else
			{
				COVER("dldelete.c",10);
				list->last = NULL;
			}
		}
		COVER("dldelete.c",11);
		dll_freeNode(this);
		list->size -= 1;
		dll_touch(list);
	}
	else
	{
		COVER("dldelete.c",12);
		retval = NULL;
	}
	COVER("dldelete.c",13);
	return retval;
}

/************** End of file **************/

