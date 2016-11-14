/* Created RJudd March 17, 1999 */
/* SPAWARSYSCEN D881 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_ccorr1d_destroy_d.c,v 1.2 1999/12/05 02:04:46 judd Exp judd $ */

#include<vsip.h>
#include<vsip_ccorr1dattributes_d.h>

int vsip_ccorr1d_destroy_d(vsip_ccorr1d_d *cor)
{
   if(cor != NULL){
      vsip_cvalldestroy_d(cor->x);
      vsip_cvalldestroy_d(cor->h);
      vsip_fft_destroy_d(cor->fft);
      free(cor);
   }
   return 0;
}
      
