/***********************************************************************
 *
 * dkdata.c -- This file contains functions to access and modify a
 *             a user-defined data structure that can be stored with
 *             a duplicate key index.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***********************************************************************/

#include <stdio.h>
#include "dkpriv.h"

/***********************************************************************
 *
 * dk_data -- Given a duplicate key index, returns a pointer to a
 *            user-defined structure.  This pointer can be set by dk_new(),
 *            or with dk_setData().
 *
 ***********************************************************************/

#ifdef __STDC__
void	*dk_data(void *pindex)
#else
void	*dk_data(pindex)
void	*pindex;
#endif
{
	DUPKEY	*index;

	if (pindex == NULL)
	{
		COVER("dkdata.c",1);
		return NULL;
	}
	COVER("dkdata.c",2);
	index = (DUPKEY*) pindex;
	return index->data;
}

/***********************************************************************
 *
 * dk_setData -- This function modifies a pointer to a user-defined
 *               structure that is kept with the duplicate key index.
 *
 ***********************************************************************/

#ifdef __STDC__
void dk_setData(void *pindex, void *data)
#else
void dk_setData(pindex,data)
void	*pindex;
void	*data;
#endif
{
	DUPKEY	*index;

	if (pindex != NULL)
	{
		COVER("dkdata.c",3);
		index = (DUPKEY*) pindex;
		index->data = data;
	}
	COVER("dkdata.c",4);
	return;
}

/************ End of file *************/

