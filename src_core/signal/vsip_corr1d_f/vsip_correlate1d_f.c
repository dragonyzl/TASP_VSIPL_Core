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
/* $Id: vsip_correlate1d_f.c,v 1.1 1999/12/02 18:47:54 judd Exp $ */

#include<vsip.h>
#include<vsip_corr1dattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<VI_functions_f.h>

void vsip_correlate1d_f(
      const vsip_corr1d_f *cor,
      vsip_bias bias,
      const vsip_vview_f *h,
      const vsip_vview_f *x,
      const vsip_vview_f *y)
{
    vsip_vview_f xxr,xxi,hhr,hhi,
                 *xr = VI_vrealview_f(cor->x,&xxr),
                 *xi = VI_vimagview_f(cor->x,&xxi),
                 *hr = VI_vrealview_f(cor->h,&hhr),
                 *hi = VI_vimagview_f(cor->h,&hhi);
    void VI_vunbiassame_f(const vsip_corr1d_f*,
                          const vsip_vview_f*,
                          const vsip_vview_f*);
    void VI_vunbiasfull_f(const vsip_corr1d_f*,
                          const vsip_vview_f*,
                          const vsip_vview_f*);
    xr->length = cor->x->length - x->length;
    vsip_vfill_f(0,xr);
    xr->offset = xr->length;
    xr->length = x->length;
    vsip_vcopy_f_f(x,xr);
    xr->offset = 0;
    xr->length = cor->x->length;
    hr->length = h->length;
    vsip_vcopy_f_f(h,hr);
    hr->offset = hr->length;
    hr->length = cor->h->length - h->length;
    vsip_vfill_f(0,hr);
    hr->offset = 0;
    hr->length = cor->h->length;
    vsip_vfill_f(0,hi);
    vsip_vfill_f(0,xi);
    vsip_ccfftip_f(cor->fft,cor->h);
    vsip_ccfftip_f(cor->fft,cor->x);
    vsip_cvjmul_f(cor->x,cor->h,cor->x);
    vsip_cvconj_f(cor->x,cor->x);
    vsip_rscvmul_f(1/(vsip_scalar_f)cor->N,cor->x,cor->x);
    vsip_ccfftip_f(cor->fft,cor->x);
    switch(cor->support){
      case VSIP_SUPPORT_FULL:
        xr->offset = xr->length - cor->mn;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_vunbiasfull_f(cor,xr,y);
        } else {
            vsip_vcopy_f_f(xr,y);
        }
        break;
      case VSIP_SUPPORT_SAME:
        xr->offset = xr->length - cor->mn + cor->m/2;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_vunbiassame_f(cor,xr,y);
        } else {
            vsip_vcopy_f_f(xr,y);
        }
        break;
      case VSIP_SUPPORT_MIN:
        xr->offset = xr->length - cor->mn + cor->m - 1;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            vsip_svmul_f((vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,xr,y);
        } else {
            vsip_vcopy_f_f(xr,y);
        }
        break;
    }
    return;
}

void VI_vunbiasfull_f(
     const vsip_corr1d_f *cor, 
     const vsip_vview_f *x, 
     const vsip_vview_f *y)
{
    /* register */ vsip_length n = y->length;
    /* register */ vsip_length s1 = n - cor->m;
    /* register */ vsip_length s2 = cor->m;
    /* register */ vsip_stride xst = x->stride * x->block->rstride,
                               yst = y->stride * y->block->rstride;
    vsip_scalar_f *xp = (x->block->array) + x->offset * x->block->rstride,
                  *yp = (y->block->array) + y->offset * y->block->rstride;
    vsip_scalar_f scale2 = (vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,
                  scale1 = (vsip_scalar_f)1.0;
    while(n-- > s1){
         *yp = *xp / scale1;
          scale1 += 1.0;
          yp+=yst; xp+=xst;
    }
    n++;
    while(n-- > s2){
         *yp = *xp * scale2;
          yp+=yst; xp+=xst;
    }
    n++;
    n++;
    while(n-- > 1){
         *yp = *xp / (vsip_scalar_f)n;
          yp+=yst; xp+=xst;
    }
    return;
}

void VI_vunbiassame_f(
     const vsip_corr1d_f *cor, 
     const vsip_vview_f *x, 
     const vsip_vview_f *y)
{
    /* register */ vsip_length n = y->length;
    /* register */ vsip_length s1 = n - cor->m/2; 
    /* register */ vsip_length s2 = cor->m/2;
    /* register */ vsip_stride xst = x->stride * x->block->rstride,
                               yst = y->stride * y->block->rstride;
    vsip_scalar_f *xp = (x->block->array) + x->offset * x->block->rstride,
                  *yp = (y->block->array) + y->offset * y->block->rstride;
    vsip_scalar_f scale2 = 1/(vsip_scalar_f)cor->m,
                  scale1 = (vsip_scalar_f)(cor->m/2);
    if((cor->m % 2) != 0){
        scale1 += 1.0;
        s2++;
    }
    xp -= xst; yp -= yst;
    while(n-- > s1){    
         *(yp+=yst) = *(xp+=xst) /(scale1);
          scale1 += 1.0; 
    } 
    n++;
    while(n-- > s2)
         *(yp+=yst) = *(xp+=xst) * scale2;
    n++;
    scale1 -= 1.0;
    while(n-- > 0){
         *(yp+=yst) = *(xp+=xst) / scale1;
          scale1 -= 1.0;
    }
    return;
}
