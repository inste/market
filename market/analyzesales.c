/*	------------------------------------------------
	
	analyzesales.c - AnalyzeSales() function

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"
#include "rbtree.h"

void AnalyzeSales(struct ItemDatabase * db, struct Billboard * bb) {
	int currcode, another;
	int i, j, p, counter = 0;
	struct Line * line;
	struct Item * fi, * si;
	
	printf("\n\t Copules of items, which are often bought together \n");
	// Building red-black tree from billboard
	for (i = 0; i < bb->m_count; ++i)
		for (j = 0; j < bb->m_items[i].m_count - 1; ++j)
			for (p = j + 1; p < bb->m_items[i].m_count; ++p)
				treeAdd(makebarCode(bb->m_items[i].m_items[j].m_item->m_barCode, 
					bb->m_items[i].m_items[p].m_item->m_barCode));
	// Linerizing our tree
	line = treeLine();
	// Sort couples by count descending
	qsort(line->m_items, line->count, sizeof(struct lCouple), LineItemDifference);
	i = 0;
	while ((i < line->count) && (line->m_items[i].count >= 2)) {
		unpackbarCode(line->m_items[i].barCode, &currcode, &another);
		fi = FindItem(db, currcode);
		si = FindItem(db, another);
		printf("\n %d: (%d and %d): %s and %s",
			counter, fi->m_barCode, si->m_barCode, fi->m_name, si->m_name);
		++i;
	}
	free(line->m_items);
	free(line);
	treeFree();
}

