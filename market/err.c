/*	------------------------------------------------
	
	err.c - Error handler

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"

void err(char * message) {
	printf("\n\t Oops, an unexpected error has happened:\n\n\t %s\n\n\t Application will be terminated.\n", message);
	abort();
}
