/*	------------------------------------------------
	
	billboard.c - Operations with array of bills (billboard)

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"


struct Billboard * AddToBillboard(struct Billboard * bboard, struct Bill * bill) {

	if (!bboard) {
		bboard = malloc(sizeof(struct Billboard));
		bboard->m_count = 1;
		bboard->m_items = malloc(sizeof(struct Bill));
		bboard->m_items[0].m_count = bill->m_count;
		bboard->m_items[0].m_items = bill->m_items;
	} else {
		++bboard->m_count;
		bboard->m_items = realloc(bboard->m_items, bboard->m_count * sizeof(struct Bill));
		bboard->m_items[bboard->m_count - 1].m_count = bill->m_count;
		bboard->m_items[bboard->m_count - 1].m_items = bill->m_items;
	}
	return bboard;
}

void FreeBillboard(struct Billboard * bboard) {
	int i;
	
	if (!bboard)
		err(EMEM);
	
	for(i = 0; i < bboard->m_count; ++i)
		free(bboard->m_items[i].m_items);
	free(bboard->m_items);
	free(bboard);
}

