/******************************************************************
 * Module:	fourier.cpp
 *
 * Purpose:	Fast Fourier Transform calculations.
 *
 * Contents:	calculate_fft()		- controls the FFT routine
 *		copy_data()		- transfer "data" to "trans_data"
 *		calculate_spectrum()	- compute the spectral data
 *		calc_params()		- calculate my parameters
 *		print_params()		- print my parameters
 *
 * Date:	22/4/91
 *
 * Modified:	22/5/91: 
 * 
 *****************************************************************/


/*
 * Complex numbers needed
 */
#include <math.h>
#include "complex.h"

/*
 * other general functions
 */
#include <stdlib.h>

/*
 * Global definitions
 */
#include "global.h"
int cut_num_data;  /* number of spectral values per smoothed value */

/*
 * FFT declarations
 */
#include "fft.h"
#include "fourier.h"


/*
 * Routine:	calculate_fft
 *
 * Description:	The Fourier transform of the data items is calculated.
 *
 * Parameters:
 *
 * Returns:	TRUE	- successful calculation
 *		FALSE	- unsuccessful
 *
 * Date:	3/6/91
 */
int calculate_fft()
{
   /*
    * copy the data to be transformed from "data" to "trans_data"
    */
   (void) copy_data();

   /*
    * call the fft routine
    */
   (void) fft();

   /*
    * calculate the spectral values and smooth
    */
   (void) calculate_spectrum();
   
   return(TRUE);
}


/*
 * Routine:	copy_data
 *
 * Description:	Copy the data to be transformed from "data" to
 *		"trans_data"
 *
 * Parameters:	none
 *
 * Returns:	nothing
 *
 * Example:
 *
 * Date:	23/5/91
 */
void copy_data()
{
   int i;

   /*
    * copy values one at a time, converting the "data" to
    * the real part of "trans_data"
    */
   for(i=0;i<num_data;i++) {
      trans_data[i].x = data[i];
      trans_data[i].y = 0.0;
   }

/*** testing **
   (void) printf("num_data trans_num_data: %5d %5d\n",num_data,trans_num_data);
   for(i=0;i<num_data;i++) {
      (void) printf("%4d %12.2f %12.2f\n",i,data[i],trans_data[i].x);
      if(trans_data[i].x < 10 && trans_data[i].x > -10) (void) printf("aaaagh\n");
   }
*/

   /*
    * The fft must be performed on data which number an integral power
    * of 2. Zeros are added to the data to satisfy this constraint.
    * This is now performed in 2 stages:
    *  (1) calculate the next integral power of 2 greater than "num_data",
    *      call this "trans_num_data".
    *  (2) add the zeros.
    */

    /*
     * (1) find "trans_num_data"
     */
    trans_num_data = (int) pow(2.0,ceil(log(num_data)/log(2.0)));

    /*
     * (2) add the zeros
     */
   for(i=num_data;i<trans_num_data;i++) {
      trans_data[i].x = 0.0;
      trans_data[i].y = 0.0;
   }
}


/*
 * Routine:	calculate_spectrum
 *
 * Description:	Calculate the Fourier spectrum from the transformed
 *		data.
 *
 * Parameters:	none
 *
 * Returns:	nothing
 *
 * Example:
 *
 * Date:	22/5/91
 */
void calculate_spectrum()
{
   int i;
/*** testing *
   double sum_data,spec_sum_data;
*/

   /*
    * the spectral values are the sum of the squares of the
    * real and complex transform values
    */
   spec_num_data = trans_num_data/2 + 1;

   for(i=0;i<spec_num_data;i++)
      spec_data[i] =  pow(trans_data[i].x,2.0)
                        + pow(trans_data[i].y,2.0);

   /*
    * scale the values to make their sum equal to that of the mean
    * square of the data
    */
   spec_data[0] = spec_data[0]/trans_num_data;
   for(i=1;i<spec_num_data-1;i++)
      spec_data[i] = 2*spec_data[i]/trans_num_data;
   spec_data[spec_num_data-1] = spec_data[spec_num_data-1]/trans_num_data;

/** testing 
   for(i=0;i<10;i++) {
      (void) printf("%2d %12.2f ",i,spec_data[i]);
      (void) printf("%12.2f %12.2f\n",spec_data[i]*pow(y_division,2.0),y_division);
   }
*/

/*** testing *
   sum_data=0;
   for(i=0;i<num_data;i++)
      sum_data = sum_data + pow(data[i],2.0);
   spec_sum_data=0;
   for(i=0;i<spec_num_data;i++)
      spec_sum_data = spec_sum_data + spec_data[i];
   (void) printf("sums %12.2f %12.2f\n",sum_data,spec_sum_data);
   getch();
*/
}


/*
 * Routine:	calc_params()
 *
 * Description:	Calculate parameters
 *
 * Parameters:	none
 *
 * Returns:	TRUE	- successful calculation
 *
 * Example:     
 *
 * Date:	10/6/91
 */
double mean;
double var;
double ra, rp, rv, rt;
int calc_params()
{
/*
 * find new parameters
 */

   double var,mean;
   double adjfac;
   int i;

   /*
    * find mean and variance
    */
   mean = 0.0;
   var = 0.0;
   for(i=0;i<num_data;i++) {
      mean = mean + data[i];
      var = var +  pow(data[i],2.0);
   }
   
   /* 
    * find other parameters
    */
 
   // find Rp
   rp = 0;
   for(i=0;i<num_data;i++) {
   	if (rp < (data[i]-mean)) rp = data[i] - mean;
   }
   
   // find Rv
   rv = 0;
   for(i=0;i<num_data;i++) {
   	if (rv < (mean-data[i])) rv = mean - data[i];
   }     
 
   // find Rt
   rt = rp + rv; 
  
  /*
   * find correlation parameters
   */
   autocorrelation_calculate();

   return(TRUE);
}

void autocorrelation_calculate()
{     
   int i;       
	
   // find first correlation coefficient
   gamma0 = 0.0;
   for(i=0;i<num_data;i++) {
      gamma0 = gamma0 +  pow(data[i],2.0);
   }
   gamma0 = pow(y_division,2.0)*gamma0/num_data;
   
   // find second correlation coefficient
	gamma1 = 0.0;
   for(i=1;i<num_data;i++) {
      gamma1 = gamma1 +  data[i]*data[i-1];
   }
   gamma1 = pow(y_division,2.0)*gamma1/num_data;
}

/*
 * Routine:	print_params()
 *
 * Description:	Print my parameters
 *
 * Parameters:	none
 *
 * Returns:	TRUE	- successful calculation
 *
 * Example:     
 *
 * Date:	23/7/91
 */
int print_params()
{
   // print the new parameters
   (void) printf("Parameters\n");
   (void) printf("--------------\n\n");
                              
   autocorrelation_print();    
   parameter_print();                          

   return(TRUE);
}


/*
 * Routines:	Functions for "autocorrelations"
 *
 * Example:     
 *
 * Date:	10/5/94
 */


void autocorrelation_print()
{  
	(void) printf("\n");
   (void) printf("Autocorrelation values\n");
   (void) printf("----------------------\n\n");
   (void) printf("first correlation coefficient: %12.4f microns\n",gamma0);
   (void) printf("second autocorrelation coefficient: %12.4f microns\n",gamma1);
}
   
   

void parameter_print()
{  
   (void) printf("\n");
   (void) printf("Parameter values\n");
   (void) printf("----------------------\n\n");
   (void) printf("rms value : %12.4f microns\n",sqrt(var));
   (void) printf("Rp value : %12.4f microns\n",rp);
   (void) printf("Rv value : %12.4f microns\n",rv);
   (void) printf("Rt value : %12.4f microns\n",rt);
 
}
