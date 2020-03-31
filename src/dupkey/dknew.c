/***************************************************************************
 *
 * dknew.c -- This file contains functions that create a duplicate key index
 *            structure based on a unique-key index structure.
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "dkpriv.h"

/***************************************************************************
 *
 * dk_new -- This function creates a duplicate key index structure based
 *           upon a unique key index structure.
 *
 ***************************************************************************/

#ifdef __STDC__
DK_DUPKEY	dk_new(DK_SETUP psetup)
#else
DK_DUPKEY	dk_new(psetup)
DK_SETUP	psetup;
#endif
{
	DUPKEY	*val;
	SETUP	*setup;

	COVER("dknew.c",1);
	if (psetup == NULL)
	{
		COVER("dknew.c",2);
		return NULL;
	}

	COVER("dknew.c",3);
	setup = (SETUP*) psetup;
	val = (DUPKEY*) malloc(sizeof(DUPKEY));
	if (val != NULL)
	{
		COVER("dknew.c",4);
		val->index = (*setup->new)(setup->setup);
		if (val->index != NULL)
		{
			COVER("dknew.c",5);
			val->listSetup = dll_setup(NULL,NULL);
			if (val->listSetup != NULL)
			{
				COVER("dknew.c",6);
				val->list = dll_new(val->listSetup);
				if (val->list != NULL)
				{
					COVER("dknew.c",7);
					val->data = setup->data;
					val->oneKey = setup->oneKey;
					val->order = setup->order;
					val->destroy = setup->destroy;
					val->insert = setup->insert;
					val->delete = setup->delete;
					val->search = setup->search;
					val->traverse = setup->traverse;
					val->dump = setup->dump;
					val->first = setup->first;
					val->last = setup->last;
					val->next = setup->next;
					val->prev = setup->prev;
					val->compare = setup->compare;
					val->changed = 0;
					return (DK_DUPKEY) val;
				}
				COVER("dknew.c",8);
				dll_freeSetup(val->listSetup);
			}
			COVER("dknew.c",9);
			(setup->destroy)(val->index,NULL,NULL,NULL);
		}
		COVER("dknew.c",10);
		free(val);
		val = NULL;
	}
	COVER("dknew.c",11);
	return (DK_DUPKEY) val;
}

/************ End of file ************/

