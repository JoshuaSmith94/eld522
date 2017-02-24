/******************************************************************
 * Module:	maths.h
 *
 * Purpose:	General mathematical declarations
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
 * make sure file is included only once
 */
#ifndef MathsDummy
#define MathsDummy


/*
 * choose 5 significant figures for the conversion
 */
#define SIG_FIG 5


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
struct mant {
   double mantissa;
   int exponent;
};

struct mant double_to_mant(double);


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
char *fcvt2(char *,double);


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
char *fcvt3(char *,double);


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
double fixed(double, int);


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
void remove_bias();


#endif

