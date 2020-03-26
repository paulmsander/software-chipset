/******************************************************************
 *
 * dldelutl.c -- This file contains utilities related to deletion
 *               from doubly-linked lists.
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
 * dll_freeNode -- This function frees a list node.
 *
 ******************************************************************/

#ifdef __STDC__
void dll_freeNode(NODE *node)
#else
void dll_freeNode(node)
NODE	*node;
#endif
{
	COVER("dldelutl.c",1);
	free(node);
	return;
}

/******************************************************************
 *
 * dll_unlink -- This function unlinks a node from a list.
 *
 ******************************************************************/

#ifdef __STDC__
void dll_unlink(NODE *node)
#else
void dll_unlink(node)
NODE	*node;
#endif
{
	COVER("dldelutl.c",2);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return;
}

/************** End of file ************/

