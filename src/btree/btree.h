/*********************************************************************
 *
 * btree.h -- This file contains public declarations and definitions
 *            used by the in-memory B-tree implementation.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *********************************************************************/

/* Header file for in-memory B-tree implementation */

typedef void *BTREE;
typedef void *BT_SETUP;

#ifdef __STDC__
extern	void		bt_dump(BTREE, void (*)(void*,void*,void*), void*);
extern	void		*bt_search(BTREE, void*, void**);
extern	BTREE		bt_new(BT_SETUP);
extern	void		bt_destroy(BTREE, void(*)(void*,void*),
			           void(*)(void*,void*), void*);
extern	int		bt_insert(BTREE, void*, void*);
extern	void		bt_traverse(BTREE, void (*)(void*,void*,void*),void*);
extern	void		*bt_delete(BTREE, void*, void**);
extern	void		*bt_first(BTREE, void**);
extern	void		*bt_next(BTREE, void**);
extern	void		*bt_last(BTREE, void**);
extern	void		*bt_prev(BTREE, void**);
extern	BT_SETUP	bt_setup(int, int(*)(void*,void*), void*);
extern	void		bt_freeSetup(BT_SETUP);
extern	void		*bt_rank(BTREE, int, void*);
extern	void		*bt_delRank(BTREE, int, void**);
extern	void		*bt_data(BTREE);
extern	void		bt_setData(BTREE, void*);
#else
extern	void		bt_dump();
extern	void		*bt_search();
extern	BTREE		bt_new();
extern	void		bt_destroy();
extern	int		bt_insert();
extern	void		bt_traverse();
extern	void		*bt_delete();
extern	void		*bt_first();
extern	void		*bt_next();
extern	void		*bt_last();
extern	void		*bt_prev();
extern	BT_SETUP	bt_setup();
extern	void		bt_freeSetup();
extern	void		*bt_rank();
extern	void		*bt_delRank();
extern	void		*bt_data();
extern	void		bt_setData();
#endif

/****** end of file ******/


