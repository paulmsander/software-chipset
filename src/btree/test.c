/************************************************************************
 *
 * test.c -- This program tests the in-memory B-tree implementation.  It
 *           attempts to cover all branches of control less those taken
 *           when malloc fails.  Perhaps one day a debugging allocator can
 *           be hooked in to test those as well.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ************************************************************************/

#include <stdio.h>
#include "btree.h"

/* These are the B-tree operations that the program tests */

enum ops { SETUP, FREESETUP, NEW, DESTROY, INSERT, DELETE, SEARCH,
           TRAVERSE, FIRST, LAST, NEXT, PREV, RANK, DELRANK, DATA, SETDATA,
           END
};

typedef enum ops OP;

char *opnames[] = {"setup","freesetup","new","destroy","insert","delete",
                   "search","traverse","first","last","next","prev","rank",
                   "delrank","data","setdata","end"
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
	int	dump;		/* If not zero, dumps tree for debugging */
};

typedef struct testcase CASE;

/* Value of "key" when calling bt_destroy */
#define	FREEKEY		1	/* call freeKey() */
#define	FREEDATA	2	/* call freeData() */

/* This is the list of test cases that make up the suite. */

CASE suite[] = {
/* ------------	OP		key	data	data2	result	dump	*/
	{	SETUP,		0,	0,	0,	0,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	0,	0	},
	{	DESTROY,	0,	0,	0,	0,	0	},
	{	INSERT,		0,	0,	0,	0,	0	},
	{	DELETE,		0,	0,	0,	0,	0	},
	{	SEARCH,		0,	0,	0,	0,	0	},
	{	TRAVERSE,	1,	0,	0,	0,	0	},
	{	FIRST,		0,	0,	0,	0,	0	},
	{	LAST,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	RANK,		0,	0,	0,	0,	0	},
	{	DELRANK,	0,	0,	0,	0,	0	},
	{	SETDATA,	0,	0,	0,	0,	0	},
	{	DATA,		0,	0,	0,	0,	0	},
	{	SETUP,		0,	1,	0,	0,	0	},
	{	SETUP,		2,	1,	1,	0,	0	},
	{	SETUP,		3,	0,	1,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	DELETE,		0,	0,	0,	0,	0	},
	{	SEARCH,		0,	0,	0,	0,	0	},
	{	TRAVERSE,	1,	0,	0,	0,	0	},
	{	FIRST,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	LAST,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	FIRST,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	LAST,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	RANK,		0,	0,	0,	0,	0	},
	{	DELRANK,	0,	0,	0,	0,	0	},
	{	SETDATA,	0,	5,	0,	0,	0	},
	{	DATA,		0,	5,	0,	0,	0	},
	{	DELETE,		5,	0,	0,	0,	0	},
	{	SEARCH,		5,	0,	0,	0,	0	},
	{	RANK,		-1,	0,	0,	0,	0	},
	{	RANK,		2,	0,	0,	0,	0	},
	{	DELRANK,	-1,	0,	0,	0,	0	},
	{	DELRANK,	2,	0,	0,	0,	0	},
	{	DESTROY,	0,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		500,	0,	0,	1,	0	},
	{	INSERT,		500,	0,	0,	-1,	0	},
	{	SEARCH,		500,	0,	0,	1,	0	},
	{	TRAVERSE,	1,	20,	0,	1,	0	},
	{	TRAVERSE,	0,	0,	0,	0,	0	},
	{	FIRST,		500,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	SEARCH,		250,	0,	0,	0,	0	},
	{	NEXT,		500,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	LAST,		500,	0,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	SEARCH,		750,	0,	0,	0,	0	},
	{	PREV,		500,	0,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	RANK,		0,	0,	0,	500,	0	},
	{	RANK,		1,	0,	0,	0,	0	},
	{	DELRANK,	1,	0,	0,	0,	0	},
	{	DESTROY,	0,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		600,	20,	0,	1,	0	},
	{	INSERT,		600,	30,	0,	-1,	0	},
	{	SEARCH,		600,	0,	0,	1,	0	},
	{	SEARCH,		600,	20,	0,	1,	0	},
	{	TRAVERSE,	1,	50,	0,	1,	0	},
	{	FIRST,		600,	0,	0,	1,	0	},
	{	FIRST,		600,	20,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	SEARCH,		250,	0,	0,	0,	0	},
	{	NEXT,		600,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	SEARCH,		250,	0,	0,	0,	0	},
	{	NEXT,		600,	20,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	LAST,		600,	0,	0,	1,	0	},
	{	LAST,		600,	20,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	SEARCH,		750,	0,	0,	0,	0	},
	{	PREV,		600,	0,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	SEARCH,		750,	0,	0,	0,	0	},
	{	PREV,		600,	20,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	RANK,		0,	0,	0,	600,	0	},
	{	RANK,		0,	20,	0,	600,	0	},
	{	DESTROY,	0,	0,	0,	0,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		500,	50,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	INSERT,		900,	90,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	INSERT,		100,	10,	0,	1,	0	},
	{	INSERT,		200,	20,	0,	1,	0	},
	{	INSERT,		800,	80,	0,	1,	0	},
	{	INSERT,		700,	70,	0,	1,	0	},
	{	INSERT,		1000,	100,	0,	1,	0	},
	{	INSERT,		600,	60,	0,	1,	0	},
	{	TRAVERSE,	1,	0,	0,	8,	0	},
	{	INSERT,		0,	0,	0,	0,	0	},
	{	INSERT,		500,	0,	0,	-1,	0	},
	{	INSERT,		900,	0,	0,	-1,	0	},
	{	INSERT,		100,	0,	0,	-1,	0	},
	{	INSERT,		200,	0,	0,	-1,	0	},
	{	INSERT,		800,	0,	0,	-1,	0	},
	{	INSERT,		700,	0,	0,	-1,	0	},
	{	INSERT,		1000,	0,	0,	-1,	0	},
	{	INSERT,		600,	0,	0,	-1,	0	},
	{	SEARCH,		50,	0,	0,	0,	0	},
	{	SEARCH,		100,	0,	0,	1,	0	},
	{	SEARCH,		150,	0,	0,	0,	0	},
	{	SEARCH,		200,	0,	0,	1,	0	},
	{	SEARCH,		250,	0,	0,	0,	0	},
	{	SEARCH,		500,	0,	0,	1,	0	},
	{	SEARCH,		550,	0,	0,	0,	0	},
	{	SEARCH,		600,	0,	0,	1,	0	},
	{	SEARCH,		650,	0,	0,	0,	0	},
	{	SEARCH,		700,	0,	0,	1,	0	},
	{	SEARCH,		750,	0,	0,	0,	0	},
	{	SEARCH,		800,	0,	0,	1,	0	},
	{	SEARCH,		850,	0,	0,	0,	0	},
	{	SEARCH,		900,	0,	0,	1,	0	},
	{	SEARCH,		950,	0,	0,	0,	0	},
	{	SEARCH,		1000,	0,	0,	1,	0	},
	{	SEARCH,		1100,	0,	0,	0,	0	},
	{	FIRST,		100,	0,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	NEXT,		100,	10,	0,	1,	0	},
	{	LAST,		1000,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	PREV,		1000,	100,	0,	1,	0	},
	{	SEARCH,		50,	0,	0,	0,	0	},
	{	NEXT,		100,	10,	0,	1,	0	},
	{	NEXT,		200,	20,	0,	1,	0	},
	{	NEXT,		500,	50,	0,	1,	0	},
	{	NEXT,		600,	60,	0,	1,	0	},
	{	NEXT,		700,	0,	0,	1,	0	},
	{	NEXT,		800,	0,	0,	1,	0	},
	{	NEXT,		900,	0,	0,	1,	0	},
	{	NEXT,		1000,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	SEARCH,		1100,	0,	0,	0,	0	},
	{	PREV,		1000,	100,	0,	1,	0	},
	{	PREV,		900,	90,	0,	1,	0	},
	{	PREV,		800,	80,	0,	1,	0	},
	{	PREV,		700,	70,	0,	1,	0	},
	{	PREV,		600,	0,	0,	1,	0	},
	{	PREV,		500,	0,	0,	1,	0	},
	{	PREV,		200,	0,	0,	1,	0	},
	{	PREV,		100,	0,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	INSERT,		300,	30,	0,	1,	0	},
	{	INSERT,		50,	5,	0,	1,	0	},
	{	INSERT,		1100,	110,	0,	1,	0	},
	{	SEARCH,		10,	0,	0,	0,	0	},
	{	NEXT,		50,	5,	0,	1,	0	},
	{	NEXT,		100,	10,	0,	1,	0	},
	{	NEXT,		200,	20,	0,	1,	0	},
	{	NEXT,		300,	30,	0,	1,	0	},
	{	NEXT,		500,	50,	0,	1,	0	},
	{	NEXT,		600,	60,	0,	1,	0	},
	{	NEXT,		700,	0,	0,	1,	0	},
	{	NEXT,		800,	0,	0,	1,	0	},
	{	NEXT,		900,	0,	0,	1,	0	},
	{	NEXT,		1000,	0,	0,	1,	0	},
	{	NEXT,		1100,	0,	0,	1,	0	},
	{	NEXT,		0,	0,	0,	0,	0	},
	{	SEARCH,		1200,	0,	0,	0,	0	},
	{	PREV,		1100,	110,	0,	1,	0	},
	{	PREV,		1000,	100,	0,	1,	0	},
	{	PREV,		900,	90,	0,	1,	0	},
	{	PREV,		800,	80,	0,	1,	0	},
	{	PREV,		700,	70,	0,	1,	0	},
	{	PREV,		600,	0,	0,	1,	0	},
	{	PREV,		500,	0,	0,	1,	0	},
	{	PREV,		300,	0,	0,	1,	0	},
	{	PREV,		200,	0,	0,	1,	0	},
	{	PREV,		100,	0,	0,	1,	0	},
	{	PREV,		50,	0,	0,	1,	0	},
	{	PREV,		0,	0,	0,	0,	0	},
	{	RANK,		0,	5,	0,	50,	0	},
	{	RANK,		1,	10,	0,	100,	0	},
	{	RANK,		2,	20,	0,	200,	0	},
	{	RANK,		3,	30,	0,	300,	0	},
	{	RANK,		4,	50,	0,	500,	0	},
	{	RANK,		6,	70,	0,	700,	0	},
	{	RANK,		10,	110,	0,	1100,	0	},
	{	RANK,		11,	0,	0,	0,	0	},
	{	DESTROY,	1,	0,	0,	11,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	SETUP,		5,	0,	1,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	TRAVERSE,	1,	23,	0,	0,	0	},
	{	INSERT,		3000,	300,	0,	1,	0	},
	{	INSERT,		5000,	500,	0,	1,	0	},
	{	INSERT,		7000,	700,	0,	1,	0	},
	{	INSERT,		9000,	900,	0,	1,	0	},
	{	INSERT,		2000,	200,	0,	1,	0	},
	{	INSERT,		4000,	400,	0,	1,	0	},
	{	INSERT,		1000,	100,	0,	1,	0	},
	{	INSERT,		4500,	450,	0,	1,	0	},
	{	INSERT,		3500,	350,	0,	1,	0	},
	{	INSERT,		2500,	250,	0,	1,	0	},
	{	INSERT,		8000,	800,	0,	1,	0	},
	{	INSERT,		500,	50,	0,	1,	0	},
	{	INSERT,		1500,	150,	0,	1,	0	},
	{	INSERT,		6000,	600,	0,	1,	0	},
	{	INSERT,		3750,	375,	0,	1,	0	},
	{	INSERT,		7500,	750,	0,	1,	0	},
	{	INSERT,		2750,	275,	0,	1,	0	},
	{	INSERT,		4750,	475,	0,	1,	0	},
	{	INSERT,		3250,	325,	0,	1,	0	},
	{	DELRANK,	0,	50,	0,	500,	0	},
	{	DELRANK,	2,	200,	0,	2000,	0	},
	{	DELRANK,	5,	325,	0,	3250,	0	},
	{	INSERT,		3250,	325,	0,	1,	0	},
	{	INSERT,		2000,	200,	0,	1,	0	},
	{	INSERT,		8500,	850,	0,	1,	0	},
	{	INSERT,		9500,	950,	0,	1,	0	},
	{	INSERT,		3300,	330,	0,	1,	0	},
	{	DELETE,		4000,	400,	0,	1,	0	},
	{	DELETE,		9250,	0,	0,	0,	0	},
	{	DELETE,		6000,	600,	0,	1,	0	},
	{	DELETE,		9500,	950,	0,	1,	0	},
	{	INSERT,		6000,	600,	0,	1,	0	},
	{	INSERT,		9500,	950,	0,	1,	0	},
	{	INSERT,		4000,	400,	0,	1,	0	},
	{	INSERT,		6500,	650,	0,	1,	0	},
	{	INSERT,		8750,	875,	0,	1,	0	},
	{	INSERT,		5500,	550,	0,	1,	0	},
	{	DELETE,		6500,	0,	0,	1,	0	},
	{	DELETE,		7000,	0,	0,	1,	0	},
	{	DELRANK,	13,	500,	0,	5000,	0	},
	{	INSERT,		500,	50,	0,	1,	0	},
	{	INSERT,		9200,	920,	0,	1,	0	},
	{	INSERT,		9600,	960,	0,	1,	0	},
	{	INSERT,		4100,	410,	0,	1,	0	},
	{	INSERT,		4200,	420,	0,	1,	0	},
	{	INSERT,		3100,	310,	0,	1,	0	},
	{	INSERT,		3200,	320,	0,	1,	0	},
	{	INSERT,		1100,	110,	0,	1,	0	},
	{	INSERT,		1200,	120,	0,	1,	0	},
	{	INSERT,		1300,	130,	0,	1,	0	},
	{	INSERT,		1400,	140,	0,	1,	0	},
	{	INSERT,		1600,	160,	0,	1,	0	},
	{	INSERT,		1700,	170,	0,	1,	0	},
	{	INSERT,		1800,	180,	0,	1,	0	},
	{	INSERT,		8250,	825,	0,	1,	0	},
	{	DELETE,		3100,	0,	0,	1,	0	},
	{	DELETE,		3200,	0,	0,	1,	0	},
	{	INSERT,		3200,	320,	0,	1,	0	},
	{	INSERT,		3100,	310,	0,	1,	0	},
	{	DESTROY,	3,	0,	0,	36,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		100,	0,	0,	1,	0	},
	{	INSERT,		99,	0,	0,	1,	0	},
	{	INSERT,		98,	0,	0,	1,	0	},
	{	INSERT,		97,	0,	0,	1,	0	},
	{	INSERT,		96,	0,	0,	1,	0	},
	{	INSERT,		95,	0,	0,	1,	0	},
	{	INSERT,		94,	0,	0,	1,	0	},
	{	INSERT,		93,	0,	0,	1,	0	},
	{	INSERT,		92,	0,	0,	1,	0	},
	{	INSERT,		91,	0,	0,	1,	0	},
	{	INSERT,		90,	0,	0,	1,	0	},
	{	INSERT,		89,	0,	0,	1,	0	},
	{	INSERT,		88,	0,	0,	1,	0	},
	{	INSERT,		87,	0,	0,	1,	0	},
	{	INSERT,		86,	0,	0,	1,	0	},
	{	INSERT,		85,	0,	0,	1,	0	},
	{	INSERT,		84,	0,	0,	1,	0	},
	{	INSERT,		83,	0,	0,	1,	0	},
	{	INSERT,		82,	0,	0,	1,	0	},
	{	INSERT,		81,	0,	0,	1,	0	},
	{	INSERT,		80,	0,	0,	1,	0	},
	{	INSERT,		79,	0,	0,	1,	0	},
	{	INSERT,		78,	0,	0,	1,	0	},
	{	INSERT,		77,	0,	0,	1,	0	},
	{	INSERT,		76,	0,	0,	1,	0	},
	{	INSERT,		75,	0,	0,	1,	0	},
	{	INSERT,		74,	0,	0,	1,	0	},
	{	INSERT,		73,	0,	0,	1,	0	},
	{	INSERT,		72,	0,	0,	1,	0	},
	{	INSERT,		71,	0,	0,	1,	0	},
	{	INSERT,		70,	0,	0,	1,	0	},
	{	INSERT,		69,	0,	0,	1,	0	},
	{	DESTROY,	3,	0,	0,	32,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
	{	SETUP,		10,	0,	1,	1,	0	},
	{	NEW,		0,	0,	0,	1,	0	},
	{	INSERT,		2,	20,	0,	1,	0	},
	{	INSERT,		3,	30,	0,	1,	0	},
	{	INSERT,		4,	40,	0,	1,	0	},
	{	INSERT,		5,	50,	0,	1,	0	},
	{	INSERT,		6,	60,	0,	1,	0	},
	{	INSERT,		7,	70,	0,	1,	0	},
	{	INSERT,		8,	80,	0,	1,	0	},
	{	INSERT,		9,	90,	0,	1,	0	},
	{	INSERT,		10,	100,	0,	1,	0	},
	{	SEARCH,		2,	0,	0,	1,	0	},
	{	SEARCH,		3,	0,	0,	1,	0	},
	{	SEARCH,		4,	0,	0,	1,	0	},
	{	SEARCH,		5,	0,	0,	1,	0	},
	{	SEARCH,		6,	0,	0,	1,	0	},
	{	SEARCH,		7,	0,	0,	1,	0	},
	{	SEARCH,		8,	0,	0,	1,	0	},
	{	SEARCH,		9,	0,	0,	1,	0	},
	{	SEARCH,		10,	0,	0,	1,	0	},
	{	SEARCH,		1,	0,	0,	0,	0	},
	{	SEARCH,		11,	0,	0,	0,	0	},
	{	DESTROY,	2,	0,	0,	9,	0	},
	{	FREESETUP,	0,	0,	0,	0,	0	},
/* ------------	OP		key	data	data2	result	dump	*/
	{	END,		0,	0,	0,	0,	0	}
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
	printf("key = %4.4d, data = ",*(int*)key);
	if (data != NULL) printf("%4.4d\n",*(int*)data);
	else printf("(NULL)\n");
	return;
}

/*
 * These functions are called by bt_destroy, and count the number of
 * key and data structures are freed, and also verify that the info
 * parameter is passed properly.  Some attempt is made to be sure that
 * the data are freed before the key.
 */

int	freedKeys;	/* Number of keys freed */
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
	freedKeys++;
	if ((int*) info != expInfo) infoOk = 0;
	if ((freedData >= 0) && (freedKeys != freedData)) freeOk = 0;
}

#ifdef __STDC__
void freeData(void *key, void *info)
#else
void freeData(key,info)
void	*key;
void	*info;
#endif
{
	if ((freedKeys >= 0) && (freedKeys != freedData)) freeOk = 0;
	freedData++;
	if ((int*) info != expInfo) infoOk = 0;
}

/*
 * The following variables and the visit() function are used for testing
 * the bt_traverse() function.
 */

int	lastKey;	/* Last key encountered by bt_traverse */
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
	if ((lastKey != 0) && (*(int*)key <= lastKey)) travOk = 0;
	else if ((int*) info != expInfo) travOk = 0;
	lastKey = *(int*) key;
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
	BTREE		tree;		/* B-tree under test */
	BT_SETUP	setup;		/* Configuration data for B-tree */

	/* Initialization */
	fail = 0;
	tree = (BTREE) NULL;
	setup = (BT_SETUP) NULL;

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
	case SETUP:
			/*
			 * Test case:  key = B-tree order,
			 *             data2 = 0 if no comparison function,
			 *             data = global data,
			 *             result = 0 if NULL expected
			 */
			setup = bt_setup(suite[i].key,
			          (suite[i].data2 ? comp : (int (*)()) NULL),
			          (void*) (suite[i].data ? &suite[i].data
			                                 : NULL));
			ok = (suite[i].result != (setup == (BT_SETUP) NULL));
			break;

	case FREESETUP:
			bt_freeSetup(setup);
			setup = (BT_SETUP) NULL;
			break;

	case NEW:
			/* Test case:  result = 0 if NULL expected */
			tree = bt_new(setup);
			ok = (suite[i].result != (tree == (BTREE) NULL));
			break;

	case DESTROY:
			/* Test case:  result = number of keys to be freed,
			 *             key    = 0 if neither free fn is called,
			 *                      FREEKEY if freeKey() only
			 *                      FREEDATA if freeData() only
			 *                      FREEKEY+FREEDATA if both
			 *             data   = info parameter
			 */
			infoOk = 1;
			freeOk = 1;
			expInfo = &suite[i].data;
			switch (suite[i].key)
			{
		case 0:
				/* Fails only if dumps core or hangs */
				freedKeys = -1;
				freedData = -1;
				bt_destroy(tree,NULL,NULL,&suite[i].data);
				break;
		case FREEKEY:
				freedKeys = 0;
				freedData = -1;
				bt_destroy(tree,freeKey,NULL,&suite[i].data);
				break;
		case FREEDATA:
				freedKeys = -1;
				freedData = 0;
				bt_destroy(tree,NULL,freeData,&suite[i].data);
				break;
		default:
				freedKeys = 0;
				freedData = 0;
				bt_destroy(tree,freeKey,freeData,
				           &suite[i].data);
				break;
			}
			tree = NULL;
			if (!freeOk || !infoOk) ok = 0;
			if ((freedKeys >= 0) && (freedKeys != suite[i].result))
				ok = 0;
			if ((freedData >= 0) && (freedData != suite[i].result))
				ok = 0;
			break;

	case INSERT:
			/* Test case:  key    = key to be inserted
			 *             data   = data to be stored with it
			 *             result = expected val of bt_insert()
			 */
			intval = bt_insert(tree,
			                suite[i].key ? &suite[i].key : NULL,
			                suite[i].data ? &suite[i].data : NULL);
			if (intval != suite[i].result) ok = 0;
			break;

	case DELETE:
			/* Test case:  key    = key to be deleted
			 *             data   = expected data returned by
			 *                      bt_delete
			 *             result = 0 if failure expected
			 */
			ptrval2 = bt_delete(tree,
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

	case SEARCH:
			/* Test case:  key    = key to be sought
			 *             data   = expected data returned by
			 *                      bt_search
			 *             result = 0 if failure expected
			 */
			ptrval2 = bt_search(tree,
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

	case TRAVERSE:
			/* Test case:  data   = info passed to bt_traverse
			 *             key    = 0 if NULL is passed as fn
			 *             result = the expected number of times
			 *                      visit() is called
			 */
			visited = 0;
			travOk = 1;
			expInfo = &suite[i].data;
			lastKey = 0;
			bt_traverse(tree, (suite[i].key ? visit : NULL),
			            &suite[i].data);
			ok = travOk;
			if (visited != suite[i].result) ok = 0;
			break;

	case FIRST:
			/* Test case:  key    = expected key returned
			 *             data   = expected data
			 *             result = 0 if tree is empty
			 */
			ptrval2 = bt_first(tree,
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
			 *             result = 0 if tree is empty
			 */
			ptrval2 = bt_last(tree,
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
			ptrval2 = bt_next(tree,
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
			ptrval2 = bt_prev(tree,
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

	case RANK:
			/* Test case:  key    = rank searched for
			 *             data   = expected data
			 *             result = expected key
			 */
			ptrval2 = bt_rank(tree,suite[i].key,
			                  suite[i].data ? &ptrval : NULL);
			if (suite[i].result != 0)
			{
				if (*(int*)ptrval2 != suite[i].result) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data != 0)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			break;

	case DELRANK:
			/* Test case:  key    = rank to be deleted
			 *             data   = expected data
			 *             result = expected key
			 */
			ptrval2 = bt_delRank(tree,suite[i].key,
			                     suite[i].data ? &ptrval : NULL);
			if (suite[i].result != 0)
			{
				if (*(int*)ptrval2 != suite[i].result) ok = 0;
			}
			else
			{
				if (ptrval2 != NULL) ok = 0;
			}
			if (suite[i].data != 0)
			{
				if (*(int*)ptrval != suite[i].data) ok = 0;
			}
			break;

	case DATA:
			/* Test case:  data = expected data */
			ptrval = bt_data(tree);
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
			bt_setData(tree,&suite[i].data);
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

		/* Dump the tree if requested */
		if ((suite[i].dump) && (tree != NULL))
		{
			printf("Contents of tree:\n");
			bt_dump(tree,dumpKey,NULL);
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

