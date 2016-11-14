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
/* $Id: vsip_vcreate_kaiser_f.c,v 1.1 1999/12/02 18:58:19 judd Exp $ */
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
#include<vsip_vviewattributes_f.h>

#define a1    ((vsip_scalar_f)2.2499997)
#define a2    ((vsip_scalar_f)1.2656208)
#define a3    ((vsip_scalar_f)0.3163866)
#define a4    ((vsip_scalar_f)0.0444479)
#define a5    ((vsip_scalar_f)0.0039444)
#define a6    ((vsip_scalar_f)0.0002100)
#define b1    ((vsip_scalar_f)0.39894228)        /* 1/sqrt(2pi) */
#define b2    ((vsip_scalar_f)0.02805063)
#define b3    ((vsip_scalar_f)0.029219405)
#define b4    ((vsip_scalar_f)0.0447422145)

extern void (vsip_vcheck_valid_f)(
             const char*,
             const vsip_vview_f*);
extern int  (vsip_report_error)(
             const char*, ...);

vsip_vview_f* vsip_vcreate_kaiser_f(
     vsip_length N, 
     vsip_scalar_f beta, 
     vsip_memory_hint h) {
  vsip_scalar_f VI_Io_f(vsip_scalar_f);
  vsip_vview_f *a;
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_nonconformal_view_lengths) && N < 2) {
    vsip_report_error("In function vsip_vcreate_blackman_f, "
      "length = %lu < 2.\n", (unsigned long int)N);
    exit(EXIT_FAILURE);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
    a  = vsip_vcreate_f(N,h);
    if(a == NULL) return (vsip_vview_f*)NULL;
#ifdef VSIP_DEVELOPMENT_MODE
         if (vsip_check_error(vsip_invalid_structure_object)) {
            vsip_vcheck_valid_f("vsip_vcreate_blackman_f", a);
         }
         if (vsip_check_error(vsip_nonconformal_view_lengths)) {
            vsip_length                 m = a->length;
              if (m < 2) { 
                vsip_report_error("In function vsip_vcreate_blackman_f, "
                  "length = %lu < 2.\n", (unsigned long int)m);
                exit(EXIT_FAILURE);
              }
         }  
#endif /* VSIP_DEVELOPMENT_MODE */
    {
      vsip_length n =  0;
      vsip_scalar_f *ap  = (a->block->array) + a->offset,
                    Ibeta,
                    x = beta,
                    c1 = (vsip_scalar_f)2.0 / (N -1 );
      if((vsip_scalar_f)fabs(x) <= 3.0){
         x /= 3.0;   
         x *= x; 
         Ibeta = (vsip_scalar_f)1 + x * (a1 + x * (a2 + x * (a3 + x * (a4 + x * (a5 + x * a6)))));
      } else {
         Ibeta = VI_Io_f(x);
      }
      /* Note this is always unit stride */
      while(n < N){
         vsip_scalar_f c3 = c1 * n - 1;
         if(c3 > 1.0) c3 = 1.0;
         x = beta * (vsip_scalar_f)sqrt(1 - (c3 * c3));
         if((vsip_scalar_f)fabs(x) <= 3.0){
            x /= 3.0;   
            x *= x; 
            *ap++ = ((vsip_scalar_f)1 + x * (a1 + x * (a2 + x * (a3 + x * (a4 + x * (a5 + x * a6)))))) / Ibeta;
         } else {
            *ap++ = VI_Io_f(x)/ Ibeta;
         }
          n++;
      }
    }
    return a;
}

vsip_scalar_f VI_Io_f(vsip_scalar_f x)
{
   vsip_length n;
   vsip_scalar_f ans,x0,x1,n0,diff;
   diff = 1;
   x1 = x * x * (vsip_scalar_f).25;
   x0 = x1;
   ans = 1 + x1;
   n = 1;
   n0 = 1;
   while(diff > .00000001){
      n++;
      n0 *= (vsip_scalar_f)n;
      x1 *= x0;
      diff = x1/(n0 * n0);
      ans += diff;
   }
   return ans;
}
