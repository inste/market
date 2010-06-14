/*	------------------------------------------------
	
	totalsales.c - TotalSales() function

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"

void TotalSales(struct ItemDatabase * db, struct Billboard * bb) {
	struct Item * item;
	int * codes = NULL, * count = NULL;
	int exists = 0, total = 0, totalc = 0, c = 0, i, j, k;
	unsigned int q;
	
	for(i = 0; i < bb->m_count; ++i)
		for(j = 0; j < bb->m_items[i].m_count; ++j) {
			exists = 0;
			for(k = 0; k < c; ++k) 
				if (codes[k] == bb->m_items[i].m_items[j].m_item->m_barCode) {
					count[k] += bb->m_items[i].m_items[j].m_quantity;
					exists = 1;
				}
			if (!exists) {
				++c;
				codes = realloc(codes, c * sizeof(int));
				if (!codes)
					err(EMEM);
				count = realloc(count, c * sizeof(int));
				if (!count)
					err(EMEM);
				codes[c - 1] = bb->m_items[i].m_items[j].m_item->m_barCode;
				count[c - 1] = bb->m_items[i].m_items[j].m_quantity;
			}
		}
	printf("\n\t Total sales:\n\n");
	
	for(i = 0; i < c; ++i) {
		item = FindItem(db, codes[i]);
		if (!item)
			err(EMISS);	
		printf("%s ", item->m_name); 
		for(q = 0; q < LFSTRLEN - strlen(item->m_name); ++q)
			printf(".");
		printf(" Saled: %4d, price: $%6d.%2d\n",
			count[i],
			(item->m_price * count[i]) / 100,
			(item->m_price * count[i]) % 100);
		total += item->m_price * count[i];
		totalc += count[i];
	}
	free(count);
	free(codes);
	printf("Total saled: %d, total price: $%d.%d\n", totalc, total / 100, total % 100);
}

