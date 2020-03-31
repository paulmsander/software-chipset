/*******************************************************************
 *
 * test.c -- This program exercises the readln function and its
 *           derivatives.
 *
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readln.h"

char	*file = "test.in";

int main()
{
	char	b[200];
	char	*l1;
	char	*l2;
	FILE	*f;
	int	ok;
	int	len;

	/* Bump stdin to data file for testing readln */
	f = freopen(file,"r",stdin);
	if ( ! f )
	{
		perror("Failed to reopen stdin");
		exit(1);
	}

	/* Open data file for testing */
	f = fopen(file,"r");
	if ( ! f )
	{
		perror("Failed to open test data");
		exit(1);
	}

	ok = 1;
	do
	{
		l1 = fgets(b,sizeof(b),f);
		if ( l1 )
		{
			if ((( len = strlen(l1) ) > 0 ) && ( b[len-1] == '\n' ))
			{
				b[len-1] = '\0';
			}
			printf("< %s\n",l1);
		}

		l2 = readln();
		if ( l2 )
		{
			printf("> %s\n",l2);
		}

		printf(": %d %d\n", (!l1), (!l2));

		ok = (( ! l1 ) == ( ! l2 ) );
		ok = ( ok && l1 ? ( strcmp(l1,l2) == 0 ) : ok );
	} while ( ok && l1 && l2 );

	xfreeln();
	xfreeln();

	printf("Test %s\n", ( ok ? "PASSED" : "FAILED" ));

#ifdef GCT
	gct_writelog("gct-log");
#endif

	return ( ! ok );
}
