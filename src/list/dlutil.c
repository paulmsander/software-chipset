/********************************************************************
 *
 * dlutil.c -- This file contains general-purpose utility functions
 *             needed by the doubly-linked list implementation.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ********************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/********************************************************************
 *
 * dll_locate -- This function performs a sequential search of a
 *               doubly-linked list for a specified key.  This function
 *               assumes the list is sorted.
 *
 ********************************************************************/

#ifdef __STDC__
int dll_locate(LIST *list, void *key, NODE **node)
#else
int dll_locate(list,key,node)
LIST	*list;
void	*key;
NODE	**node;
#endif
{
	int	res;
	NODE	*this;

	COVER("dlutil.c",1);
	this = list->last->next;
	res = (*list->comp)(this->key,key);
	while ((res < 0) && (this != list->last))
	{
		COVER("dlutil.c",2);
		this = this->next;
		res = (*list->comp)(this->key,key);
	}
	COVER("dlutil.c",3);
	*node = this;
	return res;
}

/********************************************************************
 *
 * dll_touch -- This function marks a list as having been modified.
 *              This affects the behavior of dll_next and dll_prev.
 *
 ********************************************************************/

#ifdef __STDC__
void dll_touch(LIST *list)
#else
void dll_touch(list)
LIST	*list;
#endif
{
	COVER("dlutil.c",4);
	list->current = NULL;
	list->nextOk = 0;
	list->changed = 1;
	return;
}

/************** End of file *************/

