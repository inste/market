/*	------------------------------------------------
	
	itemdiff.c - Predicates for sorting with qsort()

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"

// Ascending order

int ItemDifference(const void * p1, const void * p2) {
	return ((struct Item *)p1)->m_barCode - ((struct Item *)p2)->m_barCode;
}

int BillItemDifference(const void * p1, const void * p2) {
	return ((struct BillItem *)p1)->m_item->m_barCode - ((struct BillItem *)p2)->m_item->m_barCode;
}

// Descending order

int LineItemDifference(const void * p1, const void * p2) {
	return ((struct lCouple *)p2)->count - ((struct lCouple *)p1)->count;
}