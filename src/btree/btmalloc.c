/**************************************************************
 *
 * btmalloc.c -- This file contains functions that augment the
 *               C runtime library memory allocator in order
 *               to aid debugging.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 **************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* The following structure is used for debugging heap corruptions */

struct heapblk {
	void	*blk;
	int	freeNext;
};

struct heap_struct {
	int		allocSeq;
	int		freeLast;
	struct heapblk	blks[10000];
};

struct heap_struct btheap = {0,-1}; 


/*
 * The following code is used for allocating space on the heap.  When not
 * debugging heap corruptions, a macro aliases bt_malloc with malloc.
 */

#ifdef __STDC__
void *bt_malloc(unsigned size)
#else
void *bt_malloc(size)
unsigned	size;
#endif
{
	void	*temp;

	temp = (void*) malloc(size);
	btheap.blks[btheap.allocSeq].blk = temp;
	btheap.blks[btheap.allocSeq].freeNext = -2;
	btheap.allocSeq++;
	return temp;
}

/*
 * The following code is used for freeing memory on the heap.  If not
 * debugging heap corruptions, bt_free is aliased with free.
 */

#ifdef __STDC__
void bt_free(void *ptr)
#else
void bt_free(ptr)
void	*ptr;
#endif
{
	int	i;

	printf("Freeing heap storage at %lx\n",(unsigned long) ptr);
	for (i = 0; i < btheap.allocSeq; i++)
	{
		if (ptr == btheap.blks[i].blk)
		{
			if (btheap.blks[i].freeNext == -2)
			{
				btheap.blks[i].freeNext = btheap.freeLast;
				btheap.freeLast = i;
				free(ptr);
				return;
			}
			else
			{
				printf(
				  "ERROR: freeing %lx which was already freed\n",
				  (unsigned long) ptr);
				printf("Block\n");
				i = btheap.freeLast;
				while (i > 0)
				{
					printf("%lx\n",(unsigned long) btheap.blks[i].blk);
					i = btheap.blks[i].freeNext;
				}
				fflush(stdout);
				kill(getpid(),5);
			}
		}
	}
	printf("ERROR:  Freeing %lx which has not been allocated\n",(unsigned long) ptr);
	fflush(stdout);
	kill(getpid(),5);
}

/* The following verifies the integrity of the heap. */

#ifdef __STDC__
int bt_malloc_verify(void)
#else
int bt_malloc_verify()
#endif
{
	int	retval;
	int	once;
	int	i;

	retval = 1;
	once = 0;

#ifdef DEBUG
	for (i = 0; i < btheap.allocSeq; i++)
	{
		if (btheap.blks[i].freeNext == -2)
		{
			if (!once)
			{
				once = 1;
				printf("The following blocks are allocated:\n");
			}
			printf("%x\n",btheap.blks[i].blk);
		}
	}
	fflush(stdout);
#endif

#if 0
#ifdef sun
	retval = malloc_verify();
#endif
#endif

	return retval;
}

/***** End of file *****/

