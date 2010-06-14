/*	------------------------------------------------
	
	db.c - Database functions

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"

struct ItemDatabase * AddNewItemToDatabase(struct ItemDatabase * db, struct Item * item) {

	if (!item)
		err(EMEM);
	if (!db) {
		db = malloc(sizeof(struct ItemDatabase));
		db->m_count = 1;
		db->m_items = malloc(sizeof(struct Item));
		db->m_items[0] = *item;
	} else {
		++db->m_count;
		db->m_items = realloc(db->m_items, db->m_count * sizeof(struct Item));
		if (!db->m_items)
			return NULL;
		db->m_items[db->m_count - 1] = *item;
	}
	return db;
}


struct ItemDatabase * AddItem(struct ItemDatabase * db, struct Item * item) {
	struct ItemDatabase * res;
	int i;
	
	if(!item)
		err(EMEM);
	if(!db)
		return AddNewItemToDatabase(db, item);
	for(i = 0; i < db->m_count; ++i)
		if (db->m_items[i].m_barCode == item->m_barCode) {
			db->m_items[i].m_price = item->m_price;
			strcpy(db->m_items[i].m_name, item->m_name);
			return db;
		}
	res = AddNewItemToDatabase(db, item);
	qsort(res->m_items, res->m_count, sizeof(struct Item), ItemDifference);
	return res;
}

struct ItemDatabase * RemoveItem(struct ItemDatabase * db, int barCode) {
	int i, j = -1;

	if (!db)
		err(EMEM);
	for(i = 0; i < db->m_count; ++i)
		if (db->m_items[i].m_barCode == barCode) {
			j = i;
			break;
		}
	if (j == -1)
		return db;
	for(i = j; i < db->m_count - 1; ++i)
		db->m_items[i] = db->m_items[i + 1];
	--db->m_count;
	db->m_items = realloc(db->m_items, db->m_count * sizeof(struct Item));
	if (!db->m_items)
		err(EMEM);
	return db;
}

void printDB(struct ItemDatabase * db) {
	int i = 0;

	for(i = 0; i < db->m_count; ++i)
		printf("\n  %d) Barcode: %d, Name: %s, Price: %d", i + 1,
			db->m_items[i].m_barCode,
			db->m_items[i].m_name,
			db->m_items[i].m_price);
	printf("\n\n\n");
}


void FreeDB(struct ItemDatabase * db) {

	if (!db)
		err(EMEM);
	free(db->m_items);
	free(db);
}
