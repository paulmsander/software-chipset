/********************************************************************
 *
 * xreadln.c -- This file contains a function that performs a "safe"
 *              read from a generic I/O stream into a static area.
 *              Also provided is a function that cleans up any
 *              allocated storage.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

/*
 * This is the static buffer.  It is allocated on the heap, and signal
 * handlers clean it up.
 */
static	char	*buffer = NULL;
static	int	bufLen = -1;

/* This is the beginning size of the buffer, in bytes */
#define	DEFAULT_SIZE	10

/* This is the buffer size increment */
#define	INC_SIZE	4


/********************************************************************
 *
 * xfreeln -- This function frees the static buffer.
 *
 ********************************************************************/

void xfreeln()
{
	if (bufLen >= 0)
	{
		free(buffer);
		bufLen = -1;
	}
}

/********************************************************************
 *
 * allocBuffer -- This function creates or enlarges the buffer.
 *
 ********************************************************************/

static
char *allocBuffer()
{
	char	*buf;
	int	len;

	if (bufLen < 0)
	{
		len = DEFAULT_SIZE;
		buf = malloc(DEFAULT_SIZE);
	}
	else
	{
		len = bufLen + INC_SIZE;
		buf = realloc(buffer,len);
	}
	if (buf != NULL)
	{
		bufLen = len;
		buffer = buf;
	}
	return buf;
}

/********************************************************************
 *
 * xreadln -- This function performs a "safe" read from the given stream
 *            and returns a pointer to a static buffer, or NULL if an
 *            error occured.  The buffer is overwritten each time readln
 *            is called.  The buffer is null-terminated, and never contains
 *            a newline.
 *
 ********************************************************************/

/*
 * perform a "safe" read from a stream of input
 * This function calls a user-specified function to read text from some
 * source.  The text is read until a newline or EOF is encountered, and
 * the entirety of the text is stored in a static buffer.  This buffer
 * must not be freed by the caller, nor can it be counted on surviving
 * a subsequent call to xreadln().  If the text is needed later, it must
 * be copies elsewhere.  The interface to the user-specified function
 * must be identical to fgets.
 * returns a pointer to the entire line of text
 */

#ifdef __STDC__
char *xreadln(void *stream, char *(*fn)(char*, int, void*))
#else
char *xreadln(stream,fn)
void	*stream;	/* Arbitrary data passed to the user input routine */
char	*(*fn)();	/* User input routine */
#endif
{
	int	i;
	char	*buf;
	int	len;

	/* Allocate the buffer */
	if (buffer == NULL)
	{
		buf = allocBuffer();
		if (buf == NULL) return NULL;
	}

	/* Try reading the file, return null if EOF or error */
	buf = (*fn)(buffer,bufLen,stream);
	if (buf == NULL) return NULL;

	/* Continue reading the file until EOF or error or newline */
	len = strlen(buf);

	/* Note that testing buf for NULL is not necessary at this point
	 * because:
	 * - Loop exits if the buffer is not full
	 * - Buffer expands if full and then addition data are read
	 *   - If either an error or EOF occurs, the buffer is no longer
	 *     full after its expansion.
	 */
	while ((len == bufLen - 1) && (buffer[len-1] != '\n'))
	{
		buf = allocBuffer();
		if (buf == NULL) return NULL;
		buf = (*fn)(&buffer[len],INC_SIZE+1,stream);
		if (buf != NULL) len = len + strlen(buf);
	}

	/* Strip trailing newline */
	if (buffer[len-1] == '\n') buffer[len-1] = '\0';
	return buffer;
}

/*** End of File ***/

