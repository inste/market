/*	------------------------------------------------
	
	finditem.c - binary seaches in database and bills

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"

struct Item * FindItem(const struct ItemDatabase * database, int barCode) {
	int i, r = -1, L = 0, R = database->m_count - 1;
	
	if (!database)
		err(EMEM);

	if ((database->m_items[L].m_barCode <= barCode) && (database->m_items[R].m_barCode >= barCode)) {
		while (L <= R) {
			i = (L + R) / 2;
			if (barCode < database->m_items[i].m_barCode)
				R = i - 1;
			else if (barCode > database->m_items[i].m_barCode)
				L = i + 1;
			else {
				r = i;
				break;
			}
		}
	}
	if (r == -1)
		return NULL;
	else
		return database->m_items + r;
}

int lookForBillItem(struct Bill * bill, int barCode) {
	int i, r = -1, L = 0, R = bill->m_count - 1;
	
	if (!bill)
		err(EMEM);

	if ((bill->m_items[L].m_item->m_barCode <= barCode) && (bill->m_items[R].m_item->m_barCode >= barCode)) {
		while (L <= R) {
			i = (L + R) / 2;
			if (barCode < bill->m_items[i].m_item->m_barCode)
				R = i - 1;
			else if (barCode > bill->m_items[i].m_item->m_barCode)
				L = i + 1;
			else {
				r = i;
				break;
			}
		}
	}
	return (r == -1) ? 0 : 1;
}
