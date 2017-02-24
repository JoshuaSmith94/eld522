/******************************************************************
 * Module:	load.c
 *
 * Purpose:	Read a file created on the Talysurf.
 *
 * Contents:	load()		- read the file
 *		check_mag()	- check number read is within range
 *		check_filter()	- check value read is within range
 *		put_smoothed()	- save smoothed data
 *
 * Date:	22/5/91
 *****************************************************************/



/*
 * require routines to read data from files
 */
#include <stdio.h>

/*
 * global definitions
 */
#include "global.h"
#include "maths.h"

/*
 * definitions of horizontal and vertical magnifications
 */
#include "load.h"

/*
 * Magnification adjustments to convert sample values to
 * values in microns. The index of the "mag" array is selected
 * according to the actual magnification used. For example,
 * "mag[1]" is magnification number 1, which, when plotted on
 * Talysurf paper, has a range of +/- 50 microns.
 */
double mag[] = {0,
  50,
  25,
  12.5,
  5,
  2.5,
  1.25,
  0.5,
  0.25};

/*
 * global variables
 */
int filter_set;  /* filter setting of Talysurf */
int mag_set;  /* magnification setting of Talysurf */
double x_division;  /* scaling factor for x axis */
double y_division;  /* scaling factor for y axis */

/*
 * Routine:	load
 *
 * Description: Read a data file created by the Talysurf.
 *
 * Parameters:	none
 *
 * Returns:	TRUE	- no errors
 *		ER_FIL	- file not found
 *		ER_MAG	- magnification number invalid
 *		ER_FILT	- filter setting invalid
 *
 * Example:
 *
 * Date:	22/5/91
 */
int load()
{
   char filename[MAX_FIL_LEN];  /* the name of the file to be read */
   FILE *f;  /* file handle */
   unsigned char ch[4];  /* current sample read */
   int byte;  /* the number of the current byte being read */
   int sample_num;  /* count through the samples */
 
   /*
    * get the file name
    */

   printf("Enter the file name: ");
   (void) fscanf(stdin,"%s",filename);
   clrscr();

   /*
    * the file to be "read"
    */
   f = fopen(filename,"r");

   if (f==NULL) {
      error_number = ER_FIL;
      return(ER_FIL);
   }

   /*
    * The first item in the file describes the magnification and
    * filter settings.
    *  magnification setting (range 1 to 8) = first nibble
    *  filter setting (range 1 to 3) = second nibble
    */
   fscanf(f,"%d",&mag_set);
   fscanf(f,"%d",&filter_set);

   /*
    * Check that the magnification number is within range.
    */
   if (check_mag() != TRUE){
      fclose(f);
      return(ER_MAG);
   }

   /*
    * Check that the filter setting is within range and determine the
    * number of samples to be acquired from the file.
    */
   if (check_filter() != TRUE){
      fclose(f);
      return(ER_FILT);
   }

   /*
    * calculate the scaling factors
    */
   x_division = SAMPLE_INT;
   y_division = mag[mag_set]/HSD_SAMPLES;

   /*
    * Read the data from file
    */
   sample_num = 0;
   while (sample_num<num_data) {
      fscanf(f,"%lf",&data[sample_num++]);
   }

   /*
    * Re-calculate data relative to the best fitting line (in a mean-
    * squared error sense)
    */
   remove_bias();

   /*
    * Data has been acquired
    */
   fclose(f);

  return(TRUE);
}


/*
 * Routine:	check_mag
 *
 * Description: Check that the magnification number is within range.
 *
 * Parameters:
 *
 * Returns:	TRUE	- magnification setting is valid
 *		ER_MAG	- magnification setting is invalid
 *
 * Example:     mag_set = 3;
 *		check_mag(3);
 *		return(TRUE);  * assuming 3<=NUM_MAG_SETTINGS) *
 *
 * Date:	22/5/91
 */
int check_mag()
{
   if (mag_set<1 || mag_set>NUM_MAG_SETTINGS) {
      error_number = ER_MAG;
      return(ER_MAG);
   }
   return(TRUE);
}


/*
 * Routine:	check_filter
 *
 * Description: Check that the filter setting is within range.
 *
 * Parameters:
 *
 * Returns:	TRUE	- filter setting is valid
 *		ER_FILT	- filter setting is invalid
 *
 * Example:     filter_set = 3;  * L type filter *
 *		check_filter(3);
 *		return(TRUE);
 *
 * Date:	22/5/91
 */
int check_filter()
{
   switch (filter_set) {
      case FILTER_J:
	 num_data = FILTER_J_SAMPLES;
	 break;
      case FILTER_K:
	 num_data = FILTER_K_SAMPLES;
	 break;
      case FILTER_L:
	 num_data = FILTER_L_SAMPLES;
	 break;
      default:
	 error_number = ER_FILT;
	 return(ER_FILT);
   }
   return(TRUE);
}


/*
 * Routine:	put_smoothed
 *
 * Description: Save the current smoothed spectral data
 *
 * Parameters:	none
 *
 * Returns:	TRUE	- success
 *		ER_FIL	- file not found
 *
 * Example:     
 *
 * Date:	2/7/91
 */
int put_smoothed()
{
   char filename[MAX_FIL_LEN];  /* the name of the file to be read */
   FILE *f;  /* file handle */
   int i;  /* count through data */
 
   /*
    * get the file name
    */
   printf("Enter the file name: ");
   (void) fscanf(stdin,"%s",filename);
   clrscr();

   /*
    * open the file for writing
    */
   f = fopen(filename,"w");
   if (f==NULL) {
      error_number = ER_FIL;
      return(ER_FIL);
   }

   /* 
    * save smoothed spectral data
    */
   if (tfm_valid == TRUE) {
      (void) fprintf(f,"%d\n",num_data);
      for(i=0;i<num_data;i++) {
         (void) fprintf(f,"%d  ",i);
         (void) fprintf(f,"%ld\n",spec_data[i]);
      }
   }

   /*
    * close the file
    */
   fclose(f);
   return(TRUE);
}


