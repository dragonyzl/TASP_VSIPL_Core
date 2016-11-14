/* RJudd 22 February, 98 */
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
/* $Id: vsip_vcreate_cheby_f.c,v 1.1 1999/12/02 18:58:18 judd Exp $ */
/* Converted matlab code to VSIP */
/* Modifed March 8, 98 */
/* DAVID'S Matlab Code for cheby */
/*
//  function window = chebyw(nf, ripple)
//  % nf - window length
//  % ripple - stopband attenuation in dB
//  dp = 10.^(-ripple/20);
//  odd = rem(nf,2);
//  n2 = fix(nf/2);
//  df = acos(1/cosh(acosh((1+dp)/dp)/(nf-1)))/pi;
//  x0 = (3-cos(2*pi*df))/(1.+cos(2*pi*df));
//  alpha = (x0 + 1)/2;
//  beta = (x0 - 1)/2;
//  k = (0:nf-1);
//  f = k/nf;
//  x = alpha*cos(2*pi*f) + beta;
//  tmp = (abs(x) > 1);
//  j = sqrt(-1);
//  wf = dp*(tmp.*(cosh(((nf-1)/2).*acosh(x)))+(1-tmp).*cos(((nf-1)/2).*acos(x)));
//  if (~odd)
//     wf = real(wf).*exp(-j*pi*f);
//     wf(n2+1:nf) = -wf(n2+1:nf);
//  else
//     wf = wf +j*zeros(1,nf);
//  end
//  wt = fft(wf);
//  wt = wt(1:nf)/wt(1);
//  window = real([wt(n2+2:nf) wt(1:n2+1)]');
//  %size(window)
//  %plot(window,1,4*nf)
//  %plot(window)
*/

#include<math.h>
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<VI_functions_f.h>
#define cheby_PI ((vsip_scalar_f)3.1415926535897932384626433832795)
#define TWOPI    ((vsip_scalar_f)6.283185307179586)

vsip_vview_f* (vsip_vcreate_cheby_f)(
                        vsip_length nf, 
                        vsip_scalar_f ripple,
                        vsip_memory_hint hint) {
    vsip_vview_f *window = vsip_vcreate_f(nf,hint);
    int odd = 0;
    vsip_length n2 = 0;
    vsip_scalar_f dp     = 0.0,
                  df     = 0.0,
                  x0     = 0.0, 
                  alpha  = 0.0, 
                  beta   = 0.0;
    vsip_cvview_f *wf    = vsip_cvcreate_f(nf,VSIP_MEM_NONE),
                  *Cfoo  = vsip_cvcreate_f(nf,VSIP_MEM_NONE);
    vsip_vview_f *f      = vsip_vcreate_f(nf,VSIP_MEM_NONE),
                 *x      = vsip_vcreate_f(nf,VSIP_MEM_NONE), 
                 *tmp    = vsip_vcreate_f(nf,VSIP_MEM_NONE),
                 *wfR    = vsip_vrealview_f(wf),
                 *Refoo  = vsip_vrealview_f(Cfoo),
                 *nottmp = vsip_vcreate_f(nf,VSIP_MEM_NONE);

    /* check for malloc errors, destroy everything and return null on failure */
    if((wf == NULL) | (Cfoo == NULL) | (f == NULL) | (x == NULL) | 
       (tmp == NULL) | (wfR == NULL) | (Refoo == NULL) | 
       (window == NULL) | (nottmp == NULL)){
            vsip_valldestroy_f(x);
            vsip_valldestroy_f(f);
            vsip_valldestroy_f(tmp);
            vsip_vdestroy_f(wfR);
            vsip_vdestroy_f(Refoo);
            vsip_cvalldestroy_f(wf);
            vsip_cvalldestroy_f(Cfoo);
            vsip_valldestroy_f(nottmp);
            vsip_valldestroy_f(window);
            return (vsip_vview_f*)NULL;
    }
    vsip_cvfill_f(vsip_cmplx_f(0.0,0.0),wf);
    dp    = (vsip_scalar_f)pow(10.,(-ripple/20.0)); /*dp = 10.^(-ripple/20);*/
    odd   = ((int)nf) % 2;  /*odd = rem(nf,2);*/
    n2    = (vsip_length)floor((vsip_scalar_f)nf/2.0); /*n2 = fix(nf/2);*/
            /*df = acos(1/cosh(acosh((1+dp)/dp)/(nf-1)))/pi;*/
    df    = (vsip_scalar_f)acos(1.0/cosh(VI_acosh_f(((vsip_scalar_f)1.0 + dp)/dp) / ((vsip_scalar_f)nf - 1.0)))/cheby_PI;
            /*x0 = (3-cos(2*pi*df))/(1.+cos(2*pi*df));*/
    x0    = (vsip_scalar_f)((3. - cos(TWOPI * df))/(1. + cos(TWOPI * df)));
    alpha = (x0 + (vsip_scalar_f)1.0) / (vsip_scalar_f)2.; /*alpha = (x0 + 1)/2;*/
    beta  = (x0 - (vsip_scalar_f)1.0) / (vsip_scalar_f)2.; /*beta = (x0 - 1)/2;*/
    vsip_vramp_f((vsip_scalar_f)0.0,(vsip_scalar_f)1.0/((vsip_scalar_f)nf),f); /*k = (0:nf-1);f = k/nf;*/
    /* x = alpha*cos(2*pi*f) + beta; */
    {
      register unsigned int n = (unsigned int) nf;
      vsip_scalar_f *f_p = f->block->array + f->offset,
                    *x_p = x->block->array + x->offset;
      while(n-- > 0){
        *x_p = alpha * (vsip_scalar_f)cos(TWOPI * *f_p) + beta;
         x_p += x->stride; f_p += f->stride; 
      }
    } 
    /* END x = alpha*cos(2*pi*f) + beta; */

    /*tmp = (mag(x) > 1); */
    {
      register unsigned int n = (unsigned int) nf;
      vsip_scalar_f *x_p   = x->block->array   + x->offset,
                    *tmp_p = tmp->block->array + tmp->offset;
      while(n-- > 0){
        *tmp_p = (vsip_scalar_f)((((*x_p >= 0) ? *x_p : - *x_p) > 1) ? 1.0 : 0.0);
         x_p += x->stride; tmp_p += tmp->stride;
      }
    }
    /* END tmp = (mag(x) > 1); */

    /* wf = dp*(tmp.*(cosh((((vsip_scalar_f)nf-1.0)/2).*acosh(x)))+
                (1-tmp).*cos((((vsip_scalar_f)nf-1.0)/2).*acos(x)));*/
    { 
      vsip_svsub_f(1.0,tmp,nottmp);
      vsip_vclip_f(x,-1.0,1.0,-1.0,1.0,wfR); /* modified to handle x out side of range of acos*/
      /* ensures that for x > 1 default return value of acos is zero */
      vsip_vacos_f(wfR,Refoo);
      vsip_svmul_f(((vsip_scalar_f)nf-(vsip_scalar_f)1.0)/(vsip_scalar_f)2.0,Refoo,Refoo);
      vsip_vcos_f(Refoo,Refoo);
      vsip_vmul_f(nottmp,Refoo,wfR);
  
      VI_rcvacosh_f(x,Cfoo);

      vsip_rscvmul_f(((vsip_scalar_f)nf - (vsip_scalar_f)1.0)/(vsip_scalar_f)2.0,Cfoo,Cfoo);
      VI_cvcosh_f(Cfoo,Cfoo);
      vsip_rcvmul_f(tmp,Cfoo,Cfoo); 
      vsip_cvadd_f(Cfoo,wf,wf);
      vsip_rscvmul_f(dp,wf,wf);
    }
    /* END wf = dp*(tmp.*(cosh(((nf-1)/2).*acosh(x)))+
                (1-tmp).*cos(((nf-1)/2).*acos(x)));*/

    if(!odd ){ /* if (~odd) */
      /*wf = real(wf).*exp(-j*pi*f);*/ 
      { 
        vsip_svmul_f((vsip_scalar_f)(-cheby_PI),f,f); 
        vsip_veuler_f(f,Cfoo);
        vsip_rcvmul_f(wfR,Cfoo,wf);
      }
      /*END wf = real(wf).*exp(-j*pi*f);*/

      /*wf(n2+1:nf) = -wf(n2+1:nf);*/
      { 
        vsip_length n = n2;
        vsip_scalar_f *wf_p = (vsip_scalar_f*)(wf->block->R->array + n + n); 
        while(n-- > 0){ *wf_p++ = - *wf_p; *wf_p++ = - *wf_p;}
      }
      /*END wf(n2+1:nf) = -wf(n2+1:nf);*/
    }/* END if (~odd) */

    {/* wt = fft(wf); */
      vsip_fft_f* fftplan = vsip_ccfftip_create_f(nf,(vsip_scalar_f)(1.0/(vsip_scalar_f)nf),-1,0,0);
      vsip_ccfftip_f(fftplan,wf);
      {/* wt = wt(1:nf)/wt(1) */
        vsip_cscalar_f scale = vsip_crecip_f(vsip_cvget_f(wf,0));
        vsip_csvmul_f(scale,wf,wf);
      }            
      vsip_fft_destroy_f((void*)fftplan);
    }/*END wt = fft(wf); */

    vsip_vcopy_f_f(wfR, window);
    VI_vfreqswap_f(window);
    vsip_valldestroy_f(x);
    vsip_valldestroy_f(f);
    vsip_valldestroy_f(tmp);
    vsip_valldestroy_f(nottmp);
    vsip_vdestroy_f(wfR);
    vsip_vdestroy_f(Refoo);
    vsip_cvalldestroy_f(wf);
    vsip_cvalldestroy_f(Cfoo);
    return window;
}


/*  VSIP internal functions below */
/******************************************************************/
vsip_scalar_f VI_acosh_f(vsip_scalar_f x){ /*scalar acosh*/
     if(x <= 1.0) return 0.0;
     return (vsip_scalar_f) log(x - sqrt(x * x - 1.0));
}

/******************************************************************/
void VI_rcvacosh_f(vsip_vview_f *x, vsip_cvview_f *r){
     void VI_cvlog_f(vsip_cvview_f*,vsip_cvview_f*);
     {
         register unsigned int n = (unsigned int) r->length;
         vsip_scalar_f *x_p = x->block->array,
                       *rp_r = (vsip_scalar_f*)(r->block->R->array),
                       *rp_i = rp_r + 1;
            
         while(n-- > 0){
                    *rp_r = *x_p * *x_p - (vsip_scalar_f)1.0;
                    *rp_i = (vsip_scalar_f)0;
                     rp_r += 2; rp_i += 2; x_p++;
         }
      }
     vsip_cvsqrt_f(r,r);
     vsip_rcvadd_f(x,r,r);
     VI_cvlog_f(r,r);  
     return;
}
               
/*******************************************************************/     
void VI_cvcosh_f(vsip_cvview_f *x, vsip_cvview_f *r){
     vsip_length n = r->length;
     vsip_scalar_f *x_pr = (vsip_scalar_f*)(x->block->R->array + 2 * x->offset),
                   *x_pi,
                   *r_pr = (vsip_scalar_f*)(r->block->R->array + 2 * r->offset),
                   *r_pi,
                    tmp, mag, maginv;
     vsip_stride stx = 2 * x->stride,
                 str = 2 * r->stride;
     x_pi = x_pr + 1; r_pi = r_pr + 1;
     while(n-- > 0){
        mag    =  (vsip_scalar_f)0.50 * (vsip_scalar_f)exp(*x_pr); 
        maginv =  (vsip_scalar_f)0.25 / mag;
        tmp    = (mag + maginv) * (vsip_scalar_f)cos(*x_pi); 
        *r_pi  = (mag - maginv) * (vsip_scalar_f)sin(*x_pi);
        *r_pr  = tmp;
        x_pr += stx; r_pr += str;
        x_pi += stx; r_pi += str;
     }
}

/*******************************************************************/     

void VI_cvlog_f(vsip_cvview_f *a,vsip_cvview_f *r)
{ 
     /* register */ vsip_length n = r->length;
     vsip_stride cast = a->block->cstride;
     vsip_stride crst = r->block->cstride;
     vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                   *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
     vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                   *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
     /* register */ vsip_stride ast = (cast * a->stride),
                                rst = (crst * r->stride);
     vsip_scalar_f arg = 0;
     while(n-- > 0){
         arg  = (vsip_scalar_f)atan2(*api , *apr);
         *rpr = (vsip_scalar_f)log(sqrt(*apr * *apr + *api * *api));
         *rpi = arg;
        apr += ast; api += ast;
        rpr += rst; rpi += rst;
    }
}

/*******************************************************************/     

void VI_vfreqswap_f(vsip_vview_f *a)
{ 
   vsip_length n;
   vsip_length n2 = (a->length / 2);
   vsip_scalar_f *a_p = a->block->array + a->offset * a->block->rstride,
                 *t_p,
                 tmp;
   vsip_stride ast = a->stride * a->block->rstride;
   if(a->length % 2){
      t_p = a_p + n2 + 1;
      tmp = *(t_p - 1);
      *(t_p - 1) = *a_p;
      n = n2 - 1;
      while(n-- > 0){
         *a_p = *t_p;
          a_p += a->stride;
         *t_p = *a_p;
          t_p += a->stride;
      }
      *a_p = *t_p;
      *t_p = tmp;
   } else {
      n = n2;
      t_p = a_p + n2 ;
      while(n-- > 0){
        tmp = *t_p;
        *t_p = *a_p;
        *a_p =  tmp;
         a_p += ast; t_p += ast;
      }
   }
}

