/******************************************************************
 * Module:	fft.cpp
 *
 * Purpose:	Define fft routine.
 *
 * Date:	23/4/91
 *****************************************************************/
                    
#include <math.h>
#include "global.h"
#include "fft.h"                    
#include "complex.h"

/*
 * Routine:	fft
 *
 * Description:	The Fourier transform of the data items is calculated.
 *
 * Parameters:
 *
 * Returns:	TRUE	- successful calculation
 *		FALSE	- unsuccessful
 *
 * Example:	trans_data = [1,2,3,4], num_data = 4;
 *		following transformation, data = ?
 *
 * Date:	22/4/91
 */
void fft()
{
   double log_two_trans_num_data;
   int trans_num_data_2;
   struct complex com1,com2;  /* general complex variables */
   long k,j,na,nb,nc,nd,i,np,nr,ns,nq,n;  /* general variables */

   /*
    * initialize transform constants
    */
   log_two_trans_num_data = log(trans_num_data)/log(2.0);
   trans_num_data_2 = trans_num_data/2;
   com1.x = cos(MINUS_TWO_PI/trans_num_data);
   com1.y = sin(MINUS_TWO_PI/trans_num_data);

/*** testing **
   printf("log 2 Trans_data: %12.4f\n",log_two_trans_num_data);
   printf("coms %12.4f %12.4f\n",com1.x,com1.y);
*/
   /*
    * the transform (!)
    */
   for(k=1;k<=log_two_trans_num_data;k++){
      j=-1;
      na=(long)pow(2.0,(double)(k-1));
      nb=2*na;
      nc=trans_num_data/nb;
      com2.x=1.0;com2.y=0.0;
      for(nd=1;nd<=nc;nd++){
	 i=j+1;
	 j=j+na;
	 np=(nd-1)*nb;
	 for(nr=i;nr<=j;nr++){
	    ns=nr+trans_num_data_2;
	    dummy_data[np]=com_sum(trans_data[nr],trans_data[ns]);
	    nq=np+na;
	    dummy_data[nq]=com_prod(com2,com_diff(trans_data[nr],trans_data[ns]));
	    np++;
/**** testing **
            printf("dummy_data[1] %10.4f %10.4f",dummy_data[np].x,trans_data[np].x);
*/
	 }
	 com2=com_prod(com2,com_pow(com1,(double)na));
      }
      for(n=0;n<trans_num_data;n++) {
	 trans_data[n] = dummy_data[n];
      }
/**** testing ***
    printf("\niteration %4d, trans_data[1] %12.2d\n",k,trans_data[1].x);
    printf("dummy_data[1] %10.4f\n",dummy_data[1].x);
*/
   }

/*** testing **
   for(i=0;i<trans_num_data;i++) {
      trans_data[i].x = i;
      trans_data[i].y = 0;
   }
*/

}

