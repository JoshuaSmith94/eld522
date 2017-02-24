/******************************************************************
 * Module:	main.c
 *
 * Purpose:	Analyze data acquired from the Talysurf.
 *
 * Contents:	main		- controls the program
 *		assign_memory	- grab memory needed by the
 *				  arrays of the program
 *
 * Date:	22/5/91
 *****************************************************************/

/*
 * global definitions
 */
#include "global.h"

/*
 * declarations
 */
#include "main.h"
#include "load.h"
#include "fourier.h"
#include "complex.h"
#include "error.h"

/*
 * data are valid if already read from a file, transform values if
 * transform has been calculated for the data currently in memory, and
 * dxf_valid if a graph is to be plotted in dxf format.
 */
int data_valid;
int tfm_valid;

/*
 * Routine:	main
 *
 * Description:	Control the running of the program.
 *
 * Parameters:	none
 *
 * Returns:	TRUE 			- successful completion
 *		positive integer	- unsuccessful
 *
 * Example:
 *
 * Date:	22/5/91
 */
main()
{
   int option; /* user input */

   /*
    * assign memory to the data and transform arrays
    */
   if (assign_memory() != TRUE) {
      (void) print_error();
      return(error_number);
   }

   /*
    * set up valid flags
    */
   data_valid = FALSE;
   tfm_valid = FALSE;

   /*
    * wait for an input
    */
   while (1) {
      printf("Enter your option (l,f,p,m,e): ");
      option=getc(stdin);
      /*
       * respond to the user input
       */
      switch(option) {
         case 'l': if (load() != TRUE) {       /* load data */
                      (void) print_error();
                      return(error_number);
                   }
                   data_valid = TRUE;
			 tfm_valid = FALSE;

                   break;

         case 'f': if (data_valid == TRUE) {
	 	      			 if (tfm_valid == FALSE) {   
                         if (calculate_fft() != TRUE) {   /* perform fft */
                            (void) print_error();
                            return(error_number);
                         }
		      			 }
		      			 tfm_valid = TRUE;
                     }
                   break;

	 case 'p': if (tfm_valid == TRUE) {
		      	  if (calc_params() != TRUE) {
			 			  (void) print_error();
			 			  return(error_number);
		      	  }
                 if (put_smoothed() != TRUE) {
			 			  (void) print_error();
		      	  }
		      	  getc(stdin);
		   	  }
		   	  break;
		    
    case 'm': if (data_valid == TRUE && tfm_valid == TRUE) {
		      	  if (calc_params() != TRUE) {
			 			  (void) print_error();
			 			  return(error_number);
		      	  }
		      	  if (print_params() != TRUE) {
			 			  (void) print_error();
			 			  return(error_number);
		      	  }
		   	  }
		   	  break;

    case 'h': printf("\n\n\n\nhelp\n----\n");
			     printf("l - load data\n");
		   	  printf("f - compute frequency spectrum data\n");

		      printf("p - save frequency spectral data\n");
		   	  printf("m - compute parameters\n");
		   	  printf("e - end program\n\n\n");
		   	  getc(stdin);
		   	  break;

    case 'e': 
              return(TRUE);         /* successful completion */

    default:  invalid_input();
    }
  }

}


/*
 * Routine:	assign_memory
 *
 * Description:	Find memory space for the various arrays used in the
 *		program.
 *
 * Parameters:	none
 *
 * Returns:	TRUE	- memory allocated
 *		ER_MEM	- memory not allocated
 *
 * Example:
 *
 * Date:	22/5/91
 */

/*
 * memory allocation routines
 */
#include <stdlib.h>
#include <malloc.h>  // not needed for calloc?

/*
 * data and transform arrays
 */

/* Talysurf data */
int num_data;
double  *data;
double  *smooth_data;

/* transform data */
int trans_num_data;
struct complex  *trans_data;
struct complex  *dummy_data;

/* spectral data */
int spec_num_data;
double  *spec_data;
int smooth_num_data = SMOOTH_MAX_DATA;
struct smoothed  *smooth;
int num_combinations;
struct smoothed  *saved_smooth;

int assign_memory()
{
   /*
    * memory for the data acquired by the Talysurf
    */
   data = (double *) calloc(MAX_DATA,sizeof(double));
   smooth_data = (double *) calloc(MAX_DATA,sizeof(double));

   /*
    * transform data and dummy transform data
    */
   trans_data = (struct complex *)
      calloc(MAX_DATA,sizeof(struct complex));
   dummy_data = (struct complex *)
      calloc(MAX_DATA,sizeof(struct complex));


   /*
    * spectral data
    */
   spec_data = (double *) calloc(SPEC_MAX_DATA,sizeof(double));
   smooth = (struct smoothed *)
      calloc(SMOOTH_MAX_DATA,sizeof(struct smoothed));
   saved_smooth = (struct smoothed *)
      calloc(SMOOTH_MAX_DATA,sizeof(struct smoothed));

   /*
    * test that allocation has been achieved
    */
   if (data==NULL || trans_data==NULL || dummy_data==NULL || 
      spec_data==NULL || smooth==NULL) {
         error_number = ER_MEM;
         return(ER_MEM);
   }

   return(TRUE);
}

/*
 * Routine:	invalid_input
 *
 * Description:	Respond to an invalid key press
 *
 * Parameters:	none
 *
 * Returns:	TRUE	- successful completion
 *
 * Example:
 *
 * Date:	28/5/91
 */
int invalid_input()
{
   return(TRUE);
}

