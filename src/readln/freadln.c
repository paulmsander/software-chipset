/********************************************************************
 *
 * freadln.c -- This file contains a function that performs a "safe"
 *              read from a buffered I/O stream into a static area.
 *              Also provided is a function that cleans up any
 *              allocated storage.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ********************************************************************/

#include <stdio.h>
#include "readln.h"

#ifdef __STDC__
#define FGETS_CAST char*(*)(char*, int, void*)
#else
#define FGETS_CAST char*(*)()
#endif

/*
 * read a line of input safely from a buffered file
 * This function safely reads an entire line of input from a buffered I/O
 * stream.
 * returns a pointer to a static buffer containing the text from the input
 * stream.
 */
#ifdef __STDC__
char *freadln(FILE *stream)
#else
char *freadln(stream)
FILE	*stream;	/* Buffered I/O stream */
#endif
{
	return xreadln((void *) stream,(FGETS_CAST) fgets);
}
