/*****************************************************************
 *
 * dlinsert.c -- This file contains functions needed to perform
 *               insertion into sorted doubly-linked lists.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *****************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/*****************************************************************
 *
 * dll_insert -- This function takes as its parameters a doubly-
 *               linked list, a key, and a pointer to arbitrary
 *               data.  It performs a linear search of the list
 *               and inserts a new node in the appropriate place
 *               if the key is not found.  Returns values are:
 *               1 for success, 0 for failure, -1 for duplicate
 *               key.
 *
 *****************************************************************/

#ifdef __STDC__
int dll_insert(DL_LIST plist, void *key, void *data)
#else
int dll_insert(plist,key,data)
DL_LIST	plist;
void	*key;
void	*data;
#endif
{
	LIST	*list;
	NODE	*this;
	NODE	*next;
	int	res;

	COVER("dlinsert.c",1);

	/* Initialization */
	list = (LIST*) plist;

	/* Validate list parameter */
	if (list == NULL)
	{
		COVER("dlinsert.c",2);
		return 0;
	}
	if (list->comp == NULL)
	{
		COVER("dlinsert.c",3);
		return 0;
	}

	/* Validate key parameter */
	if (key == NULL)
	{
		COVER("dlinsert.c",4);
		return 0;
	}

	/* Perform insertion */
	COVER("dlinsert.c",5);
	if (list->last == NULL)
	{
		/* Insert first node into empty list */
		COVER("dlinsert.c",6);
		this = dll_newNode(key,data);
		if (this == NULL) return 0;
		dll_store(this,this);
		list->last = this;
	}
	else
	{
		/* Perform sequential search of list for given key */
		COVER("dlinsert.c",7);
		res = dll_locate(list,key,&this);

		/* Test for duplicate */
		if (res == 0)
		{
			COVER("dlinsert.c",8);
			return -1;
		}

		/* Create new node for new key */
		next = dll_newNode(key,data);
		if (next == NULL)
		{
			COVER("dlinsert.c",9);
			return 0;
		}

		/*
		 * Insert before "this" node if new key is less than "this",
		 * else insert after end of list and update list structure.
		 */
		if (res > 0)
		{
			COVER("dlinsert.c",10);
			dll_store(this->prev,next);
		}
		else
		{
			COVER("dlinsert.c",11);
			dll_store(list->last,next);
			list->last = next;
		}
	}
	COVER("dlinsert.c",12);
	list->size += 1;
	dll_touch(list);
	return 1;
}

/*********** End of file ***********/

