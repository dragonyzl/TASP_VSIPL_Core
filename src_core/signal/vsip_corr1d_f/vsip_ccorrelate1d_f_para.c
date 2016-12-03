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
/* $Id: vsip_ccorrelate1d_f.c,v 1.1 1999/12/02 18:47:52 judd Exp $ */

#include<vsip.h>
#include<vsip_ccorr1dattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include <omp.h>

void vsip_ccorrelate1d_f_para(
      const vsip_ccorr1d_f *cor,
      vsip_bias bias,
      const vsip_cvview_f *h,
      const vsip_cvview_f *x,
      const vsip_cvview_f *y)
{
    vsip_cvview_f xx = *cor->x,
                  hh = *cor->h;
    vsip_cvview_f *xt = &xx,
                  *ht = &hh;
    void VI_cvunbiassame_f_para(const vsip_ccorr1d_f*,
                          const vsip_cvview_f*,
                          const vsip_cvview_f*);
    void VI_cvunbiasfull_f_para(const vsip_ccorr1d_f*,
                          const vsip_cvview_f*,
                          const vsip_cvview_f*);
    xt->length = cor->x->length - x->length;
    vsip_cvfill_f(vsip_cmplx_f(0,0),xt);
    xt->offset = xt->length;
    xt->length = x->length;
    vsip_cvcopy_f_f_para(x,xt);
    xt->length = cor->x->length;
    xt->offset = 0;

    ht->length = cor->h->length - h->length;
    ht->offset = h->length; 
    vsip_cvfill_f(vsip_cmplx_f(0,0),ht);
    ht->offset = 0;
    ht->length = h->length;
    vsip_cvcopy_f_f_para(h,ht);

    vsip_ccfftip_f_para(cor->fft,cor->h);
    vsip_ccfftip_f_para(cor->fft,cor->x);
    
    vsip_cvjmul_f_para(cor->x,cor->h,cor->x);
    vsip_cvconj_f_para(cor->x,cor->x);
    vsip_rscvmul_f_para(1/(vsip_scalar_f)cor->N,cor->x,cor->x);
    vsip_ccfftip_f_para(cor->fft,cor->x);
    vsip_cvconj_f_para(cor->x,cor->x);

    switch(cor->support){
      case VSIP_SUPPORT_FULL:
        xt->offset = xt->length - cor->mn;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_cvunbiasfull_f_para(cor,xt,y);
        } else {
            vsip_cvcopy_f_f_para(xt,y);
        }
        break;
      case VSIP_SUPPORT_SAME:
        xt->offset = xt->length - cor->mn + cor->m/2;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_cvunbiassame_f_para(cor,xt,y);
        } else {
            vsip_cvcopy_f_f_para(xt,y);
        }
        break;
      case VSIP_SUPPORT_MIN:
        xt->offset = xt->length - cor->mn + cor->m - 1;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            vsip_rscvmul_f_para((vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,xt,y);
        } else {
            vsip_cvcopy_f_f_para(xt,y);
        }
        break;
    }
    return;
}

void VI_cvunbiasfull_f_para(
     const vsip_ccorr1d_f *cor, 
     const vsip_cvview_f *x, 
     const vsip_cvview_f *y)
{
    /* register */ vsip_length n = y->length;
    /* register */ vsip_length s1 = n - cor->m;
    /* register */ vsip_length s2 = cor->m;
    /* register */ vsip_stride cxst = x->block->cstride,
                               cyst = y->block->cstride;
    /* register */ vsip_stride xst = x->stride * cxst,
                               yst = y->stride * cyst;
    vsip_scalar_f *xpr = (x->block->R->array) + x->offset * cxst,
                  *ypr = (y->block->R->array) + y->offset * cyst;
    vsip_scalar_f *xpi = (x->block->I->array) + x->offset * cxst,
                  *ypi = (y->block->I->array) + y->offset * cyst;
    vsip_scalar_f scale2 = (vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,
                  scale1 = (vsip_scalar_f)1.0;

      vsip_length i;

vsip_scalar_f *xprinit=xpr;
vsip_scalar_f *xpiinit=xpi;
vsip_scalar_f *yprinit=ypr;
vsip_scalar_f *ypiinit=ypi;
#pragma omp parallel for schedule(dynamic) reduction(+:scale1)
      for(i=0;i<(n-s1);i++){
#pragma omp critical (scale1)
  {
        vsip_stride xstride=i*xst;
        vsip_stride ystride=i*yst;
        *(yprinit+ystride) = *(xprinit+xstride) / scale1;
        *(ypiinit+ystride) = *(xpiinit+xstride) / scale1;
        scale1 += 1.0;
  }
      }

if(n-s1>0){
    xprinit=xprinit+(n-s1)*xst;
    xpiinit=xpiinit+(n-s1)*xst;
    yprinit=yprinit+(n-s1)*yst;
    ypiinit=ypiinit+(n-s1)*yst;
    n=s1;
}
#pragma omp parallel for schedule(dynamic) 
      for(i=0;i<(n-s2);i++){
        vsip_stride xstride=i*xst;
        vsip_stride ystride=i*yst;
        *(yprinit+ystride) = *(xprinit+xstride) * scale2;
        *(ypiinit+ystride) = *(xpiinit+xstride) * scale2;
      }

if(n-s2>0){
    xprinit=xprinit+(n-s2)*xst;
    xpiinit=xpiinit+(n-s2)*xst;
    yprinit=yprinit+(n-s2)*yst;
    ypiinit=ypiinit+(n-s2)*yst;
    n=s2;
}
n++;

#pragma omp parallel for schedule(dynamic)
      for(i=0;i<(n-1);i++){
        vsip_stride xstride=i*xst;
        vsip_stride ystride=i*yst;
        *(yprinit+ystride) = *(xprinit+xstride) / (vsip_scalar_f)(n-i-1);
        *(ypiinit+ystride) = *(xpiinit+xstride) / (vsip_scalar_f)(n-i-1);
      }

    return;
}

void VI_cvunbiassame_f_para(
     const vsip_ccorr1d_f *cor, 
     const vsip_cvview_f *x, 
     const vsip_cvview_f *y)
{
    /* register */ vsip_length n = y->length;
    /* register */ vsip_length s1 = n - cor->m/2; 
    /* register */ vsip_length s2 = cor->m/2;
    /* register */ vsip_stride cxst = x->block->cstride,
                               cyst = y->block->cstride;
    /* register */ vsip_stride xst = x->stride * cxst,
                               yst = y->stride * cyst;
    vsip_scalar_f *xpr = (x->block->R->array) + x->offset * cxst,
                  *ypr = (y->block->R->array) + y->offset * cyst;
    vsip_scalar_f *xpi = (x->block->I->array) + x->offset * cxst,
                  *ypi = (y->block->I->array) + y->offset * cyst;
    vsip_scalar_f scale2 = 1/(vsip_scalar_f)cor->m,
                  scale1 = (vsip_scalar_f)(cor->m/2);
    if((cor->m % 2) != 0){
        scale1 += 1.0;
        s2++;
    }


    vsip_length i;

vsip_scalar_f *xprinit=xpr;
vsip_scalar_f *xpiinit=xpi;
vsip_scalar_f *yprinit=ypr;
vsip_scalar_f *ypiinit=ypi;

int idx=0;
#pragma omp parallel for shared(idx)
      for(i=0;i<(n-s1);i++){
  #pragma omp critical (scale1) 
  {
        vsip_stride xstride=i*xst;
        vsip_stride ystride=i*yst;
        *(yprinit+ystride) = *(xprinit+xstride) / scale1;
        *(ypiinit+ystride) = *(xpiinit+xstride) / scale1;
        idx++;
        scale1 += 1.0;
  }
      }


if(n-s1>0){
    xprinit=xprinit+(n-s1)*xst;
    xpiinit=xpiinit+(n-s1)*xst;
    yprinit=yprinit+(n-s1)*yst;
    ypiinit=ypiinit+(n-s1)*yst;
    n=s1;
}
#pragma omp parallel for
      for(i=0;i<(n-s2);i++){
        vsip_stride xstride=i*xst;
        vsip_stride ystride=i*yst;
        *(yprinit+ystride) = *(xprinit+xstride) * scale2;
        *(ypiinit+ystride) = *(xpiinit+xstride) * scale2;
      }


if(n-s2>0){
    xprinit=xprinit+(n-s2)*xst;
    xpiinit=xpiinit+(n-s2)*xst;
    yprinit=yprinit+(n-s2)*yst;
    ypiinit=ypiinit+(n-s2)*yst;
    n=s2;
}
scale1 -= 1.0;
idx=0;
#pragma omp parallel for shared(idx)
      for(i=0;i<n;i++){
  #pragma omp critical (scale1)
  {
        vsip_stride xstride=idx*xst;
        vsip_stride ystride=idx*yst;
        *(yprinit+ystride) = *(xprinit+xstride) / scale1;
        *(ypiinit+ystride) = *(xpiinit+xstride) / scale1;
        idx++;
        scale1 -= 1.0;
  }
      }
    return;
}
