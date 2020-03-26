/***********************************************************************
 *
 * dkdestroy.c -- This file contains functions that destroy a duplicate
 *                index.
 *
 ***********************************************************************/

#include <stdio.h>
#include <dlist.h>
#include "dkpriv.h"

struct finfo {
	DUPKEY	*index;
	void	*info;
#ifdef __STDC__
	void	(*free_data)(void*,void*);
	void	(*free_key)(void*,void*);
#else
	void	(*free_data)();
	void	(*free_key)();
#endif
};


/***********************************************************************
 *
 * freeNode -- This function frees the doubly-linked list stored at a
 *             node in the unique-key index.
 *
 ***********************************************************************/

static void freeNode(plist,pinfo)
void	*plist;
void	*pinfo;
{
	DL_LIST		list;
	struct finfo	*info;
	DK_LISTDATA	*data;

	COVER("dkdestroy.c",1);
	list = (DL_LIST) plist;
	info = (struct finfo*) pinfo;
	data = (DK_LISTDATA*) dll_data(list);

	if (info->index->oneKey == DK_SINGLE)
	{
		COVER("dkdestroy.c",2);
		dll_destroy(list,NULL,info->free_data,info->info);
		if (info->free_key != NULL)
		{
			COVER("dkdestroy.c",3);
			(*info->free_key)(data->key,info->info);
		}
	}
	else
	{
		COVER("dkdestroy.c",4);
		dll_destroy(list,info->free_key,info->free_data,info->info);
	}
	COVER("dkdestroy.c",5);
	free(data);
	return;
}

/***********************************************************************
 *
 * dk_destroy -- This function frees all of the storage associated with
 *               a duplicate key index.
 *
 ***********************************************************************/

#ifdef __STDC__
void dk_destroy(DK_DUPKEY pindex, void (*freeKey)(void*,void*),
                void (*freeData)(void*,void*), void *pinfo)
#else
void dk_destroy(pindex,freeKey,freeData,pinfo)
DK_DUPKEY	pindex;
void		(*freeKey)();
void		(*freeData)();
void		*pinfo;
#endif
{
	struct finfo	info;
	DUPKEY		*index;

	COVER("dkdestroy.c",6);
	if (pindex != NULL)
	{
		COVER("dkdestroy.c",7);
		index = (struct dupkey*) pindex;
		info.index = index;
		info.free_data = freeData;
		info.free_key = freeKey;
		info.info = pinfo;
		(index->destroy)((void*)(index->index),freeNode,NULL,
		                 (void*)(&info));
		dll_destroy(index->list,NULL,NULL,NULL);
		dll_freeSetup(index->listSetup);
		free(index);
	}
	return;
}

/************ End of file ***********/

