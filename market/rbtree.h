/*	------------------------------------------------
	
	rbtree.h - High-level interface to RBTree storage

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#ifndef _RBTREE_H_
#define _RBTREE_H_

#include "types.h"

void treeAdd(T value);
void treeFree(void);
int treeSearch(T val);
struct Line * treeLine(void);

#endif