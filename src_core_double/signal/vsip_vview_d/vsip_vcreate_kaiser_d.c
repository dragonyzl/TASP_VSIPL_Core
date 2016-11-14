/* RJudd For Core January 10, 1998 */
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
/* $Id: vsip_vcreate_kaiser_d.c,v 1.1 1999/12/05 01:56:52 judd Exp $ */
/*
// Based on work by Hughes Research Lab
// 
// HRL copyright
// Copyright (c) Hughes Research Laboratories, Inc. 1997 
// A non-exclusive, non-royalty bearing license is hereby granted to all 
// persons to copy, modify, distribute and produce derivative works for 
// any purpose, provided that this copyright notice and following disclaimer 
// appear on all copies.  
// 
// THIS LICENSE INCLUDES NO WARRANTEES, EXPRESSED OR IMPLIED, WHETHER ORAL 
// OR WRITTEN, WITH RESPECT TO THE SOFTWARE OR OTHER MATERIAL, INCLUDING 
// BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY, OR FITNESS 
// FOR A PARTICULAR PURPOSE, OR ARISING FROM A COURSE OF PERFORMANCE, OR 
// DEALING, OR FROM USAGE OR TRADE, OR OF NON-INFRINGEMENT OF ANY PATENTS 
// OF THIRD PARTIES.
//
// This material is based upon work supported by Ft. Huachuca/DARPA under
// Contract No.  DABT63-96-C-0060.  Any opinions, findings and conclusions
// or recommendations expressed in this material are those of the author(s)
// and do not necessarily reflect the views of Ft. Huachuca/DARPA.
*/

#include<vsip.h>
#include<vsip_vviewattributes_d.h>

#define a1    2.2499997
#define a2    1.2656208
#define a3    0.3163866
#define a4    0.0444479
#define a5    0.0039444
#define a6    0.0002100
#define b1    0.39894228        /* 1/sqrt(2pi) */
#define b2    0.02805063
#define b3    0.029219405
#define b4    0.0447422145

extern void (vsip_vcheck_valid_d)(
             const char*,
             const vsip_vview_d*);
extern int  (vsip_report_error)(
             const char*, ...);

vsip_vview_d* vsip_vcreate_kaiser_d(
     vsip_length N, 
     vsip_scalar_d beta, 
     vsip_memory_hint h) {
  vsip_scalar_d VI_Io_d(vsip_scalar_d);
  vsip_vview_d *a;
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_nonconformal_view_lengths) && N < 2) {
    vsip_report_error("In function vsip_vcreate_blackman_d, "
      "length = %lu < 2.\n", (unsigned long int)N);
    exit(EXIT_FAILURE);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
    a  = vsip_vcreate_d(N,h);
    if(a == NULL) return (vsip_vview_d*)NULL;
#ifdef VSIP_DEVELOPMENT_MODE
         if (vsip_check_error(vsip_invalid_structure_object)) {
            vsip_vcheck_valid_d("vsip_vcreate_blackman_d", a);
         }
         if (vsip_check_error(vsip_nonconformal_view_lengths)) {
            vsip_length                 m = a->length;
              if (m < 2) { 
                vsip_report_error("In function vsip_vcreate_blackman_d, "
                  "length = %lu < 2.\n", (unsigned long int)m);
                exit(EXIT_FAILURE);
              }
         }  
#endif /* VSIP_DEVELOPMENT_MODE */
    {
      vsip_length n =  0;
      vsip_scalar_d *ap  = (a->block->array) + a->offset,
                    Ibeta,
                    x = beta,
                    c1 = 2.0 / (N -1 );
      if((vsip_scalar_d)fabs(x) <= 3.0){
         x /= 3.0;   
         x *= x; 
         Ibeta = 1 + x * (a1 + x * (a2 + x * (a3 + x * (a4 + x * (a5 + x * a6)))));
      } else {
         Ibeta = VI_Io_d(x);
      }
      /* Note this is always unit stride */
      while(n < N){
         vsip_scalar_d c3 = c1 * n - 1;
         if(c3 > 1.0) c3 = 1.0;
         x = beta * (vsip_scalar_d)sqrt(1 - (c3 * c3));
         if((vsip_scalar_d)fabs(x) <= 3.0){
            x /= 3.0;   
            x *= x; 
            *ap++ = (1 + x * (a1 + x * (a2 + x * (a3 + x * (a4 + x * (a5 + x * a6)))))) / Ibeta;
         } else {
            *ap++ = VI_Io_d(x)/ Ibeta;
         }
          n++;
      }
    }
    return a;
}

vsip_scalar_d VI_Io_d(vsip_scalar_d x)
{
   vsip_length n;
   vsip_scalar_d ans,x0,x1,n0,diff;
   diff = 1;
   x1 = x * x * .25;
   x0 = x1;
   ans = 1 + x1;
   n = 1;
   n0 = 1;
   while(diff > .00000001){
      n++;
      n0 *= (vsip_scalar_d) n;
      x1 *= x0;
      diff = x1/(n0 * n0);
      ans += diff;
   }
   return (vsip_scalar_d) ans;
}
