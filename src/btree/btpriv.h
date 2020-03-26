/**********************************************************************
 *
 * btpriv.h -- This file contains private declarations and definitions
 *             required by the in-memory B-tree implementation.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 **********************************************************************/

/* The following structure describes a B-tree node. */

#ifdef __STDC__
typedef int(*COMPFN)(void*,void*);
#else
typedef int(*COMPFN)();
#endif

struct btnode {
	int		nkeys;		/* Number of keys stored here */
	int		tsize;		/* Keys in subtree rooted here */
	int		currKey;	/* Last key found */
	struct btnode	*parent;	/* Parent of this node */
	void		**keys;		/* array[order-1] of keys */
	void		**data;		/* array[order-1] of other data */
	struct btnode	**children;	/* array[order] of children */
};

/* The following structure describes a B-tree. */

struct btree {
	int		order;		/* Max children permitted */
	COMPFN		comp;		/* Comparison function for keys */
	struct btnode	*root;		/* Root of tree */
	int		capacity;	/* Max keys that will fit */
	struct btnode	*currNode;	/* Node accessed */
	int		nextOk;		/* Indicates last search successful */
	void		*data;		/* Other data */
};

typedef struct btree *BTREE;
typedef struct btnode BTNODE;

/* The following structure describes a B-tree setup structure. */

struct bt_setup {
	int		order;		/* Max children permitted per node */
	int		(*comp)();	/* Comparision function for keys */
	void		*data;		/* Other data */
};

typedef struct bt_setup BT_SETUP;

#ifndef DEBUG
#define bt_malloc malloc
#define bt_free (void) free
#else
#ifdef __STDC__
extern void *bt_malloc(unsigned);
extern void bt_free(void *);
#else
extern void *bt_malloc();
extern void bt_free();
#endif
#endif

#ifdef __STDC__
extern int bt_malloc_verify(void);
#else
extern int bt_malloc_verify();
#endif

#ifndef __BTUTIL_C__
#ifdef __STDC__
extern int bt_searchNode(BTNODE*, void*, int(*)(), int*);
extern int bt_rotateRight(BTNODE*, int, int);
extern int bt_rotateLeft(BTNODE*, int, int);
#else
extern int bt_searchNode();
extern int bt_rotateRight();
extern int bt_rotateLeft();
#endif
#endif

#ifndef __BTDELUTL_C__
#ifdef __STDC__
extern void bt_delKey(BTNODE*, int);
extern void bt_weld(BTREE, BTNODE*, int);
extern void *bt_delPred(BTREE, BTNODE*, void**);
#else
extern void bt_delKey();
extern void bt_weld();
extern void *bt_delPred();
#endif
#endif

#ifdef COVERAGE
#define	COVER(fn,loc)	printf("Coverage:  file %s, location %03d\n",fn,loc)
#else
#define COVER(file,loc)
#endif

/*********** End of File *************/

