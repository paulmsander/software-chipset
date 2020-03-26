/*******************************************************************
 *
 * dlpush.c -- This file contains the dll_push function.
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
 * dll_push -- This function pushes an item onto a doubly-linked
 *             list at a specified end.
 *
 *******************************************************************/

#ifdef __STDC__
void *dll_push(DL_LIST plist, int where, void *key, void *data)
#else
void *dll_push(plist,where,key,data)
DL_LIST	plist;
int	where;
void	*key;
void	*data;
#endif
{
	switch (where)
	{
case DLL_FRONT:
		COVER("dlpush.c",1);
		return dll_pushf(plist,key,data);

case DLL_BACK:
		COVER("dlpush.c",2);
		return dll_pushr(plist,key,data);

default:
		COVER("dlpush.c",3);
		return NULL;
	}
}

/*************** End of file **************/

