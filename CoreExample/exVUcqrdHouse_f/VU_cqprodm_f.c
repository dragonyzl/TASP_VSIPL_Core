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
/* $Id$ */

/* Created RJudd July 22, 1999 */
/* SPAWARSYCCEN D881 */
/* Q * A */

#include <vsip.h>
void VU_rscjvmprod_f(vsip_scalar_f, vsip_cvview_f*, vsip_cmview_f*, vsip_cvview_f*);
void VU_copu_f(vsip_cmview_f*, vsip_cvview_f*, vsip_cvview_f*);         

void VU_cqprodm_f(
     vsip_cmview_f *C,
     vsip_cmview_f *H,
     vsip_scalar_f *beta)
{
     vsip_cmattr_f attr_C,attr_C0;
     vsip_cmattr_f attr_H0;
     vsip_cvattr_f attr_h,attr_v0;
     vsip_cvview_f *h = vsip_cmcolview_f(H,0);
     vsip_length m,n;
     vsip_length j;
     vsip_stride k;
     vsip_cvview_f *v, *w;
     vsip_cmgetattrib_f(C,&attr_C);
     vsip_cvgetattrib_f(h,&attr_h);
     vsip_cmgetattrib_f(H,&attr_H0);
     attr_C0 = attr_C;
     m = attr_C.col_length;
     n = attr_C.row_length;
     v = vsip_cvcreate_f(m,0);
     vsip_cvgetattrib_f(v,&attr_v0);
     w = vsip_cvcreate_f(n,0);
     vsip_cvfill_f(vsip_cmplx_f(0,0),v);
     for(k= attr_H0.row_length - 1; k >= 0; k--){
         j = (vsip_length)k;
         attr_h.offset = j * attr_H0.row_stride +
                         j * attr_H0.col_stride + attr_H0.offset;
         attr_h.length = attr_H0.col_length -j;
         vsip_cvputlength_f(v,attr_h.length);
         vsip_cvputoffset_f(v,m - attr_h.length);
         vsip_cvputattrib_f(h,&attr_h);
         vsip_cvcopy_f_f(h,v);
         vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
         vsip_cvputattrib_f(v,&attr_v0);
         VU_rscjvmprod_f(-beta[j],v,C,w);
         VU_copu_f(C,v,w);
     }
     vsip_cmputattrib_f(C,&attr_C0);
     vsip_cvdestroy_f(h);
     vsip_cvalldestroy_f(v);
     vsip_cvalldestroy_f(w);
     return;
}

    
