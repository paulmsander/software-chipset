/*************************************************************************
 *
 * dklist.c -- This function contains a function that conveniently sets
 *             up a duplicate tree index based on a linked list.
 *
 *************************************************************************/

#include <stdio.h>
#include <dlist.h>
#include "dkpriv.h"

/*************************************************************************
 *
 * bk_setupList -- This function creates a setup structure for a
 *                 duplicate key index based on a linked list.
 *
 *************************************************************************/

#ifdef __STDC__
DK_SETUP dk_setupList(int (*comp)(void*,void*), int oneKey, int insertOrder,
                      void *data)
#else
DK_SETUP dk_setupList(comp, oneKey, insertOrder, data)
int	(*comp)();
int	oneKey;
int	insertOrder;
void	*data;
#endif
{
	DLL_SETUP	tsetup;
	DK_SETUP	retval;

	COVER("dklist.c",1);
	retval = NULL;
	tsetup = dll_setup(dk_compare, NULL);
	if (tsetup != NULL)
	{
		COVER("dklist.c",2);
		retval = dk_setup(tsetup,dll_freeSetup,dll_new,dll_destroy,
		                  dll_insert,dll_delete,dll_search,dll_traverse,
		                  dll_dump,dll_first,dll_last,dll_next,dll_prev,
		                  comp,oneKey,insertOrder,data);
		if (retval == NULL)
		{
			COVER("dklist.c",3);
			dll_freeSetup(tsetup);
		}
	}
	COVER("dklist.c",4);
	return retval;
}

/********** End of File **********/

