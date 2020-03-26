/*************************************************************************
 *
 * dkpriv.h -- This file contains declarations required by the reusable
 *             component that generalizes a unique-key indexing structure
 *             to one that can store multiple data records under a single
 *             key.
 *
 *************************************************************************/

#include "dupkey.h"

/* The following is the setup structure for the duplicate key index */
struct dk_setup {
	void	*setup;
	int	 oneKey;
	int	 order;
	void	*data;
	void  (*freeSetup) DK_ARGS((void*));
	void *(*new) DK_ARGS((void*));
	void  (*destroy) DK_ARGS((void*,void(*)(void*,void*),
	                          void(*)(void*,void*),void*));
	int   (*insert) DK_ARGS((void*,void*,void*));
	void *(*delete) DK_ARGS((void*,void*,void**));
	void *(*search) DK_ARGS((void*,void*,void**));
	void  (*traverse) DK_ARGS((void*,void(*)(void*,void*,void*),void*));
	void  (*dump) DK_ARGS((void*,void(*)(void*,void*,void*),void*));
	void *(*first) DK_ARGS((void*,void**));
	void *(*last) DK_ARGS((void*,void**));
	void *(*next) DK_ARGS((void*,void**));
	void *(*prev) DK_ARGS((void*,void**));
	int   (*compare) DK_ARGS((void*,void*));
};

typedef struct dk_setup SETUP;

/* Following is the structure of a duplicate key index */

struct dupkey {
	void		*index;
	void		*data;
	int		oneKey;
	int		order;
	int		changed;
	DLL_SETUP	listSetup;
	DL_LIST		list;
	DL_LIST		currList;
	void  (*destroy) DK_ARGS((void*,void(*)(void*,void*),
	                          void(*)(void*,void*),void*));
	int   (*insert) DK_ARGS((void*,void*,void*));
	void *(*delete) DK_ARGS((void*,void*,void**));
	void *(*search) DK_ARGS((void*,void*,void**));
	void  (*traverse) DK_ARGS((void*,void(*)(void*,void*,void*),void*));
	void  (*dump) DK_ARGS((void*,void(*)(void*,void*,void*),void*));
	void *(*first) DK_ARGS((void*,void**));
	void *(*last) DK_ARGS((void*,void**));
	void *(*next) DK_ARGS((void*,void**));
	void *(*prev) DK_ARGS((void*,void**));
	int   (*compare) DK_ARGS((void*,void*));
};

typedef struct dupkey DUPKEY;

struct dk_listData {
	DUPKEY	*index;
	void	*key;
};

typedef struct dk_listData DK_LISTDATA;

#ifdef COVERAGE
#define COVER(fn,loc)	printf("Coverage:  file %s, location %03d\n",fn,loc)
#else
#define COVER(fn,loc)
#endif

/************* End of file ************/
