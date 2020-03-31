/**************************************************************************
 *
 * dupkey.h -- This file contains public declarations needed to use the
 *             duplicate key index component.
 *
 **************************************************************************/

#ifndef DUPKEY_H__
#define DUPKEY_H__

#include <stdio.h>
#include <dlist.h>

/*
 * These specify the order in which data items are added to the list of
 * data stored with each key
 */
#define	DK_CHRON	DLL_BACK	/* Chronological order */
#define	DK_REVERSE	DLL_FRONT	/* Reverse chronological order */

/*
 * These specify if there is a single key representing each list of data,
 * or if there is a unique key structure for each data item.
 */
#define	DK_SINGLE	0	/* One key per list */
#define	DK_SEPARATE	1	/* One key per data item */

/* The following is the setup structure for the duplicate key index */
typedef	void	*DK_SETUP;

/* The following is the duplicate key index structure */
typedef	void	*DK_DUPKEY;

#ifdef __STDC__
#define DK_ARGS(ARGS) ARGS
#else
#define DK_ARGS(ARGS) ()
#endif

/* The following are public functional interfaces to the component */

int		dk_compare DK_ARGS((void*,void*));
void		*dk_data DK_ARGS((DK_DUPKEY));
void		*dk_delFirst DK_ARGS((DK_DUPKEY,void*,void**,int*));
void		*dk_delLast DK_ARGS((DK_DUPKEY,void*,void**,int*));
DL_LIST		dk_delList DK_ARGS((DK_DUPKEY,void*));
void		dk_destroy DK_ARGS((DK_DUPKEY, void (*)(void*,void*),
		           void (*)(void*,void*), void*));
void		dk_dump DK_ARGS((DK_DUPKEY,void (*)(void*,void*,void*),void*));
void		*dk_first DK_ARGS((DK_DUPKEY, void**));
void		dk_freeSetup DK_ARGS((DK_SETUP));
int		dk_insert DK_ARGS((DK_DUPKEY pindex, void *key, void *data));
void		*dk_last DK_ARGS((DK_DUPKEY, void**));
DK_DUPKEY	dk_new DK_ARGS((DK_SETUP));
void		*dk_next DK_ARGS((DK_DUPKEY, void**));
void		*dk_prev DK_ARGS((DK_DUPKEY, void**));
void		*dk_search DK_ARGS((DK_DUPKEY, void*, void**));
void		dk_setData DK_ARGS((DK_DUPKEY,void*));
DK_SETUP	dk_setup DK_ARGS((void*,
		         void (*)(void*), void* (*)(void*),
		         void  (*)(void*,void(*)(void*,void*),
		                   void(*)(void*,void*),void*),
		         int   (*insert)(void*,void*,void*),
		         void* (*)(void*,void*,void**),
		         void* (*)(void*,void*,void**),
		         void  (*)(void*,void(*)(void*,void*,void*),void*),
		         void  (*)(void*,void(*)(void*,void*,void*),void*),
		         void* (*)(void*,void**),
		         void* (*)(void*,void**),
		         void* (*)(void*,void**),
		         void* (*)(void*,void**),
		         int   (*)(void*,void*),
		         int,
		         int,
		         void *));
DK_SETUP	dk_setupBtree DK_ARGS((int, int (*)(void*,void*), int, int,
		                       void*));
DK_SETUP	dk_setupList DK_ARGS((int (*)(void*,void*), int, int, void*));
void		dk_traverse DK_ARGS((DK_DUPKEY, void(*)(void*,void*,void*),
		                     void*));

#endif

/************* End of file ************/
