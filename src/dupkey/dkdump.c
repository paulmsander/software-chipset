/**************************************************************************
 *
 * dkdump.c -- This file contains functions that display the contents of
 *             a duplicate key index structure.
 *
 **************************************************************************/

#include <stdio.h>
#include "dkpriv.h"

struct dkInfo {
	void	*info;
#ifdef __STDC__
	void	(*dump)(void*,void*,void*);
#else
	void	(*dump)();
#endif
};

typedef	struct dkInfo DKINFO;

/**************************************************************************
 *
 * dk_dumpKey -- This function displays the contents of the unique key
 *               index.
 *
 **************************************************************************/

static void
#ifdef __STDC__
dk_dumpKey(void *key, void *data, void *info)
#else
dk_dumpKey(key, data, info)
void	*key;		/* Points to list of objects */
void	*data;		/* Null pointer */
void	*info;		/* Client-specified info */
#endif
{
	DL_LIST		list;
	DK_LISTDATA	*ldata;

	list = (DL_LIST) key;
	ldata = (DK_LISTDATA*) dll_data(list);
	printf("key %08x, list %08x\n",ldata->key,list);
}

/**************************************************************************
 *
 * dk_dumpList -- This function displays the list of data stored with each
 *                key.
 *
 **************************************************************************/

static void
#ifdef __STDC__
dk_dumpList(void *key, void *pinfo, void *data)
#else
dk_dumpList(key, pinfo, data)
void	*key;		/* Points to list of objects */
void	*pinfo;		/* Pointer to client-specified data */
void	*data;		/* Null pointer */
#endif
{
	DK_LISTDATA	*ldata;
	DL_LIST		list;
	DKINFO		*info;

	list = (DL_LIST) key;
	info = (DKINFO*) pinfo;
	ldata = (DK_LISTDATA*) dll_data(list);
	printf("list %08x, key %08x\n\n",list,ldata->key);
	dll_dump(list,info->dump,info->info);
	printf("---\n");
}

/**************************************************************************
 *
 * dk_dump -- This function displays the contents of a duplicate key index.
 *
 **************************************************************************/

#ifdef __STDC__
void dk_dump(DK_DUPKEY pindex, void (*key_dump)(void*,void*,void*), void *info)
#else
void dk_dump(pindex, key_dump, info)
DK_DUPKEY	pindex;
void		(*key_dump)();
void		*info;
#endif
{
	DKINFO	dinfo;
	DUPKEY	*index;

	if (pindex != NULL)
	{
		index = (struct dupkey*) pindex;

		/* Display duplicate key structure */
		printf("Contents of duplicate key index %x:\n\n",pindex);
		printf("Keys are allocated one per %s\n",
		       ((index->oneKey == DK_SINGLE) ? "list" : "item"));
		printf("Data are inserted in %s order\n",
		       ((index->order == DK_CHRON) ? "chronological" :
		                                     "reverse"));
		printf("Global data %x\n",(long)(index->data));
		printf("Changed %d\n\n",index->changed);

		/* Dump the index */
		if (index->dump != NULL)
		{
			printf("Primary index follows...\n");
			(*index->dump)(index->index,dk_dumpKey,NULL);
		}
		else
		{
			printf("<Unable to display primary index>\n");
		}
		printf("\n\n");
		if (index->traverse != NULL)
		{
			printf("----\nData lists follow...\n\n");
			dinfo.info = info;
			dinfo.dump = key_dump;
			(*index->traverse)(index->index,dk_dumpList,&dinfo);
		}
		else
		{
			printf("<Unable to display data>\n");
		}
		printf("\nEnd of duplicate key index\n\n");
	}
	else
	{
		printf("Unable to display null duplicate key index\n");
	}
	return;
}

/********** End of File **********/

