/*	------------------------------------------------
	
	const.h - Constants

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */


#ifndef _CONST_H
#define _CONST_H

/* Printing format options	*/

// Length of the formatted string
#define LFSTRLEN	40

// Length of the 'Discount' formatted string
#define LFDSTRLEN	(LFSTRLEN - 18)



/*  String constants for errors   */

#define EMEM  "Memory operation error"
#define EFILE "Database file can't be opened"
#define ECORRUPTEDDB "Error in database file"
#define EMISS "Item not found" 

/* Code of item which should be discounted  */

#define IDISC		1234 // Dry Sherry, 11st
#define IDISCVALUE	5	 // $5.00 per two items 
#define IDISCOUNT   2

#endif

