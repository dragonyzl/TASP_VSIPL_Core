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
/* $Id: vsip_vcreate_cheby_d.c,v 1.1 1999/12/05 01:56:50 judd Exp $ */
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
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<VI_functions_d.h>
#define cheby_PI 3.1415926535897932384626433832795
#define TWOPI 6.283185307179586

vsip_vview_d* (vsip_vcreate_cheby_d)(
                        vsip_length nf, 
                        vsip_scalar_d ripple,
                        vsip_memory_hint hint) {
    vsip_vview_d *window = vsip_vcreate_d(nf,hint);
    vsip_scalar_d dp     = 0, 
                  odd    = 0, 
                  n2     = 0, 
                  df     = 0,
                  x0     = 0, 
                  alpha  = 0, 
                  beta   = 0;
    vsip_cvview_d *wf    = vsip_cvcreate_d(nf,VSIP_MEM_NONE),
                  *Cfoo  = vsip_cvcreate_d(nf,VSIP_MEM_NONE);
    vsip_vview_d *f      = vsip_vcreate_d(nf,VSIP_MEM_NONE),
                 *x      = vsip_vcreate_d(nf,VSIP_MEM_NONE), 
                 *tmp    = vsip_vcreate_d(nf,VSIP_MEM_NONE),
                 *wfR    = vsip_vrealview_d(wf),
                 *Refoo  = vsip_vrealview_d(Cfoo),
                 *nottmp = vsip_vcreate_d(nf,VSIP_MEM_NONE);

    /* check for malloc errors, destroy everything and return null on failure */
    if((wf == NULL) | (Cfoo == NULL) | (f == NULL) | (x == NULL) | 
       (tmp == NULL) | (wfR == NULL) | (Refoo == NULL) | 
       (window == NULL) | (nottmp == NULL)){
            vsip_valldestroy_d(x);
            vsip_valldestroy_d(f);
            vsip_valldestroy_d(tmp);
            vsip_vdestroy_d(wfR);
            vsip_vdestroy_d(Refoo);
            vsip_cvalldestroy_d(wf);
            vsip_cvalldestroy_d(Cfoo);
            vsip_valldestroy_d(nottmp);
            vsip_valldestroy_d(window);
            return (vsip_vview_d*)NULL;
    }
    vsip_cvfill_d(vsip_cmplx_d(0,0),wf);
    dp    = pow(10.,(-ripple/20.0)); /*dp = 10.^(-ripple/20);*/
    odd   = ((int)nf) % 2;  /*odd = rem(nf,2);*/
    n2    = floor(nf/2.0); /*n2 = fix(nf/2);*/
            /*df = acos(1/cosh(acosh((1+dp)/dp)/(nf-1)))/pi;*/
    df    = acos(1.0/cosh(VI_acosh_d((1.0 + dp)/dp) / (nf - 1.0)))/cheby_PI;
            /*x0 = (3-cos(2*pi*df))/(1.+cos(2*pi*df));*/
    x0    = (3. - cos(TWOPI * df))/(1. + cos(TWOPI * df));
    alpha = (x0 + 1.) / 2.; /*alpha = (x0 + 1)/2;*/
    beta  = (x0 - 1.) / 2.; /*beta = (x0 - 1)/2;*/

    vsip_vramp_d(0,1.0/nf,f); /*k = (0:nf-1);f = k/nf;*/
    /* x = alpha*cos(2*pi*f) + beta; */
    {
      register unsigned int n = (unsigned int) nf;
      vsip_scalar_d *f_p = f->block->array + f->offset,
                    *x_p = x->block->array + x->offset;
      while(n-- > 0){
        *x_p = alpha * cos(TWOPI * *f_p) + beta;
         x_p += x->stride; f_p += f->stride; 
      }
    } 
    /* END x = alpha*cos(2*pi*f) + beta; */

    /*tmp = (mag(x) > 1); */
    {
      register unsigned int n = (unsigned int) nf;
      vsip_scalar_d *x_p   = x->block->array   + x->offset,
                    *tmp_p = tmp->block->array + tmp->offset;
      while(n-- > 0){
        *tmp_p = (((*x_p >= 0) ? *x_p : - *x_p) > 1) ? 1.0 : 0.0;
         x_p += x->stride; tmp_p += tmp->stride;
      }
    }
    /* END tmp = (mag(x) > 1); */

    /* wf = dp*(tmp.*(cosh(((nf-1)/2).*acosh(x)))+
                (1-tmp).*cos(((nf-1)/2).*acos(x)));*/
    { 
      vsip_svsub_d(1.0,tmp,nottmp);
      vsip_vclip_d(x,-1.0,1.0,-1.0,1.0,wfR); /* modified to handle x out side of range of acos*/
      /* ensures that for x > 1 default return value of acos is zero */
      vsip_vacos_d(wfR,Refoo);
      vsip_svmul_d((nf-1.0)/2.0,Refoo,Refoo);
      vsip_vcos_d(Refoo,Refoo);
      vsip_vmul_d(nottmp,Refoo,wfR);
  
      VI_rcvacosh_d(x,Cfoo);

      vsip_rscvmul_d((nf - 1.0)/2.0,Cfoo,Cfoo);
      VI_cvcosh_d(Cfoo,Cfoo);
      vsip_rcvmul_d(tmp,Cfoo,Cfoo); 
      vsip_cvadd_d(Cfoo,wf,wf);
      vsip_rscvmul_d(dp,wf,wf);
    }
    /* END wf = dp*(tmp.*(cosh(((nf-1)/2).*acosh(x)))+
                (1-tmp).*cos(((nf-1)/2).*acos(x)));*/

    if(!odd ){ /* if (~odd) */
      /*wf = real(wf).*exp(-j*pi*f);*/ 
      { 
        vsip_svmul_d(-cheby_PI,f,f); 
        vsip_veuler_d(f,Cfoo);
        vsip_rcvmul_d(wfR,Cfoo,wf);
      }
      /*END wf = real(wf).*exp(-j*pi*f);*/

      /*wf(n2+1:nf) = -wf(n2+1:nf);*/
      { 
        unsigned int n = (unsigned int)n2;
        vsip_scalar_d *wf_p = (vsip_scalar_d*)(wf->block->R->array + n + n); 
        while(n-- > 0){ *wf_p++ = - *wf_p; *wf_p++ = - *wf_p;}
      }
      /*END wf(n2+1:nf) = -wf(n2+1:nf);*/
    }/* END if (~odd) */

    {/* wt = fft(wf); */
      vsip_fft_d* fftplan = vsip_ccfftip_create_d(nf,(vsip_scalar_d)(1.0/nf),-1,0,0);
      vsip_ccfftip_d(fftplan,wf);
      {/* wt = wt(1:nf)/wt(1) */
        vsip_cscalar_d scale = vsip_crecip_d(vsip_cvget_d(wf,0));
        vsip_csvmul_d(scale,wf,wf);
      }            
      vsip_fft_destroy_d((void*)fftplan);
    }/*END wt = fft(wf); */

    vsip_vcopy_d_d(wfR, window);
    VI_vfreqswap_d(window);
    vsip_valldestroy_d(x);
    vsip_valldestroy_d(f);
    vsip_valldestroy_d(tmp);
    vsip_valldestroy_d(nottmp);
    vsip_vdestroy_d(wfR);
    vsip_vdestroy_d(Refoo);
    vsip_cvalldestroy_d(wf);
    vsip_cvalldestroy_d(Cfoo);
    return window;
}


/*  VSIP internal functions below */
/******************************************************************/
vsip_scalar_d VI_acosh_d(vsip_scalar_d x){ /*scalar acosh*/
     return (vsip_scalar_d) log(x - sqrt(x * x - 1));
}

/******************************************************************/
void VI_rcvacosh_d(vsip_vview_d *x, vsip_cvview_d *r){
     void VI_cvlog_d(vsip_cvview_d*,vsip_cvview_d*);
     {
         register unsigned int n = (unsigned int) r->length;
         vsip_scalar_d *x_p = x->block->array,
                       *rp_r = (vsip_scalar_d*)(r->block->R->array),
                       *rp_i = rp_r + 1;
            
         while(n-- > 0){
                    *rp_r = *x_p * *x_p - 1.0;
                    *rp_i = 0;
                     rp_r += 2; rp_i += 2; x_p++;
         }
      }
     vsip_cvsqrt_d(r,r);
     vsip_rcvadd_d(x,r,r);
     VI_cvlog_d(r,r);  
     return;
}
               
/*******************************************************************/     
void VI_cvcosh_d(vsip_cvview_d *x, vsip_cvview_d *r){
     register unsigned int n = (unsigned int) r->length;
     vsip_scalar_d *x_pr = (vsip_scalar_d*)(x->block->R->array + 2 * x->offset),
                   *x_pi,
                   *r_pr = (vsip_scalar_d*)(r->block->R->array + 2 * r->offset),
                   *r_pi,
                    tmp, mag, maginv;
     int stx = 2 * x->stride,
         str = 2 * r->stride;
     x_pi = x_pr + 1; r_pi = r_pr + 1;
     while(n-- > 0){
        mag    =  0.50 * (vsip_scalar_d)exp(*x_pr); 
        maginv =  0.25 / mag;
        tmp    = (mag + maginv) * (vsip_scalar_d)cos(*x_pi); 
        *r_pi  = (mag - maginv) * (vsip_scalar_d)sin(*x_pi);
        *r_pr  = tmp;
        x_pr += stx; r_pr += str;
        x_pi += stx; r_pi += str;
     }
}

/*******************************************************************/     

void VI_cvlog_d(vsip_cvview_d *a,vsip_cvview_d *r)
{ 
     /* register */ vsip_length n = r->length;
     vsip_stride cast = a->block->cstride;
     vsip_stride crst = r->block->cstride;
     vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                   *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
     vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                   *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
     /* register */ vsip_stride ast = (cast * a->stride),
                                rst = (crst * r->stride);
     vsip_scalar_d arg = 0;
     while(n-- > 0){
         arg  = (vsip_scalar_d)atan2(*api , *apr);
         *rpr = (vsip_scalar_d)log(sqrt(*apr * *apr + *api * *api));
         *rpi = arg;
        apr += ast; api += ast;
        rpr += rst; rpi += rst;
    }
}

/*******************************************************************/     

void VI_vfreqswap_d(vsip_vview_d *a)
{ 
   vsip_length n;
   vsip_length n2 = (a->length / 2);
   vsip_scalar_d *a_p = a->block->array + a->offset * a->block->rstride,
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

