/***********************************************************************
 *                                                                     *
 * dklast.c -- This file contains the dk_last function.                *
 *                                                                     *
 ***********************************************************************/

#include <stdio.h>
#include "dkpriv.h"

/***********************************************************************
 *                                                                     *
 * dk_last -- This function returns the last data item stored with     *
 *            the key that falls last in the lexical order of the      *
 *            index.                                                   *
 *                                                                     *
 ***********************************************************************/

#ifdef __STD_C__
void *dk_last(DK_DUPKEY pindex, void **data)
#else
void *dk_last(pindex,data)
DK_DUPKEY	pindex;
void		**data;
#endif
{
	DUPKEY	*index;
	void	*retval;

	COVER("dklast.c",1);
	retval = NULL;
	if (pindex != NULL)
	{
		COVER("dklast.c",2);
		index = (DUPKEY*) pindex;
		if (index->last != NULL)
		{
			COVER("dklast.c",3);
			index->currList = (index->last)(index->index,NULL);
			if (index->currList != NULL)
			{
				COVER("dklast.c",4);
				retval = dll_last(index->currList,data);
			}
			index->changed = 0;
		}
	}
	return retval;
}

/**** End of File ****/

