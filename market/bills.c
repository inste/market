/*	------------------------------------------------
	
	bills.c - Operations with bills

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"


struct Bill * AllocBill(int itemsCount) {
	struct Bill * result = malloc(sizeof(struct Bill));

	if (!result)
		return NULL;
	result->m_count = 0;
	result->m_items = malloc(itemsCount * sizeof(struct BillItem));
	if (!result->m_items && itemsCount > 0) {
		free(result);
		return NULL;
	}
	return result;
}

void FreeBill(struct Bill * bill) {
	if (bill->m_items)
		free(bill->m_items);
	free(bill);
}

void PrintBill(const struct Bill * bill) {
	int i, totalBill = 0, totalDiscount = 0;
	unsigned int j;

	if (!bill)
		err(EMEM);
	printf("C supermarket\n\n");
	for(i = 0; i < bill->m_count; ++i) {
		int totalLine = bill->m_items[i].m_item->m_price * bill->m_items[i].m_quantity;
		if ((bill->m_items[i].m_item->m_barCode == IDISC) && (totalDiscount = bill->m_items[i].m_quantity > 1))
			totalDiscount = bill->m_items[i].m_quantity / IDISCOUNT;
		totalBill += totalLine;
		printf("%s ", bill->m_items[i].m_item->m_name);
		for(j = 0; j < LFSTRLEN - 15 - strlen(bill->m_items[i].m_item->m_name); ++j)
			printf(".");
		printf(" (x%d) $%4d.%d\n",
			bill->m_items[i].m_quantity,
			totalLine / 100,
			totalLine % 100);
	}
	if (totalDiscount > 0) {
		printf("\nDiscount ");
		for(j = 0; j < LFDSTRLEN; ++j)
			printf(".");
		printf(" $%4d.00\n", totalDiscount * IDISCVALUE);
	}
	printf("\nTOTAL ");
	for(j = 0; j < LFSTRLEN - 15; ++j)
		printf(".");
	printf(" $%4d.%d\n", totalBill / 100, totalBill % 100);
}

int IndexOfBillItem(const struct Bill * bill, int barCode) {
	int i;

	if (!bill)
		err(EMEM);
	for(i = 0; i < bill->m_count; i++) {
		if (bill->m_items[i].m_item->m_barCode == barCode)
			return i;
	}
	return -1;
}

struct Bill * ProduceBill(const struct ItemDatabase * database, const int * barCodes, int count) {
	struct Bill * result = AllocBill(count);
	int i;

	if (!result)
		err(EMEM);
	for(i = 0; i < count; i++) {
		int index;
		struct Item * in_db = FindItem(database, barCodes[i]);
		if (in_db == NULL)
			continue;
		index = IndexOfBillItem(result, barCodes[i]);
		if (index == -1) {
			result->m_items[result->m_count].m_item = FindItem(database, barCodes[i]);
			result->m_items[result->m_count].m_quantity = 1;
			++result->m_count;
		} else
			++result->m_items[index].m_quantity;
	}
	// Let's sort our bill before printing (it's needed for future binary search in the bills)
	qsort(result->m_items, result->m_count, sizeof(struct BillItem), BillItemDifference);

	return result;
}
 
