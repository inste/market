/*	------------------------------------------------
	
	allocitem.c - Allocating new Item

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"

struct Item * AllocItem(int barCode, char * name, int price) {
	struct Item * res = malloc(sizeof(struct Item));
	
	res->m_barCode = barCode;
	res->m_price = price;
	strcpy(res->m_name, name);
	return res;
} 
