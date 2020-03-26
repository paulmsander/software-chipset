/***********************************************************************
 *
 * dkinsert.c -- This file contains dk_insert, the duplicate key index
 *               insertion function.
 *
 ***********************************************************************/

#include <stdio.h>
#include <dlist.h>
#include "dkpriv.h"

/***********************************************************************
 *
 * dk_insert -- This function inserts an item into a duplicate key index.
 *              If the key has already been inserted, the data are
 *              appended to the end of the list stored with that key.
 *              If the key is new, a new list is created and inserted
 *              into the unique key index.
 *
 *              1 is returned if successful, 0 if error.
 *
 ***********************************************************************/

#ifdef __STDC__
int dk_insert(DK_DUPKEY pindex, void *key, void *data)
#else
int dk_insert(pindex,key,data)
DK_DUPKEY	pindex;
void		*key;
void		*data;
#endif
{
	int		retval;
	DL_LIST		list;
	void		*tdata;
	void		*key2;
	DK_LISTDATA	*ldata;
	DK_LISTDATA	sdata;
	DUPKEY		*index;

	/* Validate parameters */
	COVER("dkinsert.c",1);
	if (pindex == NULL)
	{
		COVER("dkinsert.c",2);
		return 0;
	}
	if (key == NULL)
	{
		COVER("dkinsert.c",3);
		return 0;
	}

	/* Initialization */
	COVER("dkinsert.c",4);
	retval = 0;
	index = (DUPKEY*) pindex;

	/* Set up for search */
	sdata.key = key;
	sdata.index = index;
	dll_setData(index->list,(void*)&sdata);

	/* Search unique-key index to see if the key is already there */
	list = (DL_LIST) (*index->search)((void*)(index->index),
	                                  (void*)(index->list),
	                                  NULL);
	if (list == NULL)
	{
		COVER("dkinsert.c",5);
		/* Create the new list */
		list = dll_new(index->listSetup);
		if (list != NULL)
		{
			COVER("dkinsert.c",6);
			/* Set up list's global data object */
			ldata = (DK_LISTDATA *) malloc(sizeof(DK_LISTDATA));
			if (ldata != NULL)
			{
				COVER("dkinsert.c",7);
				ldata->index = index;
				ldata->key = key;
				dll_setData(list,(char*)ldata);

				/* Push new item onto the list */
				key2 = dll_pushf(list,key,data);
				if (key2 != NULL)
				{
					/* Insert list into index */
					COVER("dkinsert.c",8);
					retval = (*index->insert)(index->index,
					                          list,NULL);
				}

				/* Clean memory leak if error */
				COVER("dkinsert.c",9);
				if (retval <= 0)
				{
					COVER("dkinsert.c",10);
					free(ldata);
					retval = 0;
				}
			}

			/*
			 * Error handling:  Destroy list but leave
			 * key and data alone for the client to handle
			 */
			COVER("dkinsert.c",11);
			if (retval <= 0)
			{
				COVER("dkinsert.c",12);
				dll_destroy(list,NULL,NULL,NULL);
			}
		}
	}
	else
	{
		/* Key is already there, add new data to list */
		COVER("dkinsert.c",13);
		if (index->oneKey == DK_SINGLE)
		{
			COVER("dkinsert.c",14);
			key = dll_peekf(list,NULL);
		}
		if (index->order == DK_CHRON)
		{
			/* Add to end of list for chronological order */
			COVER("dkinsert.c",15);
			retval = (dll_pushr(list,key,data) != NULL);
		}
		else
		{
			/* Add to front of list for reverse order */
			COVER("dkinsert.c",16);
			retval = (dll_pushf(list,key,data) != NULL);
			if ((retval != 0) && (index->oneKey == DK_SEPARATE))
			{
				/* List data contains 1st key in list */
				COVER("dkinsert.c",17);
				ldata = (DK_LISTDATA*) dll_data(list);
				ldata->key = key;
			}
		}
		if (retval != 0)
		{
			COVER("dkinsert.c",18);
			retval = -1;
		}
	}
	COVER("dkinsert.c",19);
	dll_setData(index->list,NULL);
	if (retval != 0)
	{
		COVER("dkinsert.c",20);
		index->changed = 1;
	}
	return retval;
}

/********** End of file **********/

