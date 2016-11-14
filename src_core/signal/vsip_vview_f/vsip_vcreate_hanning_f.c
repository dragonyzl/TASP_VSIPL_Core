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
/* $Id: vsip_vcreate_hanning_f.c,v 1.1 1999/12/02 18:58:19 judd Exp $ */
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

#define twoPI 6.2831853071796


extern void (vsip_vcheck_valid_f)(const char*,
  const vsip_vview_f*);
extern int (vsip_report_error)(const char*, ...);

vsip_vview_f* (vsip_vcreate_hanning_f)(
  vsip_length N, vsip_memory_hint h) {
  vsip_vview_f *a;
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_nonconformal_view_lengths) && N < 2) {
    vsip_report_error("In function vsip_vcreate_hanning_f, "
      "length = %lu < 2.\n", (unsigned long int)N);
    exit(EXIT_FAILURE);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
    a  = vsip_vcreate_f(N,h);
    if(a == NULL) return (vsip_vview_f*)NULL;
#ifdef VSIP_DEVELOPMENT_MODE
         if (vsip_check_error(vsip_invalid_structure_object)) {
            vsip_vcheck_valid_f("vsip_vcreate_hanning_f", a);
         }
         if (vsip_check_error(vsip_nonconformal_view_lengths)) {
            vsip_length                 m = a->length;
              if (m < 2) { 
                vsip_report_error("In function vsip_vcreate_hanning_f, "
                  "length = %lu < 2.\n", (unsigned long int)m);
                exit(EXIT_FAILURE);
              }
         }  
#endif /* VSIP_DEVELOPMENT_MODE */
    {
      /*define variables*/
      register unsigned int n =  0;
      vsip_scalar_f *ap  = (a->block->array) + a->offset,
                    temp = (vsip_scalar_f)twoPI/(N+1);
      /*end define*/
      /* Note this is always unit stride */
      while(n++ < N ){
         *ap++ = (vsip_scalar_f)0.5 * ((vsip_scalar_f)1 - (vsip_scalar_f)cos(temp * (vsip_scalar_f) n));
      }
    }
    return a;
}
