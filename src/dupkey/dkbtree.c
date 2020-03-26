/*************************************************************************
 *
 * dkbtree.c -- This function contains a function that conveniently sets
 *              up a duplicate tree index based on a B-tree.
 *
 *************************************************************************/

#include <stdio.h>
#include <btree.h>
#include "dkpriv.h"

/*************************************************************************
 *
 * bk_setupBtree -- This function creates a setup structure for a
 *                  duplicate key index based on a B-tree.
 *
 *************************************************************************/

#ifdef __STDC__
DK_SETUP dk_setupBtree(int treeOrder, int (*comp)(void*,void*), int oneKey,
                       int insertOrder, void *data)
#else
DK_SETUP dk_setupBtree(treeOrder, comp, oneKey, insertOrder, data)
int	treeOrder;
int	(*comp)();
int	oneKey;
int	insertOrder;
void	*data;
#endif
{
	BT_SETUP	tsetup;
	DK_SETUP	retval;

	retval = NULL;
	COVER("dkbtree.c",1);
	tsetup = bt_setup(treeOrder, dk_compare, NULL);
	if (tsetup != NULL)
	{
		COVER("dkbtree.c",2);
		retval = dk_setup(tsetup,bt_freeSetup,bt_new,bt_destroy,
		                  bt_insert,bt_delete,bt_search,bt_traverse,
		                  bt_dump,bt_first,bt_last,bt_next,bt_prev,
		                  comp,oneKey,insertOrder,data);
		if (retval == NULL)
		{
			COVER("dkbtree.c",3);
			bt_freeSetup(tsetup);
		}
	}
	return retval;
}

/********** End of File **********/

