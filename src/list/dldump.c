/***********************************************************************
 *
 * dldump.c -- This file contains debugging code to dump the contents
 *             of a doubly-linked list.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***********************************************************************/

#include <stdio.h>
#include "dlpriv.h"

#ifdef __STDC__
void dll_dump(DL_LIST plist,void (*key_dump)(void*,void*,void*),void *info)
#else
void dll_dump(plist,key_dump,info)
DL_LIST	plist;
void	(*key_dump)();
void	*info;
#endif
{
	LIST	*list;
	NODE	*this;

	if (plist == NULL)
	{
		printf("ERROR:  Trying to dump null list\n");
		return;
	}

	list = (LIST*) plist;
	printf("List handle located at %08lx\n",(unsigned long) list);
	printf("last = %08lx\n",(unsigned long) list->last);
	printf("current = %08lx\n",(unsigned long) list->current);
	printf("data = %08lx\n", (unsigned long) list->data);
	printf("nextOk = %d\n", list->nextOk);
	printf("size = %d\n", list->size);
	printf("changed = %d\n", list->changed);
	printf("-----------\n");
	if (list->last != NULL)
	{
		this = list->last->next;
		do
		{
			printf("Node at %08lx:\n",(unsigned long) this);
			printf("  next = %08lx\n",(unsigned long) this->next);
			printf("  prev = %08lx\n",(unsigned long) this->prev);
			if (key_dump != NULL)
			{
				key_dump(this->key,this->data,info);
			}
			printf("\n");
			this = this->next;
		} while (this != list->last->next);
	}
	return;
}

/************* End of file ************/

