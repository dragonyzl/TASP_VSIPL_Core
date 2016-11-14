/* Modified RJudd January 4, 1998 */
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
/* $Id: vsip_vrect_f.c,v 1.1 1999/12/05 16:51:02 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified January 3, 1999 */
/* to incorporate rstride */
/* vsip_vrect_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vrect_f function definition.
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

void (vsip_vrect_f)(
  const vsip_vview_f* r,
  const vsip_vview_f* t,
  const vsip_cvview_f* a) {/* a_j = r_j*(cos(t_j), sin(t_j))	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_f("vsip_vrect_f", r);
    vsip_vcheck_valid_f("vsip_vrect_f", t);
    vsip_cvcheck_valid_f("vsip_vrect_f", a);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_f*	r_a = vsip_vrealview_f(a);
    vsip_vcheck_lengths_f("vsip_vrect_f", 1, r, 3, r_a);
    vsip_vcheck_lengths_f("vsip_vrect_f", 2, t, 3, r_a);
    vsip_vdestroy_f(r_a);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_vview_f*	r_a = vsip_vrealview_f(a);
    vsip_vview_f*	i_a = vsip_vimagview_f(a);
    vsip_vcheck_clobber_f("vsip_vrect_f", r, r_a);
    vsip_vcheck_clobber_f("vsip_vrect_f", t, r_a);
    vsip_vcheck_clobber_f("vsip_vrect_f", r, i_a);
    vsip_vcheck_clobber_f("vsip_vrect_f", t, i_a);
    vsip_vdestroy_f(i_a);
    vsip_vdestroy_f(r_a);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  rrst = r->block->rstride,
                  trst = r->block->rstride;
      vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                    *rp  = (vsip_scalar_f*) ((r->block->array) + rrst * r->offset),
                    *tp  = (vsip_scalar_f*) ((t->block->array) + trst * t->offset);
      vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
      vsip_scalar_f  temp = 0;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 rst = rrst * r->stride,
                                 tst = trst * t->stride;
      while(n-- > 0){
          temp = *rp * (vsip_scalar_f)sin(*tp);
          *apr = *rp * (vsip_scalar_f)cos(*tp);
          *api = temp;
          apr += ast; api += ast; 
          rp += rst; 
          tp += tst;
      }
  }
}
