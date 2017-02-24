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

/*
 * complex structure
 */
struct complex {
	double x;
	double y;
};


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
struct complex com_sum(struct complex com1,struct complex com2);


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
struct complex com_diff(struct complex com1,struct complex com2);


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
struct complex com_prod(struct complex com1, struct complex com2);


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
struct complex com_div(struct complex com1, struct complex com2);


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
struct complex com_pow(struct complex com, double expon);
