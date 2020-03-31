/*********************************************************************
 * 
 * btinsert.c -- This file contains functions needed to insert new
 *               items into an in-memory B-tree.
 *
 * This file is part of a suite of programs called Software Chipset.
 * The source code for Software Chipset has been released into the
 * public domain by its author, Paul Sander.
 *
 *********************************************************************/

#include <stdio.h>
#include "btpriv.h"


/*********************************************************************
 *                                                                   *
 * bt_createNode -- This function allocates a node on the heap, and  *
 *                  returns a pointer to it to the caller.  If an    *
 *                  error occurs, any storage allocated is freed,    *
 *                  and NULL is returned.                            *
 *                                                                   *
 *********************************************************************/

#ifdef __STDC__
static BTNODE *bt_createNode(BTREE tree, int children)
#else
static BTNODE *bt_createNode(tree,children)
BTREE	tree;
int	children;
#endif
{
	BTNODE	*new;

	new = (BTNODE*) bt_malloc(sizeof(BTNODE));
	if (new != NULL)
	{
		new->keys = (void **) bt_malloc((tree->order-1)*sizeof(void*));
		if (new->keys != NULL)
		{
			new->data = (void **) bt_malloc(
			                         (tree->order-1)*sizeof(void*));
			if (new->data != NULL)
			{
				COVER("btinsert.c",1);
				if (children)
				{
					COVER("btinsert.c",2);
					new->children = (BTNODE**) bt_malloc(
					      (tree->order) * sizeof(BTNODE*));
					if (new->children != NULL)
					{
						return new;
					}
				}
				else
				{
					COVER("btinsert.c",3);
					new->children = NULL;
					return new;
				}
				bt_free(new->data);
			}
			bt_free(new->keys);
		}
		bt_free(new);
	}
	return NULL;
}

/*********************************************************************
 *
 * bt_insertKey -- This function inserts a key into a specified node at
 *                 a specified location in its key array.  0 is returned
 *                 if the node is already full, 1 otherwise.
 *
 *********************************************************************/

#ifdef __STDC__
static int bt_insertKey(BTNODE *node, void *key, int n, int order, void *data)
#else
static int bt_insertKey(node,key,n,order,data)
BTNODE	*node;
void	*key;
int	n;
int	order;
void	*data;
#endif
{
	int	i;

	/* Return FALSE if insertion is not possible */
	if (node->nkeys >= order - 1)
	{
		COVER("btinsert.c",4);
		return 0;
	}

	/* Shift keys to make room, then insert new key */
	COVER("btinsert.c",5);
	for (i = node->nkeys - 1; i >= n; i--)
	{
		COVER("btinsert.c",6);
		node->keys[i+1] = node->keys[i];
		node->data[i+1] = node->data[i];
	}
	node->keys[n] = key;
	node->data[n] = data;
	node->nkeys++;
	node->tsize++;
	return 1;
}

/*********************************************************************
 *
 * bt_burst -- Given a node and an index into its key and child arrays,
 *             this function splits the specified child node in half,
 *             elevating the key at the child's split point into this
 *             specified node.  0 is returned if the child array index
 *             is out of range, or the node is full, or malloc fails;
 *             1 is returned otherwise.
 *
 *********************************************************************/

#ifdef __STDC__
static int bt_burst(BTREE tree, BTNODE *node, int n)
#else
static int bt_burst(tree,node,n)
BTREE	tree;
BTNODE	*node;
int	n;
#endif
{
	BTNODE	*new;
	int	i;
	int	m;
	BTNODE	*left;
	int	lkeys;

	/* Test parameters */
	if ((node->nkeys > 0) && (node->nkeys >= tree->order - 1))
	{
		COVER("btinsert.c",7);
		return 0;
	}
	if (n < 0)
	{
		/* This should never happen */
		COVER("btinsert.c",8);
		return 0;
	}

	/* Calculate needed partial results */
	COVER("btinsert.c",9);
	m = tree->order / 2;
	left = node->children[n];
	lkeys = left->nkeys;

	/* Create a new node */
	new = bt_createNode(tree,(left->children != NULL));
	if (new != NULL)
	{
		new->parent = node;
		new->tsize = lkeys - m;

		/* Split child array */
		if (left->children != NULL)
		{
			COVER("btinsert.c",10);
			for (i = 0; i <= lkeys - m; i++)
			{
				COVER("btinsert.c",11);
				new->children[i] = left->children[m + i];
				new->children[i]->parent = new;
				new->tsize += new->children[i]->tsize;
			}
		}

		/* Split keys */
		COVER("btinsert.c",12);
		for (i = 0; i < lkeys - m; i++)
		{
			COVER("btinsert.c",13);
			new->keys[i] = left->keys[m + i];
			new->data[i] = left->data[m + i];
		}
		COVER("btinsert.c",14);
		new->nkeys = lkeys - m;
		left->nkeys = m - 1;
		left->tsize = left->tsize - new->tsize - 1;

		/* Elevate the key where the split was made */
		for (i = node->nkeys; i > n; i--)
		{
			COVER("btinsert.c",15);
			node->keys[i] = node->keys[i-1];
			node->data[i] = node->data[i-1];
			node->children[i+1] = node->children[i];
		}
		COVER("btinsert.c",16);
		node->children[n+1] = new;
		node->keys[n] = left->keys[m - 1];
		node->data[n] = left->data[m - 1];
		node->nkeys++;
		tree->capacity += tree->order - 1;
		return 1;
	}

	/* Failed to allocate new node, return FALSE */
	return 0;
}

/*********************************************************************
 *
 * bt_rebalance -- This function tries to rebalance the two adjacent
 *                 nodes.  This is needed when an insertion is attempted
 *                 into a node that is already full but its neighbors are
 *                 not, or when a deletion is made and the node is less
 *                 than half-full.
 *
 *********************************************************************/

#ifdef __STDC__
static void bt_rebalance(BTNODE *node, int n, int order)
#else
static bt_rebalance(node,n,order)
BTNODE	*node;
int	n;
int	order;
#endif
{
	int	res;

	COVER("btinsert.c",17);
	if (node->children[n]->nkeys < (order-1)/2)
	{
		COVER("btinsert.c",18);
		res = bt_rotateLeft(node,n,order);
	}
	else
	if ((n < node->nkeys) && (node->children[n+1]->nkeys < (order-1)/2))
	{
		/*
		 * It turns out that the only time a tree needs to be
		 * rebalanced by this function is after a burst.  When that
		 * happens, the left child may have one less key than the
		 * right.  If the key is inserted on the right, the left
		 * rotation rebalances.  Otherwise, the key is inserted on
		 * the left, and tree becomes balanced.  Therefore, this
		 * branch should never be taken.
		 */
		COVER("btinsert.c",19);
		res = bt_rotateRight(node,n,order);
	}
	COVER("btinsert.c",20);
	return;
}

/*********************************************************************
 *
 * bt_insertNode -- This function performs a recursive-descent of a b-tree,
 *                  inserting a new key in a leaf node.  If the leaf is
 *                  full, the tree is reorganized to make room.  -1 is
 *                  returned if the insert fails due to a duplicate key.
 *                  0 is returned if the insert fails for some other
 *                  reason.  1 is returned if successful.
 *
 *********************************************************************/

#ifdef __STDC__
static int bt_insertNode(BTREE tree, BTNODE *node, void *key, void *data)
#else
static int bt_insertNode(tree,node,key,data)
BTREE	tree;
BTNODE	*node;
void	*key;
void	*data;
#endif
{
	int	i;
	int	res;

	/* Locate proper place for new key in node */
	i = bt_searchNode(node,key,tree->comp,&res);
	if (res)
	{
		COVER("btinsert.c",21);
		return -1;
	}

	/* If no children, insert key in this node */
	COVER("btinsert.c",22);
	if (node->children == NULL)
	{
		COVER("btinsert.c",23);
		res = bt_insertKey(node,key,i,tree->order,data);
		return res;
	}

	/* Try to insert the new key in a child node */
	res = bt_insertNode(tree,node->children[i],key,data);

	/* Child is full, reorganize */
	COVER("btinsert.c",24);
	if (res == 0)
	{
		COVER("btinsert.c",25);
		/* Try rotating right */
		if ((res == 0) && (i < node->nkeys) &&
		    (node->children[i+1]->nkeys < tree->order - 2))
		{
			COVER("btinsert.c",26);
			res = bt_rotateRight(node,i,tree->order);
		}

		/* Try rotating left */
		COVER("btinsert.c",27);
		if ((res == 0) && (i > 0) &&
		    (node->children[i-1]->nkeys < tree->order - 2))
		{
			COVER("btinsert.c",28);
			res = bt_rotateLeft(node,i - 1,tree->order);
		}

		/* Can't rotate, try bursting */
		COVER("btinsert.c",29);
		if (res == 0)
		{
			COVER("btinsert.c",30);
			res = bt_burst(tree,node,i);
		}
		COVER("btinsert.c",31);
		if (res > 0)
		{
			COVER("btinsert.c",32);
			res = bt_insertNode(tree,node,key,data);
			if (res > 0)
			{
				COVER("btinsert.c",33);
				bt_rebalance(node,i,tree->order);
			}
		}
	}
	else if (res > 0)
	{
		COVER("btinsert.c",34);
		node->tsize++;
	}
	COVER("btinsert.c",35);
	return res;
}

/*********************************************************************
 *
 * bt_insert -- This function inserts a new key into a b-tree.  -1 is
 *              returned if the insert fails due to a duplicate key.
 *              0 is returned if the insert fails for some other
 *              reason.  1 is returned if successful.
 *
 *********************************************************************/

#ifdef __STDC__
int bt_insert(void *ptree, void *key, void *data)
#else
int bt_insert(ptree,key,data)
void	*ptree;
void	*key;
void	*data;
#endif
{
	int	res;
	BTNODE	*new;
	BTNODE	*node;
	BTREE	tree;

	if (ptree == NULL)
	{
		COVER("btinsert.c",36);
		return 0;
	}

	if (key == NULL)
	{
		COVER("btinsert.c",37);
		return 0;
	}

	tree = (BTREE) ptree;

	/* Begin at root */
	node = tree->root;

	/* If root is empty, insert first key */
	COVER("btinsert.c",38);
	if (node->nkeys == 0)
	{
		COVER("btinsert.c",39);
		node->keys[0] = key;
		node->data[0] = data;
		node->nkeys = 1;
		node->tsize = 1;
		tree->currNode = NULL;
		return 1;
	}

	/* Try inserting new key */
	COVER("btinsert.c",40);
	res = bt_insertNode(tree,node,key,data);

	/* If 0 return, burst the root, rebalance, and try again */
	if (res == 0)
	{
		COVER("btinsert.c",41);
		new = bt_createNode(tree,1);
		if (new != NULL)
		{
			new->nkeys = 0;
			new->tsize = node->tsize;
			new->children[0] = node;
			new->parent = NULL;
			node->parent = new;
			tree->root = new;
			tree->capacity += tree->order - 1;
			res = bt_burst(tree,new,0);
			if (res > 0)
			{
				COVER("btinsert.c",42);
				res = bt_insertNode(tree,new,key,data);
			}
			COVER("btinsert.c",43);
			if (res > 0)
			{
				COVER("btinsert.c",44);
				bt_rebalance(new,0,tree->order);
				tree->currNode = NULL;
			}
			COVER("btinsert.c",45);
			return res;
		}
	}
	COVER("btinsert.c",46);
	if (res > 0)
	{
		COVER("btinsert.c",47);
		tree->currNode = NULL;
	}
	COVER("btinsert.c",48);
	return res;
}

/********** End of file ************/

