/*	------------------------------------------------
	
	main.c - main() worker loop

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"
#include <locale.h>
int main(void) {
	int codes1[] = { 1234, 4719, 1234, 1234, 2344 };
	int codes2[] = { 1234, 1112, 1111, 1111, 2344, 4719 };
	int codes3[] = { 3814, 1234, 1234, 2344, 4719 };
	struct Bill * bill;
	struct Billboard * bb = NULL;
	struct Item * i;
	struct ItemDatabase * db = NULL;

	db = LoadDBFromFile("db.txt");
	if (!db)
		err(EMEM);
	
	bill = ProduceBill(db, codes1, sizeof(codes1) / sizeof(codes1[0]));
	bb = AddToBillboard(bb, bill);
	
	//PrintBill(bill);
	free(bill);
	
	bill = ProduceBill(db, codes2, sizeof(codes2) / sizeof(codes2[0]));
	bb = AddToBillboard(bb, bill);
	
	//PrintBill(bill);
	free(bill);
	
	bill = ProduceBill(db, codes3, sizeof(codes3) / sizeof(codes3[0]));
	bb = AddToBillboard(bb, bill);

	//PrintBill(bill);	
	free(bill);
	
	//TotalSales(db, bb);
	
	//AnalyzeSales(db, bb);

	i = AllocItem(255, "The New Device", 5556);

	printf("\n Adding new item: barcode = 255, name : 'The New Device', cost = 5556': \n");

	printDB(db);

	db = AddItem(db, i);

	printDB(db);
	
	printf("\n Removing item with barcode = 3814: \n");

	db = RemoveItem(db, 3814);

	printDB(db);

	FreeBillboard(bb);

	FreeDB(db);

#ifndef __GNUC__
	printf("\n\t Press any key...");
	_getch();
#endif
	return 0;
}