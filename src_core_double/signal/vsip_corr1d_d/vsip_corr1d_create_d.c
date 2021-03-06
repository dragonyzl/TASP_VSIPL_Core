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
/* $Id: vsip_corr1d_create_d.c,v 1.1 1999/12/05 02:03:32 judd Exp judd $ */

#include<vsip.h>
#include<vsip_corr1dattributes_d.h>

vsip_corr1d_d *vsip_corr1d_create_d(
     vsip_length M,
     vsip_length N,
     vsip_support_region support,
     unsigned int ntimes,
     vsip_alg_hint hint)
{
     vsip_corr1d_d *cor = (vsip_corr1d_d*) malloc(sizeof(vsip_corr1d_d));
     if(cor == NULL) return (vsip_corr1d_d*) NULL;
     cor->support = support;
     cor->hint = hint;
     cor->ntimes = ntimes;
     cor->m  = M;
     cor->n  = N;
     cor->mn = M + N - 1;
     if(support == VSIP_SUPPORT_MIN){
        cor->lag_len = N-M+1;
     } else if( support == VSIP_SUPPORT_SAME){
        cor->lag_len = N;
     } else {
        cor->lag_len = N + M -1;
     }
     {
        vsip_length p = cor->mn;
        cor->N = 2;
        while(cor->N <= p){
          cor->N *=2;
        } 
     }
     cor->x = vsip_cvcreate_d(cor->N,VSIP_MEM_NONE);
     cor->h = vsip_cvcreate_d(cor->N,VSIP_MEM_NONE);
     cor->fft = vsip_ccfftip_create_d(cor->N,1,VSIP_FFT_FWD,0,0);
     if((cor->x == NULL) ||
        (cor->h == NULL) ||
        (cor->fft == NULL)){
          vsip_corr1d_destroy_d(cor);
          return (vsip_corr1d_d*)NULL;
     }
     return cor;
}
