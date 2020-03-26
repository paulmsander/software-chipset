/*********************************************************************
 *
 * dlrankutl.c -- This file contains utility functions for accessing
 *                the contents of a list by rank.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *********************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/*********************************************************************
 *
 * dll_locRank -- This function locates a node in a list by rank.
 *
 *********************************************************************/

#ifdef __STDC__
NODE *dll_locRank(LIST *list, int rank)
#else
NODE *dll_locRank(list,rank)
LIST	*list;
int	rank;
#endif
{
	NODE	*node;

	COVER("dlrankutl.c",1);
	node = list->last->next;
	while (rank > 0)
	{
		COVER("dlrankutl.c",2);
		node = node->next;
		rank--;
	}
	return node;
}

/**************** End of file ***************/

