/************************************************************************
 *
 * dlnew.c -- This file contains routines needed for creating
 *            doubly-linked lists.
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
 * dll_new -- Given a SETUP structure, this function creates an empty
 *            doubly-linked list.
 *
 ************************************************************************/

#ifdef __STDC__
DL_LIST dll_new(DLL_SETUP psetup)
#else
DL_LIST dll_new(psetup)
DLL_SETUP	psetup;
#endif
{
	LIST	*retval;
	SETUP	*setup;

	retval = (LIST*) malloc(sizeof(LIST));
	if (retval != NULL)
	{
		COVER("dlnew.c",3);
		retval->last = NULL;
		retval->current = NULL;
		retval->nextOk = 0;
		retval->size = 0;
		retval->changed = 0;
		if (psetup != NULL)
		{
			setup = (SETUP*) psetup;
			retval->data = setup->data;
			retval->comp = setup->comp;
		}
		else
		{
			retval->data = NULL;
			retval->comp = NULL;
		}
	}
	COVER("dlnew.c",4);
	return (DL_LIST) retval;
}

/************* End of file **************/

