/***************************************************************************
 *
 * dksetup.c -- This file contains functions that set up a duplicate key
 *              index structure based on a unique-key index structure.
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "dkpriv.h"

/***************************************************************************
 *
 * dk_setup -- This function allocates a setup structure for a duplicate
 *             key index structure and returns it to the caller.  The
 *             parameters of this function include a setup structure for
 *             a unique-key index structure, a function to compare two
 *             keys, and pointers to the functions of the unique-key
 *             structure that correspond to the duplicate-key structure
 *             operations.
 *
 ***************************************************************************/

#ifdef __STDC__
DK_SETUP dk_setup(
        void *setup,
        void  (*freeSetup)(void*),
        void *(*new)(void*),
        void  (*destroy)(void*,void(*)(void*,void*),void(*)(void*,void*),void*),
        int   (*insert)(void*,void*,void*),
        void *(*delete)(void*,void*,void**),
        void *(*search)(void*,void*,void**),
        void  (*traverse)(void*,void(*)(void*,void*,void*),void*),
        void  (*dump)(void*,void(*)(void*,void*,void*),void*),
        void *(*first)(void*,void**),
        void *(*last)(void*,void**),
        void *(*next)(void*,void**),
        void *(*prev)(void*,void**),
        int   (*compare)(void*,void*),
        int   oneKey,
        int   order,
        void *data)
#else
DK_SETUP dk_setup(setup,freeSetup,new,destroy,insert,delete,search,traverse,
	           dump,first,last,next,prev,compare,oneKey,order,data)
void	*setup;
void	 (*freeSetup)();
void	*(*new)();
void	 (*destroy)();
int	 (*insert)();
void	*(*delete)();
void	*(*search)();
void	 (*traverse)();
void	 (*dump)();
void	*(*first)();
void	*(*last)();
void	*(*next)();
void	*(*prev)();
int	 (*compare)();
int	 oneKey;
int	 order;
void	*data;
#endif
{
	SETUP	*val;

	/* Validate parameters */
	if (new == NULL)
	{
		COVER("dksetup.c",1);
		return NULL;
	}
	if (destroy == NULL)
	{
		COVER("dksetup.c",2);
		return NULL;
	}
	if (insert == NULL)
	{
		COVER("dksetup.c",3);
		return NULL;
	}
	if (compare == NULL)
	{
		COVER("dksetup.c",4);
		return NULL;
	}
	if (search == NULL)
	{
		COVER("dksetup.c",5);
		return NULL;
	}
	if ((order != DK_CHRON) && (order != DK_REVERSE))
	{
		COVER("dksetup.c",6);
		return NULL;
	}
	if ((oneKey != DK_SINGLE) && (oneKey != DK_SEPARATE))
	{
		COVER("dksetup.c",7);
		return NULL;
	}

	/* Build set-up structure */
	COVER("dksetup.c",8);
	val = (SETUP*) malloc(sizeof(SETUP));
	if (val != NULL)
	{
		COVER("dksetup.c",9);
		val->setup = setup;
		val->freeSetup = freeSetup;
		val->new = new;
		val->destroy = destroy;
		val->insert = insert;
		val->delete = delete;
		val->search = search;
		val->traverse = traverse;
		val->dump = dump;
		val->first = first;
		val->last = last;
		val->next = next;
		val->prev = prev;
		val->compare = compare;
		val->oneKey = oneKey;
		val->order = order;
		val->data = data;
	}
	COVER("dksetup.c",10);
	return (DK_SETUP) val;
}

/***************************************************************************
 *
 * dk_freeSetup -- This function frees the duplicate key index setup
 *                 structure.
 *
 ***************************************************************************/

#ifdef __STDC__
void dk_freeSetup(DK_SETUP psetup)
#else
void dk_freeSetup(psetup)
DK_SETUP	psetup;
#endif
{
	SETUP	*setup;

	if (psetup == NULL)
	{
		COVER("dksetup.c",11);
		return;
	}

	COVER("dksetup.c",12);
	setup = (SETUP*) psetup;
	if (setup->freeSetup != NULL)
	{
		COVER("dksetup.c",13);
		(*setup->freeSetup)(setup->setup);
	}
	COVER("dksetup.c",14);
	free(setup);
	return;
}

/************ End of file ************/

