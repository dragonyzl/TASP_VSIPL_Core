/* Created RJudd March 21, 1999 */
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
/* $Id: vsip_conv1d_destroy_d.c,v 1.1 1999/12/05 02:07:18 judd Exp judd $ */

#include<vsip.h>
#include<vsip_conv1dattributes_d.h>

int vsip_conv1d_destroy_d(vsip_conv1d_d *conv)
{
   if(conv != NULL){
      if(conv->x != NULL) vsip_cvalldestroy_d(conv->x);
      if(conv->H != NULL) vsip_cvalldestroy_d(conv->H);
      if(conv->fft != NULL) vsip_fft_destroy_d(conv->fft);
      if(conv->fftm != NULL) vsip_fftm_destroy_d(conv->fftm);
      if(conv->Xm != NULL) vsip_cmalldestroy_d(conv->Xm);
      free(conv);
   }
   return 0;
}