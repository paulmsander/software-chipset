/***********************************************************************
 *
 * dkdellast.c -- This file contains code that deletes the last item
 *                 that matches a given key.  Here, "last" is the "last"
 *                 with respect to traversal with dk_first/dk_next or
 *                 dk_traverse.
 *
 ***********************************************************************/

#include <stdio.h>
#include <dlist.h>
#include "dkpriv.h"


/***********************************************************************
 *
 * dk_delLast -- This function removes the last item from the index
 *                that matches the specified key, or NULL in the event
 *                of an error.
 *
 ***********************************************************************/

#ifdef __STDC__
void *dk_delLast(DK_DUPKEY pindex, void *key, void **data, int *safe)
#else
void *dk_delLast(pindex, key, data, safe)
DK_DUPKEY	pindex;
void		*key;
void		**data;
int		*safe;
#endif
{
	DUPKEY		*index;
	void		*retval;
	DK_LISTDATA	listData;
	DK_LISTDATA	*ldata;
	DL_LIST		list;
	void		*next;

	/* Verify parameters */
	if (pindex == NULL)
	{
		COVER("dkdellast.c",1);
		return NULL;
	}

	/* Misc. initialization */
	COVER("dkdellast.c",2);
	retval = NULL;
	index = (DUPKEY*) pindex;

	/* Build composite key for search */
	listData.key = key;
	listData.index = index;
	dll_setData(index->list,(void*)&listData);

	/* Search for key */
	list = (index->search)(index->index,index->list,NULL);
	if (list != NULL)
	{
		COVER("dkdellast.c",3);
		/* Got it, pop it off the rear of the list */
		retval = dll_popr(list,data);
		if (retval != NULL)
		{
			COVER("dkdellast.c",4);
			next = dll_peekf(list,NULL);
			if (next == NULL)
			{
				COVER("dkdellast.c",5);
				/*
				 * This was last item in the list, delete the
				 * list and tell the caller to free the key.
				 */
				*safe = 1;

				/*
				 * This will succeed, because a search succeeded
				 * already.  But if it fails, we must return the
				 * key and data anyway, which indicates no error
				 * even if one occurred.
				 */
				(index->delete)(index->index,index->list,NULL);

				/* Clean up the list */
				ldata = (DK_LISTDATA*) dll_data(list);
				free(ldata);
				dll_destroy(list,NULL,NULL,NULL);
			}
			else
			{
				COVER("dkdellast.c",6);
				*safe = (index->oneKey == DK_SEPARATE);
			}
		}
		COVER("dkdellast.c",7);
	}
	COVER("dkdellast.c",8);
	index->changed = 1;
	dll_setData(index->list,NULL);
	return retval;
}

/*** End of File ***/

