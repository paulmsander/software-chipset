/***********************************************************************
 *
 * dldata.c -- This file contains functions used for storing and
 *             retrieving the global list object data field.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***********************************************************************/

#include <stdio.h>
#include "dlpriv.h"

/***********************************************************************
 *
 * dll_data -- This function retrieves the list's global client-defined
 *             data pointer.
 *
 ***********************************************************************/

#ifdef __STDC__
void *dll_data(DL_LIST plist)
#else
void *dll_data(plist)
DL_LIST	plist;
#endif
{
	LIST	*list;

	list = (LIST*) plist;
	if (list == NULL)
	{
		COVER("dldata.c",1);
		return NULL;
	}
	COVER("dldata.c",2);
	return list->data;
}

/***********************************************************************
 *
 * dll_setData -- This function sets the list's global client-defined
 *                data pointer.
 *
 ***********************************************************************/

#ifdef __STDC__
void dll_setData(DL_LIST plist, void *data)
#else
void dll_setData(plist,data)
DL_LIST	plist;
void	*data;
#endif
{
	LIST	*list;

	list = (LIST*) plist;
	if (list != NULL)
	{
		COVER("dldata.c",3);
		list->data = data;
	}
	COVER("dldata.c",4);
	return;
}

/****************** End of file ******************/

