/*	------------------------------------------------
	
	market.h - The main header

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#ifndef _MARKET_H
#define _MARKET_H

#ifndef __GNUC__
// Supress all stdlib's secure warnings
#define _CRT_SECURE_NO_WARNINGS
#endif

// System headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __GNUC__
#include <conio.h>
#endif

// Local headers

#include "types.h"
#include "const.h"

// Defines

/* Prototypes   */

// error.c
void err(char * message);

//itemdiff.c
int ItemDifference(const void * p1, const void * p2);
int BillItemDifference(const void * p1, const void * p2);
int LineItemDifference(const void * p1, const void * p2);

//finditem.c
struct Item * FindItem(const struct ItemDatabase * database, int barCode);
int lookForBillItem(struct Bill * bill, int barCode);
	
//bills.c

struct Bill * AllocBill(int itemsCount);
void FreeBill(struct Bill * bill);
void PrintBill(const struct Bill * bill);
int IndexOfBillItem(const struct Bill * bill, int barCode);
struct Bill * ProduceBill(const struct ItemDatabase * database, const int * barCodes, int count);

// db.c

struct ItemDatabase * AddNewItemToDatabase(struct ItemDatabase * db, struct Item * item);
struct ItemDatabase * AddItem(struct ItemDatabase * db, struct Item * item);
struct ItemDatabase * RemoveItem(struct ItemDatabase * db, int barCode);
void printDB(struct ItemDatabase * db);
void FreeDB(struct ItemDatabase * db);

// db_file.c

struct Item * MakeItemFromString(char * line);
struct ItemDatabase * LoadDBFromFile(char * filename);
void SaveDBToFile(struct ItemDatabase * db, char * filename);
	
// billboard.c

struct Billboard * AddToBillboard(struct Billboard * bboard, struct Bill * bill);
void FreeBillboard(struct Billboard * bboard);
	
// allocitem.c

struct Item * AllocItem(int barCode, char * name, int price);
	
// totalsales.c

void TotalSales(struct ItemDatabase * db, struct Billboard * bb);

// analyzesales.c

void AnalyzeSales(struct ItemDatabase * db, struct Billboard * bb);

// barcodes.c

T makebarCode(int fCode, int sCode);
void unpackbarCode(T code, int * a, int * b);


#endif

