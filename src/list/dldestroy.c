/************************************************************************
 *
 * dldestroy.c -- This file contains routines needed for destroying
 *                doubly-linked lists.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "dlpriv.h"

/************************************************************************
 *
 * dll_destroy -- This function destroys a doubly-linked list.  It is
 *                passed the doomed list, along with pointers to functions
 *                that destroy the keys and client-defined data stored in
 *                each node in the list.  An additional parameter is
 *                passed along to the callback functions without modification.
 *                The freeData function is always called before the freeKey
 *                function.  Either or both of these may be NULL, in which
 *                no action is taken for that item.  The interfaces for
 *                freeKey and freeData are the same, which is the following:
 *
 *                void freeMe(keyOrData,info)
 *                void *keyOrData;
 *                void *info;
 *
 ************************************************************************/

#ifdef __STDC__
void dll_destroy(DL_LIST plist, void (*freeKey)(void*,void*),
                 void(*freeData)(void*,void*), void *info)
#else
void dll_destroy(plist,freeKey,freeData,info)
DL_LIST	plist;
void	(*freeKey)();
void	(*freeData)();
void	*info;
#endif
{
	LIST	*list;
	NODE	*this;
	NODE	*next;

	COVER("dldestroy.c",1);
	list = (LIST*) plist;
	if (list != NULL)
	{
		COVER("dldestroy.c",2);
		if (list->last != NULL)
		{
			COVER("dldestroy.c",3);
			this = list->last->next;
			while (this != list->last)
			{
				COVER("dldestroy.c",4);
				next = this->next;
				if (freeData != NULL)
				{
					COVER("dldestroy.c",5);
					(*freeData)(this->data,info);
				}
				if (freeKey != NULL)
				{
					COVER("dldestroy.c",6);
					(*freeKey)(this->key,info);
				}
				COVER("dldestroy.c",7);
				free(this);
				this = next;
			}
			if (freeData != NULL)
			{
				COVER("dldestroy.c",8);
				(*freeData)(this->data,info);
			}
			if (freeKey != NULL)
			{
				COVER("dldestroy.c",9);
				(*freeKey)(this->key,info);
			}
			COVER("dldestroy.c",10);
			free(this);
		}
		COVER("dldestroy.c",11);
		free(list);
	}
	COVER("dldestroy.c",12);
	return;
}

/************* End of file **************/

