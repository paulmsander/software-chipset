/************************************************************************
 *
 * test.c -- This program tests the duplicate-key generalizer
 *           implementation.  It attempts to cover all branches of control
 *           less those taken when malloc fails.  It also makes no attempt
 *           to test all possible flows of control taken by the unique-key
 *           index or doubly-linked list implementations upon which the
 *           generalizer is based.
 *
 ************************************************************************/

#include <stdio.h>
#include <dlist.h>
#include <btree.h>
#include "dupkey.h"

/* Define this for verbose output */
#define VERBOSE

/* These are the list operations that the program tests */

enum ops { BTSETUP, SETUP, FREESETUP, MARK, NEW, DESTROY, INSERT,
           FIRST, LAST, SEARCH, NEXT, PREV, TRAVERSE, DELFIRST, DELLAST,
           DELLIST, LFIRST, LNEXT, LDATA, LDESTROY, DATA, SETDATA, BTFREESETUP,
           SETUPBT,SETUPDL,DLSETUP,DUMP,
           END
};

typedef enum ops OP;

char *opnames[] = {"btsetup","setup","freesetup","mark", "new", "destroy",
                   "insert","first","last","search","next","prev","traverse",
                   "delFirst","delLast","delList","listFirst","listNext",
                   "listData","listDest","data","setData", "btfreeset",
                   "setupBt","setupDl","Dlsetup","dump",
                   "end"
};

/*
 * The following structure describes a test case.  An array of these
 * is given to an interpreter which performs each test and reports the
 * results.
 */

struct testcase {
	OP	op;		/* Operation */
	int	key;		/* Insertion/seek key */
	int	data;		/* Application-specific or expected data */
	int	data2;		/* Secondary data */
	int	result;		/* Return code or expected result */
	int	dump;		/* If not zero, dumps list for debugging */
};

typedef struct testcase CASE;

/* Value of "key" when calling dll_destroy */
#define	FREEKEY		1	/* call freeKey() */
#define	FREEDATA	2	/* call freeData() */

/* Invalid value for insertion order and key repetition */
#define	DK_INVALID	100

/* This is the list of test cases that make up the suite. */

CASE suite[] = {
/* ------------	OP		key	data	data2	result	dump	*/
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	TRAVERSE,	1,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	0,	0	},
	{	DESTROY,	0,	0,	0,	0,	0	},
	{	DESTROY,	1,	0,	0,	0,	0	},
	{	DESTROY,	2,	0,	0,	0,	0	},
	{	DESTROY,	3,	0,	0,	0,	0	},
	{	INSERT,		1000,	1,	0,	0,	0	},
	{	SEARCH,		1000,	0,	0,	0,	0	},
	{	FIRST,		1000,	0,	0,	0,	0	},
	{	LAST,		1000,	0,	0,	0,	0	},
	{	NEXT,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	TRAVERSE,	1,	0,	0,	0,	0	},
	{	DELFIRST,	1000,	0,	0,	0,	0	},
	{	DELLAST,	1000,	0,	0,	0,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	SETDATA,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		0,	1,	0,	0,	0	},
	{	SETUP,		0,	2,	0,	0,	0	},
	{	SETUP,		0,	3,	0,	0,	0	},
	{	SETUP,		0,	4,	0,	0,	0	},
	{	SETUP,		0,	5,	0,	0,	0	},
	{	SETUP,		-1,	0,	0,	0,	0	},
	{	SETUP,		0,	0,	-1,	0,	0	},
	{	SETUP,		0,	7,	0,	1,	0	},
	{	NEW,		0,	0,	0,	0,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		0,	6,	0,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DUMP,		0,	0,	0,	0,	0	},
	{	DATA,		0,	6,	0,	0,	0	},
	{	SETDATA,	0,	15,	0,	0,	0	},
	{	DATA,		0,	15,	0,	0,	0	},
	{	INSERT,		0,	0,	0,	0,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	NEXT,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		1000,	0,	0,	1,	0	},
	{	NEXT,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	FIRST,		1000,	0,	0,	0,	0	},
	{	LAST,		1000,	0,	0,	0,	0	},
	{	TRAVERSE,	1,	0,	0,	0,	0	},
	{	DESTROY,	0,	0,	0,	0,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		1,	0,	0,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DUMP,		0,	0,	0,	0,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	DESTROY,	3,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	DESTROY,	3,	0,	1,	1,	0	},
	{	DUMP,		0,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	INSERT,		1000,	2,	0,	-1,	0	},
	{	INSERT,		2000,	1,	0,	1,	0	},
	{	INSERT,		2000,	2,	0,	-1,	0	},
	{	DUMP,		0,	0,	0,	0,	0	},
	{	SEARCH,		1000,	1,	0,	1,	0	},
	{	SEARCH,		2000,	1,	0,	1,	0	},
	{	FIRST,		1000,	1,	0,	1,	0	},
	{	NEXT,		1000,	2,	0,	1,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	NEXT,		2000,	2,	0,	1,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	LAST,		2000,	2,	0,	1,	0	},
	{	PREV,		2000,	1,	0,	1,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	PREV,		1000,	1,	0,	1,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	NEXT,		1000,	1,	0,	1,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	NEXT,		2500,	0,	0,	0,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	PREV,		2000,	2,	0,	1,	0	},
	{	TRAVERSE,	0,	10,	0,	0,	0	},
	{	TRAVERSE,	1,	20,	0,	4,	0	},
	{	DESTROY,	3,	0,	4,	2,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		0,	0,	1,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DUMP,		0,	0,	0,	0,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	DESTROY,	3,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	DESTROY,	3,	0,	1,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		1000,	2,	0,	1,	0	},
	{	INSERT,		1000,	1,	0,	-1,	0	},
	{	INSERT,		2000,	2,	0,	1,	0	},
	{	INSERT,		2000,	1,	0,	-1,	0	},
	{	SEARCH,		1000,	1,	0,	1,	0	},
	{	SEARCH,		2000,	1,	0,	1,	0	},
	{	FIRST,		1000,	1,	0,	1,	0	},
	{	NEXT,		1000,	2,	0,	1,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	NEXT,		2000,	2,	0,	1,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	LAST,		2000,	2,	0,	1,	0	},
	{	PREV,		2000,	1,	0,	1,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	PREV,		1000,	1,	0,	1,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	NEXT,		1000,	1,	0,	1,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	NEXT,		2500,	0,	0,	0,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	PREV,		2000,	2,	0,	1,	0	},
	{	TRAVERSE,	0,	10,	0,	0,	0	},
	{	TRAVERSE,	1,	20,	0,	4,	0	},
	{	DESTROY,	3,	0,	4,	4,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		0,	0,	0,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		1000,	2,	0,	1,	0	},
	{	INSERT,		1000,	1,	0,	-1,	0	},
	{	INSERT,		2000,	2,	0,	1,	0	},
	{	INSERT,		2000,	1,	0,	-1,	0	},
	{	SEARCH,		1000,	1,	0,	1,	0	},
	{	SEARCH,		2000,	1,	0,	1,	0	},
	{	FIRST,		1000,	1,	0,	1,	0	},
	{	NEXT,		1000,	2,	0,	1,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	NEXT,		2000,	2,	0,	1,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	LAST,		2000,	2,	0,	1,	0	},
	{	PREV,		2000,	1,	0,	1,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	PREV,		1000,	1,	0,	1,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	NEXT,		1000,	1,	0,	1,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	NEXT,		2500,	0,	0,	0,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	PREV,		2000,	2,	0,	1,	0	},
	{	TRAVERSE,	0,	10,	0,	0,	0	},
	{	TRAVERSE,	1,	20,	0,	4,	0	},
	{	DESTROY,	3,	0,	4,	2,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		1,	0,	1,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	INSERT,		1000,	2,	0,	-1,	0	},
	{	INSERT,		2000,	1,	0,	1,	0	},
	{	INSERT,		2000,	2,	0,	-1,	0	},
	{	SEARCH,		1000,	1,	0,	1,	0	},
	{	SEARCH,		2000,	1,	0,	1,	0	},
	{	FIRST,		1000,	1,	0,	1,	0	},
	{	NEXT,		1000,	2,	0,	1,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	NEXT,		2000,	2,	0,	1,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	NEXT,		2000,	0,	0,	0,	0	},
	{	LAST,		2000,	2,	0,	1,	0	},
	{	PREV,		2000,	1,	0,	1,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	PREV,		1000,	1,	0,	1,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	NEXT,		1000,	1,	0,	1,	0	},
	{	SEARCH,		500,	0,	0,	0,	0	},
	{	PREV,		1000,	0,	0,	0,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	NEXT,		2000,	1,	0,	1,	0	},
	{	SEARCH,		1500,	0,	0,	0,	0	},
	{	PREV,		1000,	2,	0,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	NEXT,		2500,	0,	0,	0,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	PREV,		2000,	2,	0,	1,	0	},
	{	TRAVERSE,	0,	10,	0,	0,	0	},
	{	TRAVERSE,	1,	20,	0,	4,	0	},
	{	DESTROY,	3,	0,	4,	4,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		1,	0,	1,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DUMP,		0,	0,	0,	0,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	INSERT,		1000,	2,	0,	-1,	0	},
	{	INSERT,		1000,	3,	0,	-1,	0	},
	{	INSERT,		2000,	1,	0,	1,	0	},
	{	INSERT,		2000,	2,	0,	-1,	0	},
	{	INSERT,		2000,	3,	0,	-1,	0	},
	{	INSERT,		3000,	1,	0,	1,	0	},
	{	INSERT,		3000,	2,	0,	-1,	0	},
	{	INSERT,		3000,	3,	0,	-1,	0	},
	{	INSERT,		4000,	1,	0,	1,	0	},
	{	INSERT,		4000,	2,	0,	-1,	0	},
	{	INSERT,		4000,	3,	0,	-1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELFIRST,	1000,	1,	1,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DELFIRST,	1000,	2,	1,	1,	0	},
	{	DELFIRST,	1000,	3,	1,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELFIRST,	1000,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELLAST,	2000,	3,	1,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DELLAST,	2000,	2,	1,	1,	0	},
	{	DELLAST,	2000,	1,	1,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELLAST,	2000,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DELLIST,	3000,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	LDATA,		0,	0,	0,	1,	0	},
	{	LFIRST,		3000,	1,	0,	1,	0	},
	{	LNEXT,		3000,	2,	0,	1,	0	},
	{	LNEXT,		3000,	3,	0,	1,	0	},
	{	LNEXT,		0,	0,	0,	0,	0	},
	{	DELLIST,	3000,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DESTROY,	3,	0,	3,	3,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTSETUP,	0,	1,	0,	1,	0	},
	{	SETUP,		1,	0,	0,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	INSERT,		1000,	2,	0,	-1,	0	},
	{	INSERT,		1000,	3,	0,	-1,	0	},
	{	INSERT,		2000,	1,	0,	1,	0	},
	{	INSERT,		2000,	2,	0,	-1,	0	},
	{	INSERT,		2000,	3,	0,	-1,	0	},
	{	INSERT,		3000,	1,	0,	1,	0	},
	{	INSERT,		3000,	2,	0,	-1,	0	},
	{	INSERT,		3000,	3,	0,	-1,	0	},
	{	INSERT,		4000,	1,	0,	1,	0	},
	{	INSERT,		4000,	2,	0,	-1,	0	},
	{	INSERT,		4000,	3,	0,	-1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELFIRST,	1000,	1,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DELFIRST,	1000,	2,	0,	1,	0	},
	{	DELFIRST,	1000,	3,	1,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELFIRST,	1000,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELLAST,	2000,	3,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DELLAST,	2000,	2,	0,	1,	0	},
	{	DELLAST,	2000,	1,	1,	1,	0	},
	{	SEARCH,		2500,	0,	0,	0,	0	},
	{	DELLAST,	2000,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DELLIST,	3000,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	LDATA,		0,	3000,	0,	1,	0	},
	{	LFIRST,		3000,	1,	0,	1,	0	},
	{	LNEXT,		3000,	2,	0,	1,	0	},
	{	LNEXT,		3000,	3,	0,	1,	0	},
	{	LNEXT,		0,	0,	0,	0,	0	},
	{	DELLIST,	3000,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	DESTROY,	3,	0,	3,	1,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	BTFREESETUP,	0,	0,	0,	0,	0	},
	{	SETUPBT,	0,	1,	0,	0,	0	},
	{	SETUPBT,	0,	2,	0,	0,	0	},
	{	NEW,		0,	0,	0,	0,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	SETUPBT,	0,	0,	0,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	SETUPDL,	0,	1,	0,	0,	0	},
	{	NEW,		0,	0,	0,	0,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	SETUPDL,	0,	0,	0,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	DLSETUP,	0,	0,	0,	1,	0	},
	{	SETUP,		0,	0,	0,	1,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	DLSETUP,	0,	1,	0,	0,	0	},
	{	SETUP,		0,	0,	0,	1,	0	},
	{	FREESETUP,	0,	1,	0,	0,	0	},
	{	BTSETUP,	0,	0,	0,	1,	0	},
	{	SETUP,		1,	0,	0,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	FIRST,		0,	0,	0,	0,	0	},
	{	LAST,		0,	0,	0,	0,	0	},
	{	INSERT,		1000,	1,	0,	1,	0	},
	{	FIRST,		1000,	1,	0,	1,	0	},
	{	INSERT,		1000,	2,	0,	-1,	0	},
	{	LAST,		1000,	2,	0,	1,	0	},
	{	FIRST,		1000,	1,	0,	1,	0	},
	{	DUMP,		0,	0,	0,	0,	0	},
	{	DELLIST,	1000,	0,	0,	1,	0	},
	{	DESTROY,	3,	0,	0,	0,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	DELLIST,	1000,	0,	0,	0,	0	},
/* ------------	OP		key	data	data2	result	dump	*/
	{	END,		0,	0,	0,	0,	0	}
};

/* This structure is used for testing the dk_setup function */

struct tsetup {
#ifdef __STDC__
	void *(*new)(void*);
	void  (*destroy)(void*,void(*)(void*,void*),void(*)(void*,void*),void*);
	int   (*insert)(void*,void*,void*);
	int   (*compare)(void*,void*);
#else
	void	*(*new)();
	void	 (*destroy)();
	int	 (*insert)();
	int	 (*compare)();
#endif
};

/* This is the comparison function */

#ifdef __STDC__
int comp(void *key1, void *key2)
#else
int comp(key1,key2)
void	*key1;
void	*key2;
#endif
{
	return *((int*)key1) - *((int*)key2);
}

/* This function displays a key and its data */
#ifdef __STDC__
void dumpKey(void *key,void *data,void *info)
#else
void dumpKey(key,data,info)
void	*key;
void	*data;
void	*info;
#endif
{
	printf("  key = %4.4d (%08lx)\n  data = ",*(int*)key,(unsigned long)key);
	if (data != NULL) printf("%4.4d\n",*(int*)data);
	else printf("(NULL)\n");
	return;
}

/*
 * These functions are called by dk_destroy, and count the number of
 * key and data structures are freed, and also verify that the info
 * parameter is passed properly.  Some attempt is made to be sure that
 * the data are freed before the key.
 */

int	freedKeys;	/* Number of keys freed */
int	lastKey;	/* Matches keys to data */
int	lastData;	/* Matches keys to data */
int	freedData;	/* Number of data records freed */
int	*expInfo;	/* Expected value of info */
int	infoOk;		/* Indicates that the info was always correct */
int	freeOk;		/* Indicates that the freeKey and freeData functions
			 * were called correctly
			 */

#ifdef __STDC__
void freeKey(void *key, void *info)
#else
void freeKey(key,info)
void	*key;
void	*info;
#endif
{
#ifdef VERBOSE
	printf("Freeing key %d at %lx\n",*(int*)key,(unsigned long) key);
#endif
	if ((int*) info != expInfo)
	{
		infoOk = 0;
		printf("FAILURE:  unexpected info in freeKey\n");
	}
	if (freedData >= 0)
	{
		if (lastKey > freedData)
		{
			freeOk = 0;
			printf("FAILURE:  lastKey %d <= freedData %d\n",
			       lastKey,freedData);
		}
		lastKey = freedData;
	}
	freedKeys++;
}

#ifdef __STDC__
void freeData(void *key, void *info)
#else
void freeData(key,info)
void	*key;
void	*info;
#endif
{
#ifdef VERBOSE
	printf("Freeing data %d at %lx\n",*(int*)key,(unsigned long) key);
#endif
	if ((int*) info != expInfo)
	{
		infoOk = 0;
		printf("FAILURE:  unexpected info in freeData\n");
	}
	if ((freedKeys >= 0) && (freedKeys > freedData))
	{
		printf("FAILURE:  freedKeys %d > freedData %d\n",freedKeys,
		       freedData);
		freeOk = 0;
	}
	freedData++;
}

/*
 * The following variables and the visit() function are used for testing
 * the dk_traverse() function.
 */

int	travOk;		/* Traversal successful */
int	visited;	/* Number of nodes visited */

#ifdef __STDC__
void visit(void *key, void *info, void *data)
#else
void visit(key,info,data)
void	*key;
void	*info;
void	*data;
#endif
{
	visited++;
	if ((lastKey != 0) && (*(int*)key < lastKey)) travOk = 0;
	else if ((lastKey != 0) && (*(int*)key == lastKey) &&
	         (*(int*)data <= lastData)) travOk = 0;
	else if ((int*) info != expInfo) travOk = 0;
	lastKey = *(int*) key;
	lastData = *(int*) data;
	return;
}
/* The test suite starts here... */

#ifdef __STDC__
int main(int argc, char **argv)
#else
int main(argc,argv)
int	argc;
char	**argv;
#endif
{
	int		i;		/* Loop counter */
	int		ok;		/* Current test succeeded */
	int		fail;		/* Any test failed */
	int		done;		/* Holds size of test table */
	int		intval;		/* Integer value */
	void		*ptrval;	/* Pointer value */
	void		*ptrval2;	/* Pointer value */
	DK_DUPKEY	index;		/* Duplicate key index under test */
	DK_SETUP	setup;		/* Configuration data for index */
	int		safe;		/* Safe to delete key */
	DL_LIST		list;		/* Returned list */

	/* The following are setup data for a duplicate key index */
	void		*isetup;	/* Configuration data for unique-key
					 * index
					 */
#ifdef __STD_C__
	void		(*ifreeSetup)(void*);
	void		*(*inew)(void*);
	void		(*idestroy)(void*,void(*)(void*,void*),
			            void(*)(void*,void*),void*);
	int		(*iinsert)(void*,void*,void*);
	void		*(*idelete)(void*,void*,void**);
	void		*(*isearch)(void*,void*,void**);
	void		(*itraverse)(void(*)(void*,void*,void*),void*);
	void		(*idump)(void*,void(*)(void*,void*,void*),void*);
	void		*(*ifirst)(void*,void**);
	void		*(*ilast)(void*,void**);
	void		*(*inext)(void*,void**);
	void		*(*iprev)(void*,void**);
#else
	void		(*ifreeSetup)();
	void		*(*inew)();
	void		(*idestroy)();
	int		(*iinsert)();
	void		*(*idelete)();
	void		*(*isearch)();
	void		(*itraverse)();
	void		(*idump)();
	void		*(*ifirst)();
	void		*(*ilast)();
	void		*(*inext)();
	void		*(*iprev)();
#endif

	/* Initialization */
	fail = 0;
	index = (DK_DUPKEY) NULL;
	setup = (DK_SETUP) NULL;
	isetup = (void*) NULL;
	list = (DL_LIST) NULL;

	/* Compute the number of test cases there are */
	done = sizeof(suite)/sizeof(CASE);

	/* Display heading */
	printf("test OP         key   data  data2  result  intval ptrval  ptrval2  pass\n");
	for (i = 0; (i < done) && (suite[i].op != END); i++)
	{
		/* Initialize test case */
		ok = 1;
		intval = 0;
		ptrval = NULL;
		ptrval2 = NULL;

		/* Perform test */
		switch (suite[i].op)
		{
	case MARK:
			/* Not a test case; it puts a mark on the output */
			printf("-- -- -- -- -- -- -- -- -- -- -- -- -- --\n");
			break;

	case BTSETUP:
			/* Not a test case; sets up a B-tree */
			/* result = 1 when success is expected */
			/* data = 1 if full dump capability wanted */
			isetup = (void*) bt_setup(10,dk_compare,NULL);
			ok = (isetup != NULL);
			if ( isetup != NULL )
			{
				ifreeSetup = bt_freeSetup;
				inew = bt_new;
				idestroy = bt_destroy;
				iinsert = bt_insert;
				idelete = bt_delete;
				isearch = bt_search;
				if ( suite[i].data )
				{
					itraverse = bt_traverse;
					idump = bt_dump;
				}
				else
				{
					itraverse = NULL;
					idump = NULL;
				}
				ifirst = bt_first;
				ilast = bt_last;
				inext = bt_next;
				iprev = bt_prev;
			}
			else
			{
				ifreeSetup = NULL;
				inew = NULL;
				idestroy = NULL;
				iinsert = NULL;
				idelete = NULL;
				isearch = NULL;
				itraverse = NULL;
				idump = NULL;
				ifirst = NULL;
				ilast = NULL;
				inext = NULL;
				iprev = NULL;
			}
			break;

	case DLSETUP:
			/* Not a test case; sets up a B-tree */
			/* result = 1 when success is expected */
			isetup = (void*) dll_setup(dk_compare,NULL);
			ok = (isetup != NULL);
			if ( isetup != NULL )
			{
				if ( suite[i].data ) ifreeSetup = dll_freeSetup;
				else ifreeSetup = NULL;
				inew = dll_new;
				idestroy = dll_destroy;
				iinsert = dll_insert;
				idelete = dll_delete;
				isearch = dll_search;
				itraverse = dll_traverse;
				idump = dll_dump;
				ifirst = dll_first;
				ilast = dll_last;
				inext = dll_next;
				iprev = dll_prev;
			}
			else
			{
				ifreeSetup = NULL;
				inew = NULL;
				idestroy = NULL;
				iinsert = NULL;
				idelete = NULL;
				isearch = NULL;
				itraverse = NULL;
				idump = NULL;
				ifirst = NULL;
				ilast = NULL;
				inext = NULL;
				iprev = NULL;
			}
			break;

	case BTFREESETUP:
			ifreeSetup = NULL;
			inew = NULL;
			idestroy = NULL;
			iinsert = NULL;
			idelete = NULL;
			isearch = NULL;
			itraverse = NULL;
			idump = NULL;
			ifirst = NULL;
			ilast = NULL;
			inext = NULL;
			iprev = NULL;
			break;

	case SETUP:
			/*
			 * Test case:  key    = DK_CHRON or DK_REVERSE
			 *             data2  = DK_SINGLE or DK_SEPARATE
			 *             data   = selects failure mode
			 *             result = 0 if NULL expected
			 */

			switch (suite[i].data)
			{
		case 1:
				/* No inew */
				setup = dk_setup(isetup,ifreeSetup,NULL,
				                 idestroy,iinsert,
				                 idelete,isearch,
				                 itraverse,idump,
				                 ifirst,ilast,inext,
				                 iprev,comp,suite[i].data2,
				                 suite[i].key,NULL);
				break;
		case 2:
				/* No idestroy */
				setup = dk_setup(isetup,ifreeSetup,inew,
				                 NULL,iinsert,
				                 idelete,isearch,
				                 itraverse,idump,
				                 ifirst,ilast,inext,
				                 iprev,comp,suite[i].data2,
				                 suite[i].key,NULL);
				break;
		case 3:
				/* No iinsert */
				setup = dk_setup(isetup,ifreeSetup,inew,
				                 idestroy,NULL,
				                 idelete,isearch,
				                 itraverse,idump,
				                 ifirst,ilast,inext,
				                 iprev,comp,suite[i].data2,
				                 suite[i].key,NULL);
				break;
		case 4:
				/* No compare function */
				setup = dk_setup(isetup,ifreeSetup,inew,
				                 idestroy,iinsert,
				                 idelete,isearch,
				                 itraverse,idump,
				                 ifirst,ilast,inext,
				                 iprev,NULL,suite[i].data2,
				                 suite[i].key,NULL);
				break;
		case 5:
				/* No search function */
				setup = dk_setup(isetup,ifreeSetup,inew,
				                 idestroy,iinsert,
				                 idelete,NULL,
				                 itraverse,idump,
				                 ifirst,ilast,inext,
				                 iprev,comp,suite[i].data2,
				                 suite[i].key,NULL);
				break;
		case 6:
				/* No optional functions */
				setup = dk_setup(isetup,ifreeSetup,inew,
				                 idestroy,iinsert,
				                 NULL,isearch,NULL,NULL,NULL,
				                 NULL, NULL,NULL,comp,
				                 suite[i].data2,
				                 suite[i].key,
				                 (void*)&suite[i].data);
				break;
		case 7:
				/* No index setup */
				setup = dk_setup(NULL,ifreeSetup,inew,
				                 idestroy,iinsert,
				                 idelete,isearch,
				                 itraverse,idump,
				                 ifirst,ilast,inext,
				                 iprev,comp,suite[i].data2,
				                 suite[i].key,NULL);
				break;
		default:
				/* Normal case */
				setup = dk_setup(isetup,ifreeSetup,inew,
				                 idestroy,iinsert,
				                 idelete,isearch,
				                 itraverse,idump,
				                 ifirst,ilast,inext,
				                 iprev,comp,suite[i].data2,
				                 suite[i].key,NULL);
				break;
			}
			ok = (suite[i].result != (setup == (DK_SETUP) NULL));
			break;

	case SETUPBT:
			/*
			 * Test case:  key    = DK_CHRON or DK_REVERSE
			 *             data2  = DK_SINGLE or DK_SEPARATE
			 *             data   = selects failure mode
			 *             result = 0 if NULL expected
			 */

			switch (suite[i].data)
			{
		case 1:
				/* Invalid tree order */
				setup = dk_setupBtree(-1,comp,suite[i].data2,
				                      suite[i].key,NULL);
				break;

		case 2:
				/* No compare function */
				setup = dk_setupBtree(10,NULL,suite[i].data2,
				                      suite[i].key,NULL);
				break;

		default:
				/* Normal case */
				setup = dk_setupBtree(10,comp,suite[i].data2,
				                      suite[i].key,NULL);
				break;
			}
			ok = (suite[i].result != (setup == (DK_SETUP) NULL));
			break;

	case SETUPDL:
			/*
			 * Test case:  key    = DK_CHRON or DK_REVERSE
			 *             data2  = DK_SINGLE or DK_SEPARATE
			 *             data   = selects failure mode
			 *             result = 0 if NULL expected
			 */

			switch (suite[i].data)
			{
		case 1:
				/* No compare function */
				setup = dk_setupList(NULL,suite[i].data2,
				                     suite[i].key,NULL);
				break;

		default:
				/* Normal case */
				setup = dk_setupList(comp,suite[i].data2,
				                     suite[i].key,NULL);
				break;
			}
			ok = (suite[i].result != (setup == (DK_SETUP) NULL));
			break;

	case FREESETUP:
			printf("Running dk_freeSetup %lx\n", (unsigned long) setup);
			dk_freeSetup(setup);
#if 0
			/*
			 * The following was removed because dk_freeSetup
			 * calls dll_freeSetup.  Thus, the following code
			 * raises a duplicate free error in the malloc library.
			 */
			if ( suite[i].data ) {
				printf(" Running dll_freeSetup %lx\n", (unsigned long) isetup);
				dll_freeSetup(isetup);
			}
#endif
			setup = (DLL_SETUP) NULL;
			isetup = NULL;
			break;

	case NEW:
			/* Test case:  result = 0 if NULL expected */
			index = dk_new(setup);
			ok = (suite[i].result != (index == (DK_DUPKEY) NULL));
			break;

	case DESTROY:
			/* Test case:  result = number of keys to be freed,
			 *             data2  = number of items to be freed,
			 *             key    = 0 if neither free fn is called,
			 *                      FREEKEY if freeKey() only
			 *                      FREEDATA if freeData() only
			 *                      FREEKEY+FREEDATA if both
			 *             data   = info parameter
			 */
			infoOk = 1;
			freeOk = 1;
			lastKey = 0;
			expInfo = &suite[i].data;
			switch (suite[i].key)
			{
		case 0:
				/* Fails only if dumps core or hangs */
				freedKeys = -1;
				freedData = -1;
				dk_destroy(index,NULL,NULL,&suite[i].data);
				break;
		case FREEKEY:
				freedKeys = 0;
				freedData = -1;
				dk_destroy(index,freeKey,NULL,&suite[i].data);
				break;
		case FREEDATA:
				freedKeys = -1;
				freedData = 0;
				dk_destroy(index,NULL,freeData,&suite[i].data);
				break;
		default:
				freedKeys = 0;
				freedData = 0;
				dk_destroy(index,freeKey,freeData,
				           &suite[i].data);
				break;
			}
			index = NULL;
			if (!freeOk || !infoOk) ok = 0;
			if ((freedKeys >= 0) && (freedKeys != suite[i].result))
				ok = 0;
			if ((freedData >= 0) && (freedData != suite[i].data2))
				ok = 0;
			break;

	case INSERT:
			/* Test case:  key    = key to be inserted
			 *             data   = data to be stored with it
			 *             result = expected val of dll_insert()
			 */
			intval = dk_insert(index,
			               suite[i].key ? &suite[i].key : NULL,
			               suite[i].data ? &suite[i].data : NULL);
			if (intval != suite[i].result) ok = 0;
			break;

	case SEARCH:
			/* Test case:  key    = key to be sought
			 *             data   = expected data returned by
			 *                      dk_search
			 *             result = 0 if failure expected
			 */
			ptrval2 = dk_search(index,
			                  suite[i].key ? &suite[i].key : NULL,
			                  suite[i].data ? &ptrval : NULL);
			if (suite[i].key == 0)
			{
				if (ptrval2 != NULL) ok = 0;
			}
			else
			{
				if (ptrval2 == NULL)
				{
					if (suite[i].result) ok = 0;
				}
				else
				{
					if (*(int*)ptrval2 != suite[i].key)
					{
						ok = 0;
					}
				}
			}
			if (suite[i].data != 0)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case FIRST:
			/* Test case:  key    = expected key returned
			 *             data   = expected data
			 *             result = 0 if list is empty
			 */
			ptrval2 = dk_first(index,
			                   suite[i].data ? &ptrval : NULL);
			if (suite[i].result)
			{
				if (*(int*)ptrval2 != suite[i].key) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case LAST:
			/* Test case:  key    = expected key returned
			 *             data   = expected data
			 *             result = 0 if list is empty
			 */
			ptrval2 = dk_last(index,
			                  suite[i].data ? &ptrval : NULL);
			if (suite[i].result)
			{
				if (*(int*)ptrval2 != suite[i].key) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case NEXT:
			/* Test case:  key    = expected key returned
			 *             data   = expected data
			 *             result = 0 if last key was found
			 */
			ptrval2 = dk_next(index,
			                  suite[i].data ? &ptrval : NULL);
			if (suite[i].result)
			{
				if (*(int*)ptrval2 != suite[i].key) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case PREV:
			/* Test case:  key    = expected key returned
			 *             data   = expected data
			 *             result = 0 if first key was found
			 */
			ptrval2 = dk_prev(index,
			                  suite[i].data ? &ptrval : NULL);
			if (suite[i].result)
			{
				if (*(int*)ptrval2 != suite[i].key) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case DELFIRST:
			/* Test case:  key    = key to be deleted
			 *             data   = expected data returned by
			 *                      dll_delete
			 *             data2  = 1 if key is safe to free
			 *             result = 0 if failure expected
			 */
			ptrval2 = dk_delFirst(index,
			                  suite[i].key ? &suite[i].key : NULL,
			                  suite[i].data ? &ptrval : NULL,
			                  &safe);
			if (suite[i].key == 0)
			{
				if (ptrval2 != NULL) ok = 0;
			}
			else
			{
				if (ptrval2 == NULL)
				{
					if (suite[i].result) ok = 0;
				}
				else
				{
					if (*(int*)ptrval2 != suite[i].key)
					{
						ok = 0;
					}
				}
			}
			if (suite[i].data != 0)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			if (ok && ptrval2) ok = ( ! safe == ! suite[i].data2 );
			break;

	case DELLAST:
			/* Test case:  key    = key to be deleted
			 *             data   = expected data returned by
			 *                      dll_delete
			 *             data2  = 1 if key is safe to free
			 *             result = 0 if failure expected
			 */
			ptrval2 = dk_delLast(index,
			                  suite[i].key ? &suite[i].key : NULL,
			                  suite[i].data ? &ptrval : NULL,
			                  &safe);
			if (suite[i].key == 0)
			{
				if (ptrval2 != NULL) ok = 0;
			}
			else
			{
				if (ptrval2 == NULL)
				{
					if (suite[i].result) ok = 0;
				}
				else
				{
					if (*(int*)ptrval2 != suite[i].key)
					{
						ok = 0;
					}
				}
			}
			if (suite[i].data != 0)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			if (ok && ptrval2) ok = ( ! safe == ! suite[i].data2 );
			break;

	case TRAVERSE:
			/* Test case:  data   = info passed to dll_traverse
			 *             key    = 0 if NULL passed as fn
			 *             result = the expected number of times
			 *                      visit() is called
			 */
			visited = 0;
			travOk = 1;
			expInfo = &suite[i].data;
			lastKey = 0;
			dk_traverse(index, (suite[i].key ? visit : NULL),
			            &suite[i].data);
			ok = travOk;
			if (visited != suite[i].result) ok = 0;
			break;

	case DATA:
			/* Test case:  data = expected data */
			ptrval = dk_data(index);
			if (suite[i].data != 0)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case SETDATA:
			/* Test case:  data = new data */
			dk_setData(index,&suite[i].data);
			break;

	case DELLIST:
			/* Test case:  key = key of list
			 *             result = 0 if fail, 1 if success
			 *
			 * list points to linked list of deleted items
			 */
			list = dk_delList(index,
			                  suite[i].key ? &suite[i].key : NULL);
			if ((list == NULL) != (suite[i].result == 0))
			{
				ok = 0;
			}
			break;

	case LFIRST:
			/* Test case:  key = expected key
			 *             data = expected data, 0 if NULL
			 *             result = 0 if list is empty
			 */
			ptrval2 = dll_first(list,
			                    suite[i].data ? &ptrval : NULL);
			if (suite[i].result)
			{
				if (*(int*)ptrval2 != suite[i].key) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case LNEXT:
			/* Test case:  key    = expected key returned
			 *             data   = expected data
			 *             result = 0 if last key was found
			 */
			ptrval2 = dll_next(list,
			                   suite[i].data ? &ptrval : NULL);
			if (suite[i].result)
			{
				if (*(int*)ptrval2 != suite[i].key) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case LDATA:
			/* Test case:  data = expected data */
			ptrval = dll_data(list);
			if (suite[i].data != 0)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			else
			{
				if (ptrval != NULL) ok = 0;
			}
			break;

	case LDESTROY:
			/* Test case:  No data */
			dll_destroy(list,NULL,NULL,NULL);
			list = NULL;
			break;

	case DUMP:
			dk_dump(index,dumpKey,NULL);
			break;

	default:
			break;
		}

		/* Note test case failure */
		if (!ok) fail = 1;

		/* Display result of test case */
		printf("%4.4d %-9.9s %5.4d %5.4d %5.4d  %5.4d   %5.4d   ",
		       i,opnames[suite[i].op],suite[i].key,suite[i].data,
		       suite[i].data2,suite[i].result,intval);
		if (ptrval == NULL) printf(" NULL   ");
		else printf("%5.4d   ",*(int*)ptrval);
		if (ptrval2 == NULL) printf(" NULL    ");
		else printf("%5.4d    ",*(int*)ptrval2);
		if (ok) printf("yes  ");
		else printf("no   ");
		printf("\n");

		/* Dump the list if requested */
		if ((suite[i].dump) && (index != NULL))
		{
			printf("Contents of index:\n");
			dk_dump(index,dumpKey,NULL);
		}
	}
	if (suite[i].op == END)
	{
		i = done;
	}

	/* Display summary */
	printf("TEST %s\n",(fail ? "FAILED" : "PASSED"));

#ifdef GCT
	gct_writelog("gct-log");
#endif

	/* Return 0 on success, non-zero on failure */
	return ((i != done) || fail);
}

/********* End of file *********/

