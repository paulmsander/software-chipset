/************************************************************************
 *
 * dlsetup.c -- This file contains routines needed for manipulating
 *              setup structures for doubly-linked lists.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ************************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/************************************************************************
 *
 * dll_setup -- This function creates a doubly-linked list setup structure,
 *              and returns it to the caller.  The parameter is an
 *              optional comparison function (used in case the contents of
 *              the list are sorted).  The setup structure is then passed
 *              to dll_new when a new list is created.
 *
 ************************************************************************/

#ifdef __STDC__
DLL_SETUP dll_setup(int (*comp)(void*,void*),void *data)
#else
DLL_SETUP dll_setup(comp,data)
int	(*comp)();
void	*data;
#endif
{
	SETUP	*retval;

	COVER("dlsetup.c",1);
	retval = (SETUP*) malloc(sizeof(SETUP));
	if (retval != NULL)
	{
		COVER("dlsetup.c",2);
		retval->comp = comp;
		retval->data = data;
	}
	return (DLL_SETUP) retval;
}

/************************************************************************
 *
 * dll_freeSetup -- This function frees a doubly-linked list setup structure.
 *
 ************************************************************************/

#ifdef __STDC__
void dll_freeSetup(DLL_SETUP setup)
#else
void dll_freeSetup(setup)
DLL_SETUP	setup;
#endif
{
	COVER("dlsetup.c",3);
	if (setup != NULL)
	{
		COVER("dlsetup.c",4);
		free(setup);
	}
	return;
}

/************* End of file **************/

