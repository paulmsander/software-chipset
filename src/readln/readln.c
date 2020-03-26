/********************************************************************
 *
 * readln.c -- This file contains a function that performs a "safe"
 *             read from stdin into a static area.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ********************************************************************/

#include <stdio.h>
#include "readln.h"

/*
 * read a line of input safely from stdin.
 * This function safely reads an entire line of input from stdin.
 * returns a pointer to a static buffer containing the text from the input
 * stream.
 */
#ifdef __STDIN__
char *readln(void)
#else
char *readln()
#endif
{
	return freadln(stdin);
}
