/***********************************************************************
 *                                                                     *
 * dksearch.c -- This file contains the dk_search function.            *
 *                                                                     *
 ***********************************************************************/

#include <stdio.h>
#include "dkpriv.h"

/***********************************************************************
 *                                                                     *
 * dk_search -- This function searches the duplicate key index for the *
 *              specified key.  If the key is found, it is returned to *
 *              caller along with the data pointer stored with it.  If *
 *              the key is not found, NULL is returned.  In any case,  *
 *              the index is left in a state in which dk_next and      *
 *              dk_prev do the expected thing.                         *
 *                                                                     *
 ***********************************************************************/

#ifdef __STD_C__
void *dk_search(DK_DUPKEY pindex, void *target, void **data)
#else
void *dk_search(pindex,target,data)
DK_DUPKEY	pindex;
void		*target;
void		**data;
#endif
{
	DUPKEY		*index;
	void		*retval;
	DK_LISTDATA	listData;

	COVER("dksearch.c",1);
	retval = NULL;
	if (pindex != NULL)
	{
		COVER("dksearch.c",2);
		index = (DUPKEY*) pindex;
		listData.key = target;
		listData.index = index;
		dll_setData(index->list,(void*)&listData);
		index->currList = (index->search)(index->index,
		                   index->list,NULL);
		if (index->currList != NULL)
		{
			COVER("dksearch.c",3);
			retval = dll_first(index->currList,data);
		}
		index->changed = 0;
		dll_setData(index->list,NULL);
	}
	return retval;
}

/**** End of File ****/

