/********************************************************************
 *                                                                  *
 * dkprev.c -- This file contains the dk_prev function.             *
 *                                                                  *
 ********************************************************************/

#include <stdio.h>
#include "dkpriv.h"

/********************************************************************
 *                                                                  *
 * dk_prev -- This function returns the previous item in the last   *
 *            list touched by dk_search, dk_first, dk_last,         *
 *            dk_prev, or dk_prev.  It returns NULL if the last     *
 *            list in the lexical order of the index is overrun.    *
 *                                                                  *
 ********************************************************************/

void *
#ifdef __STD_C__
dk_prev(DK_DUPKEY pindex, void **data)
#else
dk_prev(pindex,data)
DK_DUPKEY	pindex;
void		**data;
#endif
{
	void	*retval;
	DUPKEY	*index;

	retval = NULL;
	if (pindex == NULL)
	{
		COVER("dk_prev.c",1);
		return retval;
	}
	index = (DUPKEY*) pindex;
	if (index->changed)
	{
		COVER("dk_prev.c",2);
		return retval;
	}
	if (index->prev == NULL)
	{
		COVER("dk_prev.c",3);
		return retval;
	}
	if (index->currList != NULL)
	{
		COVER("dk_prev.c",4);
		retval = dll_prev(index->currList,data);
	}
	if (retval == NULL)
	{
		COVER("dk_prev.c",5);
		index->currList = (index->prev)(index->index,NULL);
		if (index->currList != NULL)
		{
			COVER("dk_prev.c",6);
			retval = dll_last(index->currList,data);
		}
	}
	return retval;
}

/**** End of file ****/

