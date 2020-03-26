/********************************************************************
 *                                                                  *
 * dknext.c -- This file contains the dk_next function.             *
 *                                                                  *
 ********************************************************************/

#include <stdio.h>
#include "dkpriv.h"

/********************************************************************
 *                                                                  *
 * dk_next -- This function returns the next item in the last       *
 *            list touched by dk_search, dk_first, dk_last,         *
 *            dk_next, or dk_prev.  It returns NULL if the last     *
 *            list in the lexical order of the index is overrun.    *
 *                                                                  *
 ********************************************************************/

void *
#ifdef __STD_C__
dk_next(DK_DUPKEY pindex, void **data)
#else
dk_next(pindex,data)
DK_DUPKEY	pindex;
void		**data;
#endif
{
	void	*retval;
	DUPKEY	*index;

	retval = NULL;
	if (pindex == NULL)
	{
		COVER("dk_next.c",1);
		return retval;
	}
	index = (DUPKEY*) pindex;
	if (index->changed)
	{
		COVER("dk_next.c",2);
		return retval;
	}
	if (index->next == NULL)
	{
		COVER("dk_next.c",3);
		return retval;
	}
	if (index->currList != NULL)
	{
		COVER("dk_next.c",4);
		retval = dll_next(index->currList,data);
	}
	if (retval == NULL)
	{
		COVER("dk_next.c",5);
		index->currList = (index->next)(index->index,NULL);
		if (index->currList != NULL)
		{
			COVER("dk_next.c",6);
			retval = dll_first(index->currList,data);
		}
	}
	return retval;
}

/**** End of file ****/

