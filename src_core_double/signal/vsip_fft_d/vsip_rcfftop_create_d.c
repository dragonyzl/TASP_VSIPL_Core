/* Created By RJudd October 14, 1998 */
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
/* $Id: vsip_rcfftop_create_d.c,v 1.1 1999/12/05 02:01:22 judd Exp judd $ */
/* real to complex fft */
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_fftattributes_d.h>
#include"VI_ft_d.h"
#include<VI_functions_d.h>

vsip_fft_d* vsip_rcfftop_create_d(vsip_length N,
                       vsip_scalar_d scale,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_d wt1,wt2;
    vsip_fft_d *fft = (vsip_fft_d*) malloc(sizeof(vsip_fft_d));
    if(fft == NULL) return (vsip_fft_d*) NULL;
    fft->N = N/2;
    fft->scale = scale;
    fft->d = VSIP_FFT_FWD;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_d(2 * fft->N + 2,VSIP_MEM_NONE); /* create some work space */
    fft->wt = vsip_cvcreate_d(fft->N,VSIP_MEM_NONE);
    fft->index = (vsip_scalar_vi*) malloc(fft->N * sizeof(vsip_scalar_vi));
    /* check for creation problem */
    if( (fft->pn == NULL) || (fft->p0 == NULL) || 
        (fft->pF == NULL) || (fft->wt == NULL) || 
        (fft->temp == NULL) || (fft->index == NULL)){
          vsip_fft_destroy_d(fft);
          return (vsip_fft_d*) NULL;
    }
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_RCFFTOP; 
    /* calculate factors, fft->length is number of factors found */
    fft->length = VI_nuV_d(fft->N,
         fft->pn,
         fft->p0,
         fft->pF);

    /* create twiddle table */
    { 
        vsip_vview_d *wtR = VI_vrealview_d(fft->wt,&wt1);
        vsip_vview_d *wtI = VI_vimagview_d(fft->wt,&wt2); 
        vsip_vramp_d(0,- VI_ft_d_2PI/fft->N,wtR);  
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }
    /* create euler for rcfftop in fft->temp */
    fft->temp->offset = fft->N + 1;
    fft->temp->length = fft->N + 1;
    {
        vsip_vview_d *wtR = VI_vrealview_d(fft->temp,&wt1);
        vsip_vview_d *wtI = VI_vimagview_d(fft->temp,&wt2); 
        vsip_vramp_d(0,- VI_ft_d_PI/fft->N,wtR);
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }
    fft->temp->offset = 0;
    fft->temp->length = fft->N;
        
    if((fft->p0[0] == 1) && (fft->pF[0] == fft->N)){
        fft->dft = 1;
    } else {
        fft->dft = 0;
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< fft->N; i++) fft->index[i] = VI_jofk_d(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
