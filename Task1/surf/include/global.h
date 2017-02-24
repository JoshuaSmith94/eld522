/******************************************************************
 * Module:	global.h
 *
 * Purpose:	Global definitions.
 *
 * Contents:	Booleans
 *		Maximum number of data values
 *		File name lengths
 *		Batch file name
 *		Error numbers
 *
 * Date:	22/5/91
 *****************************************************************/

#ifndef GlobalDummy  /* include this file only once */
#define GlobalDummy

/*
 * Booleans
 */
#define TRUE 0
#define FALSE -1

/*
 * maximum number of data values
 */
#define MAX_DATA 8192
#define SPEC_MAX_DATA MAX_DATA/2+1
#define SMOOTH_MAX_DATA 20

/*
 * Limit of file name length
 */
#define MAX_FIL_LEN 40

/*
 * Scaling factors for the x and y axes, expressed as a multiplying
 * factor per unit
 */
extern double x_division;  /* x scaling factor */
extern double y_division;  /* y scaling factor */
   
/* Talysurf data */
extern int num_data;  
extern double *data;
extern double *smooth_data;
extern int data_valid;

/* transform data */
extern int trans_num_data;
extern struct complex *trans_data;
extern struct complex *dummy_data;
extern int tfm_valid;

/* spectral data */
extern int spec_num_data;
extern double *spec_data;

/* smoothed spectral data */
struct smoothed {
   int subscr;
   double data;
};
extern int smooth_num_data;
extern int cut_num_data;
extern struct smoothed *smooth;

/* saved smoothed spectral data */
extern int num_combinations;
extern struct smoothed *saved_smooth;

/* curve fit to spectral data (defined in fft.c) */
extern double a_guess;
extern double b_guess;

/* new parameters */
extern double rms;
extern double c_lambda;


/*
 * batch input file handle
 */
#include <stdio.h>
extern FILE *curin;


/*
 * error number definitions
 */
#include "error.h"
extern int error_number;

/*
 * Routine:	clrscr
 *
 * Description:	Clear the screen.
 */
#define clrscr() printf("\n")

/*
 * Routine:	getch
 *
 * Description:	Get a keyboard character.
 */
#define getch() getc(stdin)

/*
 * Routine:	min
 *
 * Description:	Return the smaller of two ints.
 */
// #define min __min
#define min(x,y) (x<y?x:y)

#endif
