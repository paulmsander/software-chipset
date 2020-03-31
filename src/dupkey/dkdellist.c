/***********************************************************************
 *
 * dkdellist.c -- This file contains code that deletes all items with
 *                that match a specified key.
 *
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <dlist.h>
#include "dkpriv.h"


/***********************************************************************
 *
 * dk_delList -- This function removes all items that have the specified
 *               key, and returns a doubly-linked list containing them
 *               all.
 *
 *               The global data pointer in the returned list is
 *               set to NULL if each data record has its own copy of
 *               the key; when the list is destroyed, the free_key
 *               parameter should be passed an appropriate value.
 *               The global data pointer in the returned list is
 *               set to point to the key if the key is shared by all
 *               of the data records; when the list is destroyed, the
 *               global data pointer should be saved, then dll_destroy
 *               is called (passing NULL as the free_key parameter),
 *               then the key (pointed to by the saved global data
 *               pointer) is freed.
 *
 ***********************************************************************/

#ifdef __STDC__
DL_LIST dk_delList(DK_DUPKEY pindex, void *key)
#else
DL_LIST dk_delList(pindex, key)
DK_DUPKEY	pindex;
void		*key;
#endif
{
	DUPKEY		*index;
	DK_LISTDATA	listData;
	DK_LISTDATA	*ldata;
	DL_LIST		list;

	/* Verify parameters */
	if (pindex == NULL)
	{
		COVER("dkdellist.c",1);
		return NULL;
	}

	/* Misc. initialization */
	COVER("dkdellist.c",2);
	index = (DUPKEY*) pindex;

	/* Build composite key for search */
	listData.key = key;
	listData.index = index;
	dll_setData(index->list,(void*)&listData);

	/* Search for key */
	list = (DL_LIST) (index->delete)(index->index,index->list,NULL);
	if (list != NULL)
	{
		COVER("dkdellist.c",3);
		ldata = (DK_LISTDATA*) dll_data(list);
		if (index->oneKey == DK_SINGLE)
		{
			COVER("dkdellist.c",4);
			dll_setData(list,ldata->key);
		}
		else
		{
			COVER("dkdellist.c",5);
			dll_setData(list,NULL);
		}
		free(ldata);
	}
	COVER("dkdellist.c",6);
	index->changed = 1;
	dll_setData(index->list,NULL);
	return list;
}

/*** End of File ***/

