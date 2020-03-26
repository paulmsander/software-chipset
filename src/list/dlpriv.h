/*****************************************************************
 *
 * dlpriv.h -- This file contains private declarations and
 *             definitions used by the in-memory doubly-linked
 *             list implemenation.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *****************************************************************/

#include "dlist.h"

#ifdef __STDC__
typedef int (*COMPFN)(void*,void*);
#else
typedef int (*COMPFN)();
#endif

struct node {
	struct node	*next;
	struct node	*prev;
	void		*key;
	void		*data;
};

struct list {
	struct node	*last;
	struct node	*current;
	void		*data;
	COMPFN		comp;
	int		nextOk;
	int		size;
	int		changed;
};

struct setup {
	COMPFN		comp;
	void		*data;
};

typedef struct node NODE;
typedef struct list LIST;
typedef struct setup SETUP;

#ifdef __STDC__

extern	NODE	*dll_newNode(void*,void*);
extern	void	dll_store(NODE*,NODE*);
extern	void	dll_unlink(NODE*);
extern	void	dll_freeNode(NODE*);
extern	int	dll_locate(LIST*,void*,NODE**);
extern	void	dll_touch(LIST*);
extern	NODE	*dll_locRank(LIST*,int);

#else

extern	NODE	*dll_newNode();
extern	void	dll_store();
extern	void	dll_unlink();
extern	void	dll_freeNode();
extern	int	dll_locate();
extern	void	dll_touch();
extern	NODE	*dll_locRank();

#endif

#ifdef COVERAGE
#define COVER(fn,loc)   printf("Coverage:  file %s, location %03d\n",fn,loc)
#else
#define COVER(file,loc)
#endif

/************** End of file ***************/

