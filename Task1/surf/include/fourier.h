/******************************************************************
 * Module:	fourier.h
 *
 * Purpose:	Fast Fourier Transform (FFT) routine.
 *
 * Contents:	calculate_fft()		- controls the FFT routine
 *		copy_data()		- transfer "data" to "trans_data"
 *		calculate_spectrum()	- compute the spectral data
 *		calc_params()		- calculate my parameters
 *		print_params()		- print my parameters
 *
 * Date:	22/4/91
 *
 *
 *****************************************************************/

/*
 * make sure of only one inclusion
 */
#ifndef FourierDummy
#define FourierDummy

/*
 * First two autocorrelation values
 */
double gamma0;
double gamma1;
void autocorrelation_calculate();
void autocorrelation_print();

/*
 * Parameters
 */
double ra; // Ra value
double rp; // maximum peak  
double rv; // maximum valley
double rt; // maximum peak to valley
void parameter_calculate();
void parameter_print();


/*
 * prototypes
 */
int calculate_fft();
void copy_data();
void calculate_spectrum();
int calc_params();
int print_params();


#endif



