/***************************************************************
 *
 * readln.h -- This file contains public declarations for the
 *             readln functions.
 *
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***************************************************************/

#ifndef READLN_H
#define READLN_H

#include <stdio.h>

#ifdef __STDC__

extern void xfreeln(void);
extern char *xreadln(void*, char *(*fn)(char*, int, void*));
extern char *freadln(FILE*);
extern char *readln(void);

#else

extern void xfreeln();
extern char *xreadln();
extern char *freadln();
extern char *readln();

#endif

#endif
