/*	------------------------------------------------
	
	types.h - Definition of the types

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#ifndef _TYPES_H
#define _TYPES_H

struct Item {
	int m_barCode;
	char m_name[86];
	int m_price;
};

struct ItemDatabase{
	int m_count;
	struct Item * m_items;
};

struct BillItem {
	const struct Item * m_item;
	int m_quantity;
};

struct Bill {
	int m_count;
	struct BillItem * m_items;
};

struct Billboard {
	int m_count;
	struct Bill * m_items;
};

/*
	We will store smaller barCode in 1 and 2 bytes of long int,
	and bigger in 3 and 4 
*/

typedef unsigned long int T;

/* linearize */

struct lCouple {
	T barCode;
	int count;
};

struct Line {
	struct lCouple * m_items;
	int count;
	int pos;
};

#endif

