/******************************************************************
 * Module:	fft.h
 *
 * Contents:	
 *			Definitions
 *				constants
 *				confidence interval lengths.
 *
 *			Declarations
 *				fft()	- the fast Fourier transform
 *
 *
 * Date:	23/4/91
 *****************************************************************/

/*
 * Constants
 */
#define MINUS_TWO_PI -6.2831853
#define FOUR_PI 12.5663706
#define PI 3.141592654


/*
 * Routine:	fft
 *
 * Description:	The Fourier transform of the data items is calculated.
 *
 * Date:	22/4/91
 */
void fft();
