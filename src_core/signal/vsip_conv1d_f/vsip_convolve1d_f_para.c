/* $Id: vsip_convolve1d_f.c,v 1.1 1999/12/02 18:45:23 judd Exp $ */
#include<vsip.h>
#include<vsip_conv1dattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<VI_functions_f.h>

void vsip_convolve1d_f_para(
       const vsip_conv1d_f *conv,
       const vsip_vview_f *x,
       const vsip_vview_f *y)
{
  if(conv->method == 0){ /*kernel >= N/2 or kernel > 1000 */
     vsip_vview_f xxt = *x;
     vsip_vview_f *xt = &xxt;
     vsip_vview_f xxr,xxi;
     vsip_vview_f *xr = VI_vrealview_f(conv->x,&xxr),
                  *xi = VI_vimagview_f(conv->x,&xxi);
     vsip_length xtn2 = x->length/2;
     xi->length = xtn2;
     if((x->length % 2) != 0) xtn2++;
     xr->length = xtn2;
     /* make sure work area starts full of zeros */
     vsip_cvfill_f(vsip_cmplx_f(0,0),conv->x);
     /* copy input vector into work area */
     xt->length = xtn2; vsip_vcopy_f_f_para(xt,xr);
     xt->offset = xtn2; xt->length = x->length - xtn2; vsip_vcopy_f_f_para(xt,xi);
     /* do the fft on the input data */
     /**************************************************/
     vsip_ccfftip_f_para(conv->fft,conv->x);
     /* multiply time filter in frequency domain */
     vsip_cvmul_f_para(conv->H,conv->x,conv->x);
     /* do invers fft using forward fft */
     vsip_cvconj_f_para(conv->x,conv->x);
     vsip_rscvmul_f_para((vsip_scalar_f)1.0/(vsip_scalar_f)conv->x->length,conv->x,conv->x);
     /**************************************************/
     vsip_ccfftip_f_para(conv->fft,conv->x);
     vsip_cvconj_f_para(conv->x,conv->x);
     /* do overlap add of real with complex */
     xr->offset = xtn2; 
     xr->length = conv->nh - 1;
     xi->offset = 0; 
     xi->length = xr->length;
     vsip_vadd_f_para(xr,xi,xi);
     /* set length and offset of real to first half without overlap */
     xr->length = xr->offset; 
     xr->offset = 0; 
     /* desample by setting stride */
     xr->stride = (vsip_stride)conv->D; 
     xi->stride = (vsip_stride)conv->D;
     if(conv->support == VSIP_SUPPORT_SAME){
        vsip_vview_f yyt = *y;
        vsip_vview_f *yt = &yyt;
        xr->offset = (conv->nh/2);
        xr->length -= xr->offset;
        {
           vsip_offset o = xr->length % xr->stride;
           /* if o is zero, xi offset is zero, otherwise is stride - o */
           xi->offset = o ? xi->stride - o : o;
           xr->length /= xr->stride;
           if(o != 0) xr->length++;
        }
        xi->length = conv->Noutput - xr->length;
        yt->length = xr->length;
        vsip_vcopy_f_f_para(xr,yt);
        yt->length = xi->length;
        yt->offset += (yt->stride * xr->length);
        vsip_vcopy_f_f_para(xi,yt);
     }
     if(conv->support == VSIP_SUPPORT_MIN){
        vsip_vview_f yyt = *y;
        vsip_vview_f *yt = &yyt;
        if(xtn2 < conv->nh) {
          xi->offset = conv->nh - xtn2 -1;
          xi->length = conv->Noutput;
          vsip_vcopy_f_f_para(xi,yt);
        } else { 
          xr->offset = conv->nh - 1;
          xr->length = (xr->length - xr->offset);
          {
             vsip_offset o = xr->length % xr->stride;
             /* if o is zero, xi offset is zero, otherwise is stride - o */
             xi->offset = o ? xi->stride - o : o;
             xr->length /= xr->stride;
             if(o != 0) xr->length++;
          }
          xi->length = conv->Noutput - xr->length;
          yt->length = xr->length;
          vsip_vcopy_f_f_para(xr,yt);
          yt->length = xi->length;
          yt->offset += (yt->stride * xr->length);
          vsip_vcopy_f_f_para(xi,yt);
        }  
     }
     if(conv->support == VSIP_SUPPORT_FULL){
       vsip_vview_f yyt = *y;
       vsip_vview_f *yt = &yyt;
       {
          vsip_offset o = xr->length % xr->stride;
          /* if o is zero, xi offset is zero, otherwise is stride - o */
          xi->offset = o ? xi->stride - o : o;
          xr->length /= xr->stride;
          if(o != 0) xr->length++;
       }
       xi->length = conv->Noutput - xr->length;
       yt->length = xr->length;
       vsip_vcopy_f_f_para(xr,yt);
       yt->length = xi->length;
       yt->offset += (yt->stride * xr->length);
       vsip_vcopy_f_f_para(xi,yt);
      }
   }else{
      vsip_cmview_f XXm = *conv->Xm,
                  *Xm  = &XXm;
     { /* make sure we start with an initialized zero matrix */
          vsip_cvview_f XXVt,
                        *XVt = VI_cmrowview_f(Xm,0,&XXVt);
          XVt->length = Xm->row_length * Xm->col_length;
          vsip_cvfill_f(vsip_cmplx_f(0,0),XVt);
     }
     { /* copy data into matrix */
       unsigned int i = 1;
       vsip_vview_f XXR,XXI,XX = *x,*XT;
       vsip_cvview_f XXC;
       vsip_cvview_f *XC = VI_cmrowview_f(Xm,0,&XXC);
       vsip_vview_f *XR = VI_vrealview_f(XC,&XXR);
       vsip_vview_f *XI = VI_vimagview_f(XC,&XXI);
       vsip_vview_f *X = &XX;
       vsip_length Xinc,XTinc;
       if(x->length > conv->Ndata){
           vsip_length L = X->length - conv->Ndata;
           X->length = conv->Ndata;
           XR->length = conv->Ndata;
           XI->length = conv->Ndata;
           Xinc = X->length * X->stride;
           XTinc = Xm->col_stride;
           XT = XR;

/*
           while(L > 0){
              vsip_vcopy_f_f_para(X,XT);
              X->offset += Xinc;
              if(i%2) { 
                   XT = XI;
                   XR->offset += XTinc;
              } else {
                   XT = XR;
                   XI->offset += XTinc;
              }
              if(L > XT->length){
                 L -= XT->length;
              } else {
                   XT->length = L;
                   X->length = L;
                   vsip_vcopy_f_f_para(X,XT);
                   L = 0;
              }
              i++;
           }
*/
/******************************BEGIN***********************************/
vsip_offset xoffset = X->offset;
vsip_offset xroffset = XR->offset;
vsip_offset xioffset = XI->offset;
unsigned int itertimes;
              if(L <= XT->length){
                  itertimes=1;
              }
              else itertimes=(unsigned int)(L / (XT->length));
              if(L % XT->length == 0) itertimes--;
              itertimes+=i;
#pragma omp parallel for
        for(i=1;i<itertimes;i++){
              vsip_vcopy_f_f_para(X,XT);
              X->offset = xoffset + i * Xinc;
              if(i%2) { 
                   XT = XI;
                   XR->offset = xroffset + ((vsip_offset)(i/2) + 1) * XTinc;
              } else {
                   XT = XR;
                   XI->offset = xioffset + (vsip_offset)(i/2) * XTinc;
              }
                
        }
            if (L > XT->length)
            {
                L = XT->length  % L;
            }
            i=itertimes;

              vsip_vcopy_f_f_para(X,XT);
              X->offset = xoffset + i * Xinc;
              if(i%2) { 
                   XT = XI;
                   XR->offset = xroffset + ((vsip_offset)(i/2) + 1) * XTinc;
              } else {
                   XT = XR;
                   XI->offset = xioffset + (vsip_offset)(i/2) * XTinc;
              }

              XT->length = L;
              X->length = L;
              vsip_vcopy_f_f_para(X,XT);
              L=0;

/********************************END*********************************/

       } else { 
           XR->length = X->length;
           vsip_vcopy_f_f_para(X,XR);
       }
     }
     { /* do forward fft and multiply the filter (freq domain kernel) */
      /**************************ccfftmip************************/
          vsip_ccfftmip_f_para(conv->fftm,Xm);
          vsip_cvmmul_f_para(conv->H,Xm,VSIP_ROW,Xm);
     }
     {  /* do inverse fft using forward fft */
          vsip_cvview_f XXVt,
                        *XVt = VI_cmrowview_f(Xm,0,&XXVt);
          XVt->length = Xm->row_length * Xm->col_length; /* flaten matrix */
          vsip_cvconj_f_para(XVt,XVt); /* conjugate */
          vsip_rscvmul_f_para((vsip_scalar_f)1.0/Xm->row_length,XVt,XVt); /* scale */
    /**************************ccfftmip************************/
          vsip_ccfftmip_f_para(conv->fftm,Xm); /* forward fftm */
          vsip_cvconj_f_para(XVt,XVt); /* conjugate */
     }
     { /* do overlap add */
          vsip_length i;
          vsip_cvview_f xxc;
          vsip_vview_f  xxr,xxi,
                        xxo,*xo=&xxo,
                        xxa,*xa=&xxa;
          vsip_cvview_f *xc = VI_cmrowview_f(Xm,0,&xxc);
          vsip_vview_f  *xr = VI_vrealview_f(xc,&xxr);
          vsip_vview_f  *xi = VI_vimagview_f(xc,&xxi);
          vsip_offset xinc = Xm->col_stride;
          vsip_length loa = conv->nh - 1;
          vsip_offset Oo  = conv->Ndata;
          xi->length = loa; xr->length = loa;
          for(i=1; i<conv->NumSection; i++){
             if(i%2) {
                   xxo = xxr; xxa = xxi;
                   xr->offset += xinc;
             }else{
                   xxo = xxi; xxa = xxr;
                   xi->offset += xinc;
             }
             xo->offset += Oo;
             vsip_vadd_f_para(xo,xa,xa);
          } 
      }
      { /* copy to output vector */
          unsigned int i = 1;
          vsip_cvview_f XXC;
          vsip_vview_f  XXR,XXI,XXT;
          vsip_cvview_f *XC = VI_cmrowview_f(Xm,0,&XXC);
          vsip_vview_f  *XR = VI_vrealview_f(XC,&XXR);
          vsip_vview_f  *XI = VI_vimagview_f(XC,&XXI);
          vsip_vview_f  *XT = &XXT;
          vsip_offset xinc = Xm->col_stride;
          vsip_length L = conv->Noutput;
          XR->stride = conv->D;
          XI->stride = conv->D;
          XR->length = conv->Ndata;
          XI->length = conv->Ndata;
          XXT = XXR;
          if(conv->support == VSIP_SUPPORT_SAME){
             vsip_vview_f yyt = *y;
             vsip_vview_f *yt = &yyt;
             XT->offset = conv->nh / 2;
             XT->length -= XT->offset;

/*
             while(L > 0){
                vsip_offset o = XT->length % XT->stride;
                XT->length /= XT->stride;
                if(o != 0){
                    o = XT->stride - o; 
                    XT->length++;
                }
                if(L > XT->length){
                      L -= XT->length;
                }else{
                      XT->length = L;
                      L = 0;
                }
                yt->length = XT->length;
                vsip_vcopy_f_f_para(XT,yt);
                yt->offset += (yt->length * yt->stride);
                if(i%2){
                    XXT = XXI;
                    XR->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }else{
                    XXT = XXR;
                    XI->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }
                i++;
             }
*/
/******************************BEGIN***********************************/

vsip_length xtlength = XT->length;
vsip_offset ytoffset = yt->offset;
vsip_offset xtoffset = XT->offset;
vsip_offset xroffset = XR->offset;
vsip_offset xioffset = XI->offset;

int idx;
#pragma omp parallel for shared(xtlength) reduction(+:xioffset,xroffset,xtoffset)
            for(idx=0;idx<1;idx++){
#pragma omp critical (xtlength)
  {
            if(L>0){
                idx = -1;
                vsip_offset o = xtlength % XT->stride;
                xtlength /= XT->stride;
                
                if(o != 0){
                    o = XT->stride - o; 
                    xtlength++;
                }
                if(L > xtlength){
#pragma opm atomic
                      L -= xtlength;
                }else{
                      xtlength = L;
                      L = 0;
                }
                yt->length = xtlength;
                XT->length = xtlength;
                XT->offset = xtoffset;
                yt->offset = ytoffset;
                vsip_vcopy_f_f_para(XT,yt);

                ytoffset += (yt->length * yt->stride);
                if(i%2){
                    XI->offset = xioffset;
                    XXT = XXI;
                    xtlength = XT->length;
                    xtoffset = XT->offset;
                    xroffset += xinc;
                    xtoffset += o;
                    xtlength -= o;
                }else{
                    XR->offset = xroffset;
                    XXT = XXR;
                    xtlength = XT->length;
                    xtoffset = XT->offset;
                    xioffset += xinc;
                    xtoffset += o;
                    xtlength -= o;
                }
                i++;
            }  
            }
  }

XT->length = xtlength;
XT->offset = xtoffset;
yt->offset = ytoffset;
XI->offset = xioffset;
XR->offset = xroffset;
/******************************END***********************************/

          }
          if(conv->support == VSIP_SUPPORT_MIN){
             vsip_vview_f yyt = *y;
             vsip_vview_f *yt = &yyt;
             XT->offset = conv->nh - 1;
             XT->length -= XT->offset;
/*
             while(L > 0){
                vsip_offset o = XT->length % XT->stride;
                XT->length /= XT->stride;
                if(o != 0){
                    o = XT->stride - o; 
                    XT->length++;
                }
                if(L > XT->length){ 
                      L -= XT->length;
                }else{ 
                      XT->length = L; 
                      L = 0; 
                } 
                yt->length = XT->length;
                vsip_vcopy_f_f_para(XT,yt);
                yt->offset += (yt->length * yt->stride);
                if(i%2){
                    XXT = XXI;
                    XR->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }else{
                    XXT = XXR;
                    XI->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }
                i++; 
             }  
*/

/*******************************BEGIN**********************************/
vsip_length xtlength = XT->length;
vsip_offset ytoffset = yt->offset;
vsip_offset xtoffset = XT->offset;
vsip_offset xroffset = XR->offset;
vsip_offset xioffset = XI->offset;

int idx;
#pragma omp parallel for shared(xtlength) reduction(+:xioffset,xroffset,xtoffset)
            for(idx=0;idx<1;idx++){
#pragma omp critical (xtlength)
  {
            if(L>0){
                idx = -1;
                vsip_offset o = xtlength % XT->stride;
                xtlength /= XT->stride;
                
                if(o != 0){
                    o = XT->stride - o; 
                    xtlength++;
                }
                if(L > xtlength){
#pragma opm atomic
                      L -= xtlength;
                }else{
                      xtlength = L;
                      L = 0;
                }
                yt->length = xtlength;
                XT->length = xtlength;
                XT->offset = xtoffset;
                yt->offset = ytoffset;
                vsip_vcopy_f_f_para(XT,yt);

                ytoffset += (yt->length * yt->stride);
                if(i%2){
                    XI->offset = xioffset;
                    XXT = XXI;
                    xtlength = XT->length;
                    xtoffset = XT->offset;
                    xroffset += xinc;
                    xtoffset += o;
                    xtlength -= o;
                }else{
                    XR->offset = xroffset;
                    XXT = XXR;
                    xtlength = XT->length;
                    xtoffset = XT->offset;
                    xioffset += xinc;
                    xtoffset += o;
                    xtlength -= o;
                }
                i++;
            }  
            }
  }

XT->length = xtlength;
XT->offset = xtoffset;
yt->offset = ytoffset;
XI->offset = xioffset;
XR->offset = xroffset;
/*******************************END**********************************/

          }
          if(conv->support == VSIP_SUPPORT_FULL){
             vsip_vview_f yyt = *y;   
             vsip_vview_f *yt = &yyt; 

/*
             while(L > 0){ 
                vsip_offset o = XT->length % XT->stride; 
                XT->length /= XT->stride;
                if(o != 0){
                    o = XT->stride - o; 
                    XT->length++;
                }
                if(L > XT->length){   
                      L -= XT->length;
                }else{  
                      XT->length = L;  
                      L = 0;  
                }  
                yt->length = XT->length; 
                vsip_vcopy_f_f_para(XT,yt); 
                yt->offset += (yt->length * yt->stride); 
                if(i%2){ 
                    XXT = XXI;   
                    XR->offset += xinc;  
                    XT->offset += o;
                    XT->length -= o;  
                }else{ 
                    XXT = XXR;   
                    XI->offset += xinc;  
                    XT->offset += o;
                    XT->length -= o;  
                } 
                i++;  
             }   
*/

/********************************BEGIN********************************/

vsip_length xtlength = XT->length;
vsip_offset ytoffset = yt->offset;
vsip_offset xtoffset = XT->offset;
vsip_offset xroffset = XR->offset;
vsip_offset xioffset = XI->offset;

int idx;
#pragma omp parallel for shared(xtlength) reduction(+:xioffset,xroffset,xtoffset)
            for(idx=0;idx<1;idx++){
#pragma omp critical (xtlength)
  {
            if(L>0){
                idx = -1;
                vsip_offset o = xtlength % XT->stride;
                xtlength /= XT->stride;
                
                if(o != 0){
                    o = XT->stride - o; 
                    xtlength++;
                }
                if(L > xtlength){
#pragma opm atomic
                      L -= xtlength;
                }else{
                      xtlength = L;
                      L = 0;
                }
                yt->length = xtlength;
                XT->length = xtlength;
                XT->offset = xtoffset;
                yt->offset = ytoffset;
                vsip_vcopy_f_f_para(XT,yt);

                ytoffset += (yt->length * yt->stride);
                if(i%2){
                    XI->offset = xioffset;
                    XXT = XXI;
                    xtlength = XT->length;
                    xtoffset = XT->offset;
                    xroffset += xinc;
                    xtoffset += o;
                    xtlength -= o;
                }else{
                    XR->offset = xroffset;
                    XXT = XXR;
                    xtlength = XT->length;
                    xtoffset = XT->offset;
                    xioffset += xinc;
                    xtoffset += o;
                    xtlength -= o;
                }
                i++;
            }  
            }
  }

XT->length = xtlength;
XT->offset = xtoffset;
yt->offset = ytoffset;
XI->offset = xioffset;
XR->offset = xroffset;
/********************************END*********************************/

          }
      }
   }
   return;
}
