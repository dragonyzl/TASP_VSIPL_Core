/* Created By RJudd January 9, 1999 */
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
/* $Id: vsip_fftm_destroy_f.c,v 1.2 1999/12/04 03:16:13 judd Exp judd $ */
/* destroy vsip vectors created in vsip_xxfftxx_create_f */
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_fftmattributes_f.h>

int vsip_fftm_destroy_f(vsip_fftm_f *fft)
{
    if(fft != NULL){
       vsip_cvalldestroy_f(fft->wt);
       vsip_cvalldestroy_f(fft->temp);
       free(fft->pn);
       free(fft->p0);
       free(fft->pF);
       free(fft->index);
       free(fft);
    }
    return 0;
}
