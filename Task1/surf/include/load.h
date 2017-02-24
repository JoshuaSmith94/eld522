/******************************************************************
 * Module:	load.h
 *
 * Purpose:	Definitions of filter (horizontal) and magnification
 *		(vertical) setting of the Talysurf.
 *
 * Contents:	Definitions for the horizontal scale
 *				Definitions for the vertical scale
 *				Declaration of prototypes
 *
 * Date:	22/4/91
 *****************************************************************/

/*
 * definitions for the horizontal scale
 */

   /*
    * sample interval (between consecutive samples) in microns
    */
   #define SAMPLE_INT 1.0

   /*
    * number of samples collected in a traverse - all values must
    * be less than MAX_DATA defined in "global.h"
    */
   #define FILTER_J_SAMPLES 1750
   #define FILTER_K_SAMPLES 4000
   #define FILTER_L_SAMPLES 7500

   /*
    * the filters available on the Talysurf
    */
   #define FILTER_J 1
   #define FILTER_K 2
   #define FILTER_L 3

/*
 * definitions for the vertical scale
 */

   /*
    * half scale in number of bits
    */
   #define HSD_SAMPLES 256

   /*
    * number of magnification settings available on the Talysurf
    */
   #define NUM_MAG_SETTINGS 8

   /*
    * Magnification adjustments to convert sample values to
    * values in microns. The index of the "mag" array is selected
    * according to the actual magnification used. For example,
    * "mag[1]" is magnification number 1, which, when plotted on
    * Talysurf paper, has a range of +/- 50 microns.
    */
extern double mag[NUM_MAG_SETTINGS + 1];

/*
 * prototypes
 */
int load();
int check_mag();
int check_filter();
int put_smoothed();

