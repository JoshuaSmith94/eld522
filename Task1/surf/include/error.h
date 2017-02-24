/******************************************************************
 * Module:	error.h
 *
 * Purpose:	Define error numbers.
 *
 * Contents:
 *		Definitions:
 *			error numbers
 *		Declarations:
 *			print_error()	- prints the error number
 *
 * Date:	25/4/91
 *****************************************************************/

#define MAX_ERRORS 11

#define ER_FIL 1
#define ER_MAG 2
#define ER_FILT 3
#define ER_MEM 4
#define ER_GRHW 5
#define ER_GRIN 6
#define ER_DIV0 7
#define ER_COMPAT 8
#define ER_FONT 9
                   
                                                     
/*
 * Routine:	print_error
 *
 * Description: Print error messages in response to a given error
 *     		number
 *
 * Parameters:  none
 *
 * Returns:	nothing
 *
 * Example:     error_number=10;
 *		printf("Magnification number out of range\n");
 *
 * Date:	22/5/91
 */
void print_error();
                                                     
