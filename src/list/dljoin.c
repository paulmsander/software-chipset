/***********************************************************************
 *
 * dljoin.c -- This file contains functions used for concatenating
 *             two lists.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "dlpriv.h"

/***********************************************************************
 *
 * dll_join -- This function 
 *
 ***********************************************************************/

#ifdef __STDC__
DL_LIST dll_join(DL_LIST plist1, DL_LIST plist2)
#else
DL_LIST dll_data(plist1,plist2)
DL_LIST	plist1;
DL_LIST	plist2;
#endif
{
	LIST	*list1;
	LIST	*list2;
	LIST	*retval;

	list1 = (LIST*) plist1;
	list2 = (LIST*) plist2;
	COVER("dll_join.c",1);

	if ( list1 == NULL )
	{
		/*
		 * Return second list if first is NULL.  Note that the
		 * second may be NULL, which indicates an error.
		 */
		COVER("dll_join.c",2);
		retval = list2;
	}
	else if ( list2 == NULL )
	{
		/* Return first list if second is NULL */
		COVER("dll_join.c",3);
		retval = list1;
	}
	else if ( list1->comp != list2->comp )
	{
		/*
		 * Error if the comparison functions differ.  To
		 * do otherwise would mix data types in the same
		 * structure.
		 */
		COVER("dll_join.c",4);
		retval = NULL;
	}
	else if ( (list1->data != NULL) && (list2->data != NULL) &&
	          (list1->data != list2->data) )
	{
		/*
		 * Error if both lists have the global data item set and
		 * they differ.  To do otherwise loses one of the global
		 * data items.
		 */
		COVER("dll_join.c",5);
		retval = NULL;
	}
	else if (list1->last == NULL)
	{
		/*
		 * list1 is empty, return second list.  Note that the
		 * global data items must be checked, and if one of the
		 * lists has one, it must be returned.  list1 is freed.
		 */
		COVER("dll_join.c",6);
		retval = list2;
		if (list1->data != NULL)
		{
			COVER("dll_join.c",7);
			list2->data = list1->data;
		}
		free(list1);
	}
	else if (list2->last == NULL)
	{
		/*
		 * list2 is empty, return first list.  Note that the
		 * global data items must be checked, and if one of the
		 * lists has one, it must be returned.  list2 is freed.
		 */
		COVER("dll_join.c",8);
		retval = list1;
		if (list2->data != NULL)
		{
			COVER("dll_join.c",9);
			list1->data = list2->data;
		}
		free(list2);
	}
	else if ((list1->comp != NULL) &&
	         ((list1->comp)(list1->last->key,list2->last->next->key) > 0))
	{
		/*
		 * The lists are ordered, but the last item in the first list
		 * compares greater than the first item in the second list.
		 */
		COVER("dll_join.c",10);
		retval = NULL;
	}
	else
	{
		/* Concatenate the lists. */
		COVER("dll_join.c",11);
		retval = list1;
		list2->last->next = list1->last->next;
		list1->last = list2->last;
		list1->size = list1->size + list2->size;
		dll_touch(list1);
		if (list1->data == NULL)
		{
			/* Don't lose the global data */
			COVER("dll_join.c",12);
			list1->data = list2->data;
		}
		free(list2);
	}
	return (DL_LIST) retval;
}

/****** End of File ******/

