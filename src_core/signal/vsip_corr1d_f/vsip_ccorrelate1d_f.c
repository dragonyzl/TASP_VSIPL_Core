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

void vsip_ccorrelate1d_f(
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
    void VI_cvunbiassame_f(const vsip_ccorr1d_f*,
                          const vsip_cvview_f*,
                          const vsip_cvview_f*);
    void VI_cvunbiasfull_f(const vsip_ccorr1d_f*,
                          const vsip_cvview_f*,
                          const vsip_cvview_f*);
    xt->length = cor->x->length - x->length;
    vsip_cvfill_f(vsip_cmplx_f(0,0),xt);
    xt->offset = xt->length;
    xt->length = x->length;
    vsip_cvcopy_f_f(x,xt);
    xt->length = cor->x->length;
    xt->offset = 0;

    ht->length = cor->h->length - h->length;
    ht->offset = h->length; 
    vsip_cvfill_f(vsip_cmplx_f(0,0),ht);
    ht->offset = 0;
    ht->length = h->length;
    vsip_cvcopy_f_f(h,ht);

    vsip_ccfftip_f(cor->fft,cor->h);
    vsip_ccfftip_f(cor->fft,cor->x);
    
    vsip_cvjmul_f(cor->x,cor->h,cor->x);
    vsip_cvconj_f(cor->x,cor->x);
    vsip_rscvmul_f(1/(vsip_scalar_f)cor->N,cor->x,cor->x);
    vsip_ccfftip_f(cor->fft,cor->x);
    vsip_cvconj_f(cor->x,cor->x);

    switch(cor->support){
      case VSIP_SUPPORT_FULL:
        xt->offset = xt->length - cor->mn;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_cvunbiasfull_f(cor,xt,y);
        } else {
            vsip_cvcopy_f_f(xt,y);
        }
        break;
      case VSIP_SUPPORT_SAME:
        xt->offset = xt->length - cor->mn + cor->m/2;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_cvunbiassame_f(cor,xt,y);
        } else {
            vsip_cvcopy_f_f(xt,y);
        }
        break;
      case VSIP_SUPPORT_MIN:
        xt->offset = xt->length - cor->mn + cor->m - 1;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            vsip_rscvmul_f((vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,xt,y);
        } else {
            vsip_cvcopy_f_f(xt,y);
        }
        break;
    }
    return;
}

void VI_cvunbiasfull_f(
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
    while(n-- > s1){
         *ypr = *xpr / scale1;
         *ypi = *xpi / scale1;
          scale1 += 1.0;
          ypr+=yst; xpr+=xst;
          ypi+=yst; xpi+=xst;
    }
    n++;
    while(n-- > s2){
         *ypr = *xpr * scale2;
         *ypi = *xpi * scale2;
          ypr+=yst; xpr+=xst;
          ypi+=yst; xpi+=xst;
    }
    n++;
    n++;
    while(n-- > 1){
         *ypr = *xpr / (vsip_scalar_f)n;
         *ypi = *xpi / (vsip_scalar_f)n;
          ypr+=yst; xpr+=xst;
          ypi+=yst; xpi+=xst;
    }
    return;
}

void VI_cvunbiassame_f(
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
    while(n-- > s1){    
         *ypr = *xpr / scale1;
         *ypi = *xpi / scale1;
          scale1 += 1.0; 
          ypr+=yst; xpr+=xst;
          ypi+=yst; xpi+=xst;
    } 
    n++;
    while(n-- > s2){
         *ypr = *xpr * scale2;
         *ypi = *xpi * scale2;
          ypr+=yst; xpr+=xst;
          ypi+=yst; xpi+=xst;
    }
    n++;
    scale1 -= 1.0;
    while(n-- > 0){
         *ypr = *xpr / scale1;
         *ypi = *xpi / scale1;
          scale1 -= 1.0;
          ypr+=yst; xpr+=xst;
          ypi+=yst; xpi+=xst;
    }
    return;
}
