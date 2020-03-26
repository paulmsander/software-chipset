/*******************************************************************
 *
 * dlpeek.c -- This file contains the dll_peek function.
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
 * dll_peek -- This function returns the key and data of the item
 *             at the specified end of a doubly-linked list.  Subsequent
 *             calls to dll_next and dll_prev are not affected.
 *
 *******************************************************************/

#ifdef __STDC__
void *dll_peek(DL_LIST plist, int where, void **data)
#else
void *dll_peek(plist,where,data)
DL_LIST	plist;
int	where;
void	**data;
#endif
{
	void	*retval;

	switch (where)
	{
case DLL_FRONT:
		COVER("dlpeek.c",1);
		retval = dll_peekf(plist,data);
		break;

case DLL_BACK:
		COVER("dlpeek.c",2);
		retval = dll_peekr(plist,data);
		break;

default:
		COVER("dlpeek.c",3);
		retval = NULL;
		break;
	}
	return retval;
}

/*************** End of file **************/

