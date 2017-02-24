/******************************************************************
 * Module:	maths.cpp
 *
 * Purpose:	General mathematical definitions
 *
 * Contents:	double_to_mant()	- conversion to mantissa form
 *		fcvt2()		- convert double to string - 2 decimal places
 *		fcvt3()		- convert double to string - 3 decimal places
 *		fixed()		- round to a specified number of sig figs
 *		remove_bias()	- re-calculate data relative to mse line
 *
 * Date:	22/5/91
 *****************************************************************/

/*
 * declarations needed
 */
#include <stdlib.h>
#include <math.h>
#include <string.h>
 
/*
 * global declarations
 */
#include "global.h" 
          
/*
 * local declarations
 */          
#include "maths.h"
   
   
/*
 * Routine:	double_to_mant
 *
 * Description:	Converts a double to manitissa-exponent form.
 *
 * Parameters:	double x	< the value to be converted
 *
 * Returns:	struct mant y	- the converted value
 *
 * Example:	double_to_mant(134.6);
 *		y.mantissa = 1.346;
 *		y.exponent = 2;
 *
 * Date:	28/5/91
 */
struct mant double_to_mant(double x)
{
   struct mant y;

   y.exponent = (int) floor(log10(x));
   y.mantissa = x / pow(10.0, y.exponent);

   return(y);
}


/*
 * Routine:	fcvt2
 *
 * Description:	Convert a double to a string (2 decimal places)
 *
 * Parameters:	double source	< the double value for conversion
 *		char far *dest	> the converted string
 *
 * Returns:	the converted string
 *
 * Example:
 *
 * Date:	28/5/91
 */
char *fcvt2(char *dest, double source)
{
   char *buf = "dummy string";
   char *result= "dummy string";

   /*
    * reduce to 2 decimal places
    */
   source =  floor(100.0*source+0.5)/100.0F;

   result = gcvt(source,SIG_FIG,buf);
   (void) strcpy(dest,result);
   if (dest == "") strcpy(dest,"0");
 
   return(dest);
}


/*
 * Routine:	fcvt3
 *
 * Description:	Convert a double to a string (3 decimal places)
 *
 * Parameters:	double source	< the double value for conversion
 *		char far *dest	> the converted string
 *
 * Returns:	the converted string
 *
 * Example:
 *
 * Date:	28/5/91
 */
char *fcvt3(char *dest, double source)
{
   char *buf = "dummy string";
   char *result= "dummy string";

   /*
    * reduce to 3 decimal places
    */
   source =  floor(1000.0*source+0.5)/1000.0F;

   result = gcvt(source,SIG_FIG,buf);
   (void) strcpy(dest,result);
   if (dest == "") strcpy(dest,"0");
 
   return(dest);
}

/*
 * Routine:	fixed
 *
 * Description:	Convert a double to a fixed number of significant figures
 *
 * Parameters:	double source	< the double value for conversion
 *		int places	< the number of decimal places
 *
 * Returns:	the converted number
 *
 * Example:	fixed(123.45,2)
 *		return(120.0)
 *
 * Date:	23/7/91
 */
double fixed(double source, int places)
{
   struct mant temp;
   double return_value;

   /*
    * round the source to specified number of decimal places
    */
   temp = double_to_mant(source);
   temp.mantissa =  (floor(pow(10.0,places)*temp.mantissa+0.5)
      /pow(10.0,places));

/** testing
   printf("temp %12.4f %5d\n",temp.mantissa,temp.exponent);
*/

   return_value = temp.mantissa*pow(10.0,temp.exponent);
   return(return_value);
}


/*
 * Routine:	remove_bias
 *
 * Description:	Re-calculate data relative to the best-fitting mse
 *		line
 *
 * Parameters:	none
 *
 * Returns:	nothing
 *
 * Example:	
 *
 * Date:	23/7/91
 */
void remove_bias()
{
   double sum_x,sum_y;
   double sum_x_2,prod_x_y;
   double a,b;
   int i;

   /*
    * find the various parameters needed
    */
   sum_x = 0.0;
   sum_y = 0.0;
   sum_x_2 = 0.0;
   prod_x_y = 0.0;
   for(i=0;i<num_data;i++) {
     sum_x = sum_x + i;
     sum_y = sum_y + data[i]; 
     sum_x_2 = sum_x_2 + pow(i,2.0);
     prod_x_y = prod_x_y + i*data[i];      
   }

   /*
    * solve 2 simultaneous equations of the form:
    *
    * (1) num_data*a + sum_x*b = sum_y
    * (2) sum_x*a + sum_x_2*b = prod_x_y
    *
    * to get the best-fitting line of equation
    *
    * y = a + bx
    */
   b = (sum_y*sum_x-num_data*prod_x_y)/(sum_x*sum_x-num_data*sum_x_2);
   a = (prod_x_y-sum_x_2*b)/sum_x;

   /*
    * subtract the data from the fitted line
    */
   for(i=0;i<num_data;i++){
      data[i]=data[i]-(a+b*i);
   }

}

