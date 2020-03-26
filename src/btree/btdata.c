/***********************************************************************
 *
 * btdata.c -- This file contains functions to access and modify a
 *             a user-defined data structure that can be stored with
 *             a B-tree.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 ***********************************************************************/

#include <stdio.h>
#include "btpriv.h"

/***********************************************************************
 *
 * bt_data -- Given a B-tree, returns a pointer to a user-defined
 *            structure.  This pointer can be set by bt_new(), or
 *            with bt_setData().
 *
 ***********************************************************************/

#ifdef __STDC__
void	*bt_data(void *ptree)
#else
void	*bt_data(ptree)
void	*ptree;
#endif
{
	BTREE	tree;

	if (ptree == NULL)
	{
		COVER("btdata.c",1);
		return NULL;
	}
	COVER("btdata.c",2);
	tree = (BTREE) ptree;
	return tree->data;
}

/***********************************************************************
 *
 * bt_setData -- This function modifies a pointer to a user-defined
 *               structure that is kept with the tree.
 *
 ***********************************************************************/

#ifdef __STDC__
void bt_setData(void *ptree, void *data)
#else
void bt_setData(ptree,data)
void	*ptree;
void	*data;
#endif
{
	BTREE	tree;

	if (ptree != NULL)
	{
		COVER("btdata.c",3);
		tree = (BTREE) ptree;
		tree->data = data;
	}
	COVER("btdata.c",4);
	return;
}

/************ End of file *************/

