/*****************************************************************
 *
 * dlinsutl.c -- This file contains utility functions used in
 *               inserting nodes into a list.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "dlpriv.h"


/*****************************************************************
 *
 * dll_newNode -- This function creates and initializes a new node
 *                for a linked list.  The function's parameters
 *                are a pointer to a client-defined key and
 *                a pointer to arbitrary data.  The return value
 *                is a pointer to the new node, or NULL in case of
 *                error.
 *
 *****************************************************************/

#ifdef __STDC__
NODE *dll_newNode(void *key, void *data)
#else
NODE *dll_newNode(key,data)
void	*key;
void	*data;
#endif
{
	NODE	*retval;

	COVER("dlinsutl.c",1);
	retval = (NODE*) malloc(sizeof(NODE));
	if (retval != NULL)
	{
		COVER("dlinsutl.c",2);
		retval->key = key;
		retval->data = data;
		retval->next = NULL;
		retval->prev = NULL;
	}
	COVER("dlinsutl.c",3);
	return retval;
}

/*****************************************************************
 *
 * dll_store -- This function inserts node2 into the linked list
 *              after node1.  Node2 is assumed not to be linked
 *              into the list.
 *
 *****************************************************************/

#ifdef __STDC__
void dll_store(NODE *node1, NODE *node2)
#else
void dll_store(node1,node2)
NODE	*node1;
NODE	*node2;
#endif
{
	COVER("dlinsutl.c",4);
	node2->prev = node1;
	node2->next = node1->next;
	node1->next = node2;
	node2->next->prev = node2;
	return;
}

/************* End of file **************/

