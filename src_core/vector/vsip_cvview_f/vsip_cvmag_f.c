/* Modified RJudd December 30, 1997 */
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
/* $Id: vsip_cvmag_f.c,v 1.2 2000/02/15 21:27:40 judd Exp judd $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* vsip_cvmag_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvmag_f function definition.
//
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
//
// Author: E. Robert Tisdale
//
// Revision History:
// Feb. 28, 1997	Added copyright notice.
// Mar. 31, 1997	Modified to conform with VSIP decoder ring.	*/

#include<math.h>
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

extern void (vsip_vcheck_valid_f)(const char*,
  const vsip_vview_f*);
extern void (vsip_cvcheck_valid_f)(const char*,
  const vsip_cvview_f*);
extern void (vsip_vcheck_lengths_f)(const char*,
  int, const vsip_vview_f*,
  int, const vsip_vview_f*);
extern void (vsip_vcheck_clobber_f)(const char*,
  const vsip_vview_f*, const vsip_vview_f*);

void (vsip_cvmag_f)(
  const vsip_cvview_f* a,
  const vsip_vview_f* r) {		/* r_j = |a_j|		*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_f("vsip_cvmag_f", a);
    vsip_vcheck_valid_f("vsip_cvmag_f", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_f*	r_a = vsip_vrealview_f(a);
    vsip_vcheck_lengths_f("vsip_cvmag_f", 1, r_a, 2, r);
    vsip_vdestroy_f(r_a);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_vview_f*	r_a = vsip_vrealview_f(a);
    vsip_vview_f*	i_a = vsip_vimagview_f(a);
    vsip_vcheck_clobber_f("vsip_cvmag_f", r_a, r);
    vsip_vcheck_clobber_f("vsip_cvmag_f", i_a, r);
    vsip_vdestroy_f(i_a);
    vsip_vdestroy_f(r_a);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    /* register */ vsip_length n = r->length;
    vsip_scalar_f s,ss;
    vsip_stride cast = a->block->cstride;
    vsip_scalar_f *ap_r = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                  *rp  = (vsip_scalar_f*) ((r->block->array) + r->offset * r->block->rstride);
    vsip_scalar_f *ap_i = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
    /* register */ vsip_stride ast = (cast * a->stride),
                               rst = r->stride * r->block->rstride;
    while(n-- > 0){
       s = ((*ap_r > 0) ? *ap_r: -*ap_r) + ((*ap_i >0) ? *ap_i: -*ap_i);
       ss = s * s;
       if(ss == 0){
           *rp = 0;
       } else {
           *rp = s * (vsip_scalar_f)sqrt((*ap_r * *ap_r)/ss + (*ap_i * *ap_i)/ss);
       }
       ap_r += ast; ap_i += ast; rp += rst;
    }
  }
}
