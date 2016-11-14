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
/* $Id: vsip_ccfftmop_create_d.c,v 1.1 1999/12/05 01:58:58 judd Exp judd $ */
/* calculate number of factors of 2,3,4 in N */
/* calculate N = 2^n2 * 4^n4 * 8^n8 * 3^n3 * 5^n5 *7^n7 * n */
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_fftmattributes_d.h>
#include"VI_ftm_d.h"
#include<VI_functions_d.h>
vsip_fftm_d* vsip_ccfftmop_create_d(vsip_length M,
                       vsip_length N,
                       vsip_scalar_d scale,
                       vsip_fft_dir dir,
                       vsip_major major,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_d wt1,wt2;
    vsip_fftm_d *fft = (vsip_fftm_d*) malloc(sizeof(vsip_fftm_d));
    if(fft == NULL) return (vsip_fftm_d*) NULL;
    fft->N = N;
    fft->M = M;
    fft->major = major;
    fft->MN = (major == VSIP_COL) ? M : N;
    fft->mN = (major == VSIP_COL) ? N : M;
    fft->scale = scale;
    fft->d = dir;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_d(fft->MN,VSIP_MEM_NONE); /* create a space to copy too when unsorting */
    fft->wt = vsip_cvcreate_d(fft->MN,VSIP_MEM_NONE);
    fft->index = (vsip_scalar_vi*) malloc(fft->MN * sizeof(vsip_scalar_vi));
    if((fft->pn == NULL) || (fft->p0 == NULL) || 
       (fft->pF == NULL) || (fft->wt == NULL) ||
       (fft->temp == NULL) || (fft->index == NULL)){
         vsip_fftm_destroy_d(fft);
         return (vsip_fftm_d*) NULL;
    }
    fft->length = VI_nuV_d(fft->MN,
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
          vsip_vramp_d(0,- VI_ftm_d_2PI/fft->MN,wtR);  
        }else{ 
          vsip_vramp_d(0, VI_ftm_d_2PI/fft->MN,wtR); 
        }   
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }

    if((fft->p0[0] == 1) && (fft->pF[0] == fft->MN)){
        fft->dft = 1; /* implies no supported factor exists */
    } else {
        fft->dft = 0; /* implies at least one of the supported factors exist */
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< fft->MN; i++) fft->index[i] = VI_jofk_d(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
