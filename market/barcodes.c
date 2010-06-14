/*	------------------------------------------------
	
	barcodes.c - operations with packed barcodes

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */

#include "market.h"


T makebarCode(int fCode, int sCode) {
	T result;
	fCode = fCode % 65536;
	sCode = sCode % 65536;
	if (fCode > sCode) {
		sCode += fCode;
		fCode = sCode - fCode;
		sCode -= fCode;
	}
	result = fCode;
	result = result << 16;
	result += sCode;
	return result;
}

void unpackbarCode(T code, int * a, int * b) {
	T t = code >> 16;
	*a = t % 65536;
	*b = code % 65536;
}