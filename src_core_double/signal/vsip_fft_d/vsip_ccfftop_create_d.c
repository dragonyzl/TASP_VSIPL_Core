/* Created By RJudd August 27, 1998 */
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
/* $Id: vsip_ccfftop_create_d.c,v 1.1 1999/12/05 02:01:19 judd Exp judd $ */
/* calculate number of factors of 2,3,4 in N */
/* calculate N = 2^n2 * 4^n4 * 8^n8 * 3^n3 * 5^n5 *7^n7 * n */
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_fftattributes_d.h>
#include"VI_ft_d.h"
#include<VI_functions_d.h>
vsip_fft_d* vsip_ccfftop_create_d(vsip_length N,
                       vsip_scalar_d scale,
                       vsip_fft_dir dir,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_d wt1,wt2;
    vsip_fft_d *fft = (vsip_fft_d*) malloc(sizeof(vsip_fft_d));
    if(fft == NULL) return (vsip_fft_d*) NULL;
    fft->N = N;
    fft->scale = scale;
    fft->d = dir;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_d(N,0); /* create a space to copy too when unsorting */
    fft->wt = vsip_cvcreate_d(N,0);
    fft->index = (vsip_scalar_vi*) malloc(N * sizeof(vsip_scalar_vi));
    if((fft->pn == NULL) || (fft->p0 == NULL) || 
       (fft->pF == NULL) || (fft->wt == NULL) ||
       (fft->temp == NULL) || (fft->index == NULL)){
         vsip_fft_destroy_d(fft);
         return (vsip_fft_d*) NULL;
    }
    fft->length = VI_nuV_d(N,
         fft->pn,
         fft->p0,
         fft->pF);
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_CCFFTOP; 

    /* create twiddle table */
    { 
        vsip_vview_d *wtR = VI_vrealview_d(fft->wt,&wt1); 
        vsip_vview_d *wtI = VI_vimagview_d(fft->wt,&wt2); 
        if(dir == -1){ 
          vsip_vramp_d(0,- VI_ft_d_2PI/N,wtR);  
        }else{ 
          vsip_vramp_d(0, VI_ft_d_2PI/N,wtR); 
        }   
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }

    if((fft->p0[0] == 1) && (fft->pF[0] == N)){
        fft->dft = 1; /* implies no supported factor exists */
    } else {
        fft->dft = 0; /* implies at least one of the supported factors exist */
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< N; i++) fft->index[i] = VI_jofk_d(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
/* nuV*/
/* calculate number of factors of 2,3,4,5,7,8,n in N */
/* so that N = 2^n2 * 4^n4 * 8^n8 * 3^n3 * 5^n5 *7^n7 * n */

vsip_length VI_nuV_d(vsip_length N, 
         vsip_scalar_vi *pn,
         vsip_scalar_vi *p0,
         vsip_scalar_vi *pF)
{
    vsip_scalar_vi n2=0,n3=0,n4=0,n5=0,n8=0,n7=0;
    vsip_scalar_vi k = 0;
    vsip_scalar_vi n = N;

    while((n % 3) == 0){
        n /= 3;
        n3++;
    }
    if(n3 != 0){ 
          p0[k]=3;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n3 + 1;
          }else{
             pF[k] = 3;
             pn[k] = n3;
          }
          k++;
    }

    while((n % 5) == 0){
        n /= 5;
        n5++;
    }
    if(n5 != 0){ 
          p0[k] = 5;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n5 + 1;
          }else{
             pF[k] = 5;
             pn[k] = n5;
          }
          k++;
    }

    while((n % 7) == 0){
        n /= 7;
        n7++;
    }
    if(n7 != 0){ 
          p0[k] = 7;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n7 + 1;
          }else{
             pF[k] = 7;
             pn[k] = n7;
          }
          k++;
    }

    while((n % 8) == 0) {
        n /= 8;
        n8++;
    }
    if(n8 != 0){ 
          p0[k] = 8;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n8 + 1;
          }else{
             pF[k] = 8;
             pn[k] = n8;
          }
          k++;
    }

    while((n % 4) == 0) {
        n /= 4;
        n4++;
    }
    if(n4 != 0){ 
          p0[k] = 4;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n4 + 1;
          }else{
             pF[k] = 4;
             pn[k] = n4;
          }
          k++;
    }

    while((n % 2) == 0) {
        n /= 2;
        n2++;
    }
    if(n2 != 0){ 
          p0[k] = 2;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n2 + 1;
          }else{
             pF[k] = 2;
             pn[k] = n2;
          }
          k++;
    }

    if((n != 1) && (k == 0)){ 
          p0[k] = 1;
          pF[k] = n;
          pn[k] = 1;
          k++;
    }
    return (vsip_length)k;
}
/* Index conversion routine for DFT's */
/* 2.2.3 of Van Loan, "computational Frameworks for the */
/* Fast Fourier Transform */
vsip_scalar_vi VI_jofk_d(vsip_scalar_vi k, /* index to reverse */
                    vsip_scalar_vi *pn,
                    vsip_scalar_vi *p0,
                    vsip_scalar_vi pF,
                    vsip_length fn)
{
   vsip_scalar_vi l = (vsip_scalar_vi)fn;
   vsip_scalar_vi i,q; 
   vsip_scalar_vi j = 0; 
   vsip_scalar_vi m = k; 
   vsip_scalar_vi aq,s,p; 
   for(q = 0; q < l; q++){ 
       i = pn[q] - 1; 
       p = p0[q]; 
       while(i-- > 0){ 
          s = m/p; 
          aq = m - s * p; 
          j = p * j + aq; 
          m = s; 
       }  
   } 
   s = m/pF; 
   aq = m - s * pF; 
   j = pF * j + aq; 
   return j; 
}
