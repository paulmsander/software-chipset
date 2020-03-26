/************************************************************************
 *
 * dkcompare.c -- This file contains the comparison function that the
 *                duplicate key index uses to compare two keys.  The
 *                client's comparison function can't be used directly
 *                by the unique-key index because the key is stored as
 *                the global data object in a list.
 *
 ************************************************************************/

#include <stdio.h>
#include <dlist.h>
#include "dkpriv.h"

/************************************************************************
 *
 * dk_compare -- This function compares a key specified by the client
 *               with a key that is stored in the duplicate key index.
 *               The key that was stored is kept in the global data
 *               object of a list, and the unique key index always calls
 *               this function rather than the client's.
 *
 ************************************************************************/

int dk_compare(plist1,plist2)
void	*plist1;
void	*plist2;
{
	DL_LIST		list1;
	DL_LIST		list2;
	DK_LISTDATA	*data1;
	DK_LISTDATA	*data2;

	COVER("dkcompare.c",1);
	list1 = (DL_LIST) plist1;
	list2 = (DL_LIST) plist2;
	data1 = (DK_LISTDATA *) dll_data(list1);
	data2 = (DK_LISTDATA *) dll_data(list2);
	return (*data1->index->compare)(data1->key,data2->key);
}

/********** End of file **********/

