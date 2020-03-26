/***********************************************************************
 *                                                                     *
 * dktraverse.c -- This file contains the dk_traverse function and     *
 *                 other supporting functions.                         *
 *                                                                     *
 ***********************************************************************/

#include <stdio.h>
#include "dkpriv.h"

typedef struct {
	void	*info;
#ifdef __STD_C__
	void	(*fn)(void*,void*,void*);
#else
	void	(*fn)();
#endif
} TRAVERSE;


/***********************************************************************
 *                                                                     *
 * dk_visit -- This function visits each node in the primary (unique   *
 *             key) index, and traverses the list found there.         *
 *                                                                     *
 ***********************************************************************/

static void
#ifdef __STD_C__
dk_visit(void *key, void *info, void *data)
#else
dk_visit(key, info, data)
void	*key;
void	*info;
void	*data;
#endif
{
	DL_LIST		list;
	TRAVERSE	*trav;

	COVER("dktraverse.c",1);
	list = (DL_LIST) key;
	trav = (TRAVERSE*) info;
	dll_traverse(list,trav->fn,trav->info);
	return;
}

/***********************************************************************
 *                                                                     *
 * dk_traverse -- This function visits each item stored in the         *
 *                index.                                               *
 *                                                                     *
 ***********************************************************************/

void
#ifdef __STD_C__
dk_traverse(DK_DUPKEY pindex, void (*fn)(void*,void*,void*), void *info)
#else
dk_traverse(pindex, fn, info)
DK_DUPKEY	pindex;
void		(*fn)();
void		*info;
#endif
{
	DUPKEY		*index;
	TRAVERSE	trav;

	COVER("dktraverse.c",2);
	if ((pindex != NULL) && (fn != NULL))
	{
		COVER("dktraverse.c",3);
		index = (DUPKEY*) pindex;
		if (index->traverse != NULL)
		{
			COVER("dktraverse.c",4);
			trav.fn = fn;
			trav.info = info;
			(index->traverse)(index->index,dk_visit,(void*)&trav);
		}
	}
	return;
}

/***** End of File *****/

