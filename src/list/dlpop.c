/*******************************************************************
 *
 * dlpop.c -- This file contains the dll_pop function.
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
 * dll_pop -- This function removes an item from a doubly-linked
 *            list at a specified end.
 *
 *******************************************************************/

#ifdef __STDC__
void *dll_pop(DL_LIST plist, int where, void **data)
#else
void *dll_pop(plist,where,data)
DL_LIST	plist;
int	where;
void	**data;
#endif
{
	void	*retval;

	switch (where)
	{
case DLL_FRONT:
		COVER("dlpop.c",1);
		retval = dll_popf(plist,data);
		break;

case DLL_BACK:
		COVER("dlpop.c",2);
		retval = dll_popr(plist,data);
		break;

default:
		COVER("dlpop.c",3);
		retval = NULL;
		break;
	}
	return retval;
}

/*************** End of file **************/

