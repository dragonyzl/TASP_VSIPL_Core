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
#include <omp.h>

void vsip_correlate1d_f_para(
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
    void VI_vunbiassame_f_para(const vsip_corr1d_f*,
                          const vsip_vview_f*,
                          const vsip_vview_f*);
    void VI_vunbiasfull_f_para(const vsip_corr1d_f*,
                          const vsip_vview_f*,
                          const vsip_vview_f*);
    xr->length = cor->x->length - x->length;
    vsip_vfill_f(0,xr);
    xr->offset = xr->length;
    xr->length = x->length;
    vsip_vcopy_f_f_para(x,xr);
    xr->offset = 0;
    xr->length = cor->x->length;
    hr->length = h->length;
    vsip_vcopy_f_f_para(h,hr);
    hr->offset = hr->length;
    hr->length = cor->h->length - h->length;
    vsip_vfill_f(0,hr);
    hr->offset = 0;
    hr->length = cor->h->length;
    vsip_vfill_f(0,hi);
    vsip_vfill_f(0,xi);
    vsip_ccfftip_f_para(cor->fft,cor->h);
    vsip_ccfftip_f_para(cor->fft,cor->x);
    vsip_cvjmul_f_para(cor->x,cor->h,cor->x);
    vsip_cvconj_f_para(cor->x,cor->x);
    vsip_rscvmul_f_para(1/(vsip_scalar_f)cor->N,cor->x,cor->x);
    vsip_ccfftip_f_para(cor->fft,cor->x);
    switch(cor->support){
      case VSIP_SUPPORT_FULL:
        xr->offset = xr->length - cor->mn;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_vunbiasfull_f_para(cor,xr,y);
        } else {
            vsip_vcopy_f_f_para(xr,y);
        }
        break;
      case VSIP_SUPPORT_SAME:
        xr->offset = xr->length - cor->mn + cor->m/2;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_vunbiassame_f_para(cor,xr,y);
        } else {
            vsip_vcopy_f_f_para(xr,y);
        }
        break;
      case VSIP_SUPPORT_MIN:
        xr->offset = xr->length - cor->mn + cor->m - 1;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            vsip_svmul_f_para((vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,xr,y);
        } else {
            vsip_vcopy_f_f_para(xr,y);
        }
        break;
    }
    return;
}

void VI_vunbiasfull_f_para(
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


vsip_length i;
vsip_scalar_f *xpinit=xp;
vsip_scalar_f *ypinit=yp;

#pragma omp parallel for
      for(i=0;i<(n-s1);i++){
        *(ypinit+(vsip_stride)(i)*yst) = *(xpinit+(vsip_stride)(i)*xst) / (vsip_scalar_f)(scale1+i);
      }

scale1+=(vsip_scalar_f)(n-s1);
if(n>s1){
    xpinit=xpinit+(vsip_stride)(n-s1)*xst;
    ypinit=ypinit+(vsip_stride)(n-s1)*yst;
    n=s1;
}

#pragma omp parallel for  
      for(i=0;i<(n-s2);i++){
        *(ypinit+i*yst) = *(xpinit+i*xst) * (scale2);
      }

if(n>s2){
    xpinit=xpinit+(vsip_stride)(n-s2)*xst;
    ypinit=ypinit+(vsip_stride)(n-s2)*yst;
    n=s2;
}
n++;

#pragma omp parallel for
      for(i=0;i<n;i++){
        *(ypinit+i*yst) = *(xpinit+i*xst) / (vsip_scalar_f)(n-i-1);
      }
    return;
}

void VI_vunbiassame_f_para(
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

vsip_length i;

vsip_scalar_f *xpinit=xp;
vsip_scalar_f *ypinit=yp;

#pragma omp parallel for schedule(dynamic)
      for(i=0;i<(n-s1);i++){
        *(ypinit+i*yst) = *(xpinit+i*xst) / (vsip_scalar_f)(scale1+i);
      }
scale1+=(vsip_scalar_f)(n-s1);
if(n>s1){
    xpinit=xpinit+(n-s1)*xst;
    ypinit=ypinit+(n-s1)*yst;
    n=s1;
}

#pragma omp parallel for schedule(dynamic)
      for(i=0;i<(n-s2);i++){
        *(ypinit+(i+1)*yst) = *(xpinit+(i+1)*xst) * (scale2);
      }


if(n-s2>0){
    xpinit=xpinit+(n-s2)*xst;
    ypinit=ypinit+(n-s2)*yst;
    n=s2;
}

scale1 -= 1.0;

#pragma omp parallel for schedule(dynamic)
      for(i=0;i<n;i++){
        *(ypinit+(i)*yst) = *(xpinit+(i)*xst) /  (vsip_scalar_f)(scale1-i);
      }
    return;
}
