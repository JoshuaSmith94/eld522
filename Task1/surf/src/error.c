/******************************************************************
 * Module:	error.c
 *
 * Purpose:	Print error messages.
 *
 * Contents:    print_error	- print error messages
 *
 * Date:	25/4/91
 *****************************************************************/

/*
 * global definitions
 */
#include <stdio.h>
#include "global.h"
int error_number;

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
void print_error()
{
   /*
    * memory area for the error messages
    */
   static char *error_message[MAX_ERRORS];

   /*
    * error messages
    */
   error_message[ER_FIL] = "File not found";
   error_message[ER_MAG] = "Magnification out of range - invalid file";
   error_message[ER_FILT] = "Filter setting out of range - invalid file";
   error_message[ER_MEM] = "Insufficient memory for data arrays";
   error_message[ER_GRHW] = "No graphics present";
   error_message[ER_GRIN] = "Graphics initialization failure";
   error_message[ER_DIV0] = "Division by zero";
   error_message[ER_COMPAT] = "Incompatible file format";
   error_message[ER_FONT] = "Font file not found";

   /*
    * print the error message
    */
   printf("%s \n",error_message[error_number]);

   /*
    * wait for user input
    */
   getch();

   /*
    * clear the message
    */
   clrscr();
}
