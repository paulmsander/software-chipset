/***********************************************************************
 *                                                                     *
 * dkfirst.c -- This file contains the dk_first function.              *
 *                                                                     *
 ***********************************************************************/

#include <stdio.h>
#include "dkpriv.h"

/***********************************************************************
 *                                                                     *
 * dk_first -- This function returns the first data item stored with   *
 *             the key that falls first in the lexical order of the    *
 *             index.                                                  *
 *                                                                     *
 ***********************************************************************/

#ifdef __STD_C__
void *dk_first(DK_DUPKEY pindex, void **data)
#else
void *dk_first(pindex,data)
DK_DUPKEY	pindex;
void		**data;
#endif
{
	DUPKEY	*index;
	void	*retval;

	COVER("dkfirst.c",1);
	retval = NULL;
	if (pindex != NULL)
	{
		COVER("dkfirst.c",2);
		index = (DUPKEY*) pindex;
		if (index->first != NULL)
		{
			COVER("dkfirst.c",3);
			index->currList = (index->first)(index->index,NULL);
			if (index->currList != NULL)
			{
				COVER("dkfirst.c",4);
				retval = dll_first(index->currList,data);
			}
			index->changed = 0;
		}
	}
	return retval;
}

/**** End of File ****/

