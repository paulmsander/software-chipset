/******************************************************************
 *
 * dlist.h -- This file contains public declarations and definitions
 *            used by the in-memory doubly-linked list implementation.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ******************************************************************/

#ifndef DLIST_H
#define DLIST_H

/* Hidden data types */

typedef void *DL_LIST;
typedef void *DLL_SETUP;

/* Peek/push/pop locations */

#define	DLL_FRONT	0
#define	DLL_BACK	1

/* Function declarations */

#ifdef __STDC__
extern	DLL_SETUP	dll_setup(int(*)(void*,void*),void*);
extern	void		dll_freeSetup(DLL_SETUP);
extern	DL_LIST		dll_new(DLL_SETUP);
extern	void		dll_destroy(DL_LIST,void(*)(void*,void*),
			            void(*)(void*,void*),void*);
extern	int		dll_insert(DL_LIST, void*, void*);
extern	void		*dll_delete(DL_LIST, void*, void**);
extern	void		*dll_search(DL_LIST,void*,void**);
extern	void		dll_traverse(DL_LIST,void(*)(void*,void*,void*),void*);
extern	void		dll_dump(DL_LIST, void(*)(void*,void*,void*),void*);
extern	void		*dll_first(DL_LIST, void**);
extern	void		*dll_next(DL_LIST,void**);
extern	void		*dll_last(DL_LIST,void**);
extern	void		*dll_prev(DL_LIST,void**);
extern	void		*dll_rank(DL_LIST,int,void**);
extern	void		*dll_delRank(DL_LIST, int, void**);
extern	void		dll_setData(DL_LIST, void*);
extern	void		*dll_data(DL_LIST);
extern	void		*dll_pushf(DL_LIST,void*,void*);
extern	void		*dll_pushr(DL_LIST,void*,void*);
extern	void		*dll_push(DL_LIST,int,void*,void*);
extern	void		*dll_popf(DL_LIST,void**);
extern	void		*dll_popr(DL_LIST,void**);
extern	void		*dll_pop(DL_LIST,int,void**);
extern	void		*dll_peekf(DL_LIST,void**);
extern	void		*dll_peekr(DL_LIST,void**);
extern	void		*dll_peek(DL_LIST,int,void**);

#else

extern	DLL_SETUP	dll_setup();
extern	void		dll_freeSetup();
extern	DL_LIST		dll_new();
extern	void		dll_destroy();
extern	int		dll_insert();
extern	void		*dll_delete();
extern	void		*dll_search();
extern	void		dll_traverse();
extern	void		dll_dump();
extern	void		*dll_first();
extern	void		*dll_next();
extern	void		*dll_last();
extern	void		*dll_prev();
extern	void		*dll_rank();
extern	void		*dll_delRank();
extern	void		dll_setData();
extern	void		*dll_data();
extern	void		*dll_pushf();
extern	void		*dll_pushr();
extern	void		*dll_push();
extern	void		*dll_popf();
extern	void		*dll_popr();
extern	void		*dll_pop();
extern	void		*dll_peekf();
extern	void		*dll_peekr();
extern	void		*dll_peek();

#endif

#endif

/************* End of file *************/

