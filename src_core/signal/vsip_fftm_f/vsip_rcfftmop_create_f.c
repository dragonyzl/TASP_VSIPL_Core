/* Created By RJudd January 13, 1998 */
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
/* $Id: vsip_rcfftmop_create_f.c,v 1.1 1999/12/02 18:53:25 judd Exp judd $ */
/* real to complex fft */
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_fftmattributes_f.h>
#include"VI_ftm_f.h"
#include<VI_functions_f.h>

vsip_fftm_f* vsip_rcfftmop_create_f(vsip_length M,
                       vsip_length N,
                       vsip_scalar_f scale,
                       vsip_major major,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_f wt1,wt2;
    vsip_fftm_f *fft = (vsip_fftm_f*) malloc(sizeof(vsip_fftm_f));
    if(fft == NULL) return (vsip_fftm_f*) NULL;
    fft->N = N;
    fft->M = M;
    fft->MN = (major == VSIP_ROW) ? N/2: M/2;
    fft->mN = (major == VSIP_ROW) ?  M : N;
    fft->major = major;
    fft->scale = scale;
    fft->d = VSIP_FFT_FWD;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_f(2 * fft->MN + 2,VSIP_MEM_NONE); /* create some work space */
    fft->wt = vsip_cvcreate_f(fft->MN,VSIP_MEM_NONE);
    fft->index = (vsip_scalar_vi*) malloc(fft->MN * sizeof(vsip_scalar_vi));
    /* check for creation problem */
    if( (fft->pn == NULL) || (fft->p0 == NULL) || 
        (fft->pF == NULL) || (fft->wt == NULL) || 
        (fft->temp == NULL) || (fft->index == NULL)){
          vsip_fftm_destroy_f(fft);
          return (vsip_fftm_f*) NULL;
    }
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_RCFFTOP; 
    /* calculate factors, fft->length is number of factors found */
    fft->length = VI_nuV_f(fft->MN,
         fft->pn,
         fft->p0,
         fft->pF);

    /* create twiddle table */
    { 
        vsip_vview_f *wtR = VI_vrealview_f(fft->wt,&wt1);
        vsip_vview_f *wtI = VI_vimagview_f(fft->wt,&wt2); 
        vsip_vramp_f((vsip_scalar_f)0,- (vsip_scalar_f)VI_ftm_f_2PI/fft->MN,wtR);  
        vsip_vsin_f(wtR,wtI);
        vsip_vcos_f(wtR,wtR);
    }
    /* create euler for rcfftop in fft->temp */
    fft->temp->offset = fft->MN + 1;
    fft->temp->length = fft->MN + 1;
    {
        vsip_vview_f *wtR = VI_vrealview_f(fft->temp,&wt1);
        vsip_vview_f *wtI = VI_vimagview_f(fft->temp,&wt2); 
        vsip_vramp_f((vsip_scalar_f)0,- (vsip_scalar_f)VI_ftm_f_PI/fft->MN,wtR);
        vsip_vsin_f(wtR,wtI);
        vsip_vcos_f(wtR,wtR);
    }
    fft->temp->offset = 0;
    fft->temp->length = fft->MN;
        
    if((fft->p0[0] == 1) && (fft->pF[0] == fft->MN)){
        fft->dft = 1;
    } else {
        fft->dft = 0;
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< fft->MN; i++) fft->index[i] = VI_jofk_f(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
