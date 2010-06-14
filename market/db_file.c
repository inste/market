/*	------------------------------------------------
	
	db_file.c - File operations with database

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"

struct Item * MakeItemFromString(char * line) {
	int p = 0, n = 0;
	char c_bar[10], c_name[86], c_cost[10];
	
	if (!line)
		err(EMEM);

	if ((strlen(line) > 105) || (strlen(line) < 6))
		err(ECORRUPTEDDB);

	while (line[p++] != ',')
		if (line[p] == '\0')
			err(ECORRUPTEDDB);

	strncpy(c_bar, line, p - 1);
	c_bar[p - 1] = '\0';
	n = p;
	if (line[n] == '"') {
		++n;
		while(line[n++] != '"')
			;;
		strncpy(c_name, line + p + 1, n - p - 2);
		c_name[n - p - 2] = '\0';
		p = n + 1;
	} else {
		while(line[n++] != ',')
			;;
		strncpy(c_name, line + p, n - p - 1);
		c_name[n - p - 1] = '\0';
		p = n;
	}
	strncpy(c_cost, line + p, strlen(line) - p);
	c_cost[strlen(line) - p] = '\0';

	return AllocItem(atoi(c_bar), c_name, atoi(c_cost));
}


struct ItemDatabase * LoadDBFromFile(char * filename) {
	FILE * fd;
	struct ItemDatabase * res = NULL;
	struct Item * item = NULL;
	char line[512];
	
	if (!filename)
		err(EMEM);
	fd = fopen(filename, "rt");
	if (!fd)
		err(EFILE);
	while (!feof(fd)) {
		fgets(line, 511, fd);
		if ((item = MakeItemFromString(line)) != NULL) {
			res = AddNewItemToDatabase(res, item);
			if (!res)
				err(EMEM);
			free(item);
		}
	}
	fclose(fd);
	qsort(res->m_items, res->m_count, sizeof(struct Item), ItemDifference);
	return res;
}


void SaveDBToFile(struct ItemDatabase * db, char * filename) {
	FILE * fd;
	int i;
	
	if (!db)
		err(EMEM);
	fd = fopen(filename, "wt");
	if (!fd)
		err(EFILE);
	for (i = 0; i < db->m_count; ++i)
		fprintf(fd, "%d,\"%s\",%d\n",
			db->m_items[i].m_barCode,
			db->m_items[i].m_name,
			db->m_items[i].m_price);
	fclose(fd);
}
