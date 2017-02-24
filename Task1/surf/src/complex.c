/******************************************************************
 * Module:	complex.h
 *
 * Purpose:	Complex number manipulation routines.
 *
 * Contents:	com_sum	- adds two complex numbers
 *		com_diff- finds the difference of two complex numbers
 *		com_prod- finds the products of two complex numbers
 *		com_div	- divides one complex number by a second
 *		com_pow - raises a complex number to a power
 *
 * Date:	23/4/91
 *
 *****************************************************************/
                    
#include <math.h>
          
#include "complex.h"


/*
 * Routine:	com_sum
 *
 * Description:	Find the sum of two complex numbers.
 *
 * Parameters:	com1	< the first complex number
 *		com2	< the second complex numnber
 *
 * Returns:	com3 - the complex sum
 *
 * Example:	com1 = 2+3j; com2 = 5+6j;
 *		com3 = 7+9j;
 *
 * Date:	23/4/91
 */
struct complex com_sum(struct complex com1,struct complex com2)
{
   struct complex com3;

   /*
    * sum the real and imaginary parts separately
    */
   com3.x = com1.x + com2.x;
   com3.y = com1.y + com2.y;

   return(com3);
}

/*
 * Routine:	com_diff
 *
 * Description:	Find the difference of two complex numbers.
 *
 * Parameters:	com1	< the first complex number
 *		com2	< the second complex numnber
 *
 * Returns:	com3 - the complex difference
 *
 * Example:	com1 = 2+3j; com2 = 5+6j;
 *		com3 = -3-3j;
 *
 * Date:	23/4/91
 */
struct complex com_diff(struct complex com1,struct complex com2)
{
   struct complex com3;

   /*
    * subtract the real and imaginary parts separately
    */
   com3.x = com1.x - com2.x;
   com3.y = com1.y - com2.y;

   return(com3);
}

/*
 * Routine:	com_prod
 *
 * Description:	Find the product of two complex numbers.
 *
 * Parameters:	com1	< the first complex number
 *		com2	< the second complex numnber
 *
 * Returns:	com3 - the complex product
 *
 * Example:	com1 = 2+3j; com2 = 5+6j;
 *		com3 = -8+27j;
 *
 * Date:	23/4/91
 */
struct complex com_prod(struct complex com1, struct complex com2)
{
   struct complex com3;

   /*
    * The product is: (a+jb)(c+jd) = (ac-bd) + (bc+ad)j
    */
   com3.x = com1.x*com2.x - com1.y*com2.y;
   com3.y = com1.x*com2.y + com1.y*com2.x;

   return(com3);
}

/*
 * Routine:	com_div
 *
 * Description:	Divide a complex number by another.
 *
 * Parameters:	com1	< the dividend
 *		com2	< the divisor
 *
 * Returns:	com3 - the complex result
 *
 * Example:	com1 = 2+3j; com2 = 5+6j;
 *		com3 = 28/61 + 3j/61;
 *
 * Date:	23/4/91
 */
struct complex com_div(struct complex com1, struct complex com2)
{
   struct complex com3;
   struct complex numerator;
   double denominator;

   /*
    * The result of (a+jb)/(c+jd) is formed by:
    *  (a+jb)(c-jd)/(c**2+d**2)
    */
   denominator = pow(com2.x,2.0) + pow(com2.y,2.0);
   com2.y = - com2.y;    /* form the complex conjugate of "com2" */
   numerator = com_prod(com1,com2);
   com3.x = numerator.x/denominator;
   com3.y = numerator.y/denominator;

   return(com3);
}

/*
 * Routine:	com_pow
 *
 * Description:	Raises a complex number to a power.
 *
 * Parameters:	com	< the complex number
 *		expon	< the power to which "com" is to raised
 *
 * Returns:	com3 - the complex result
 *
 * Example:	com = 2+3j; expon = 2;
 *		com3 = -5+12j;
 *
 * Date:	23/4/91
 */
struct complex com_pow(struct complex com, double expon)
{
   struct complex com3;
   double modulus, argument;

   /*
    * convert to polar form
    */
   modulus = sqrt(pow(com.x,2.0)+pow(com.y,2.0));
   argument = atan(com.y/com.x);

   /*
    * use DeMoivre's thereom, namely (cosA+jsinA)**n = cos(nA)+jsin(nA)
    * WARNING: The Author is unsure if the theorem holds for non-integer
    *          values of "expon".
    */
   com3.x = pow(modulus,expon)*cos(expon*argument);
   com3.y = pow(modulus,expon)*sin(expon*argument);

   return(com3);
}

