/* Modified RJudd September 26,  1997 */
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
/* $Id: vsip_veuler_d.c,v 1.1 1999/12/05 01:46:31 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* vsip_veuler_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_veuler_d function definition.
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
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>

extern void (vsip_vcheck_valid_d)(const char*, const vsip_vview_d*);
extern void (vsip_cvcheck_valid_d)(const char*, const vsip_cvview_d*);
extern void (vsip_vcheck_lengths_d)(const char*,
  int, const vsip_vview_d*, int, const vsip_vview_d*);
extern void (vsip_vcheck_clobber_d)(const char*,
  const vsip_vview_d*, const vsip_vview_d*);

void (vsip_veuler_d)(
  const vsip_vview_d* a,
  const vsip_cvview_d* r) {		/* r_j = euler(a_j)	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_d("vsip_veuler_d", a);
    vsip_cvcheck_valid_d("vsip_veuler_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_d* r_r = vsip_vrealview_d(r);
    vsip_vcheck_lengths_d("vsip_veuler_d", 1, a, 2, r_r);
    vsip_vdestroy_d(r_r);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_vview_d* r_r = vsip_vrealview_d(r);
    vsip_vview_d* i_r = vsip_vimagview_d(r);
    vsip_vcheck_clobber_d("vsip_veuler_d", a, r_r);
    vsip_vcheck_clobber_d("vsip_veuler_d", a, i_r);
    vsip_vdestroy_d(i_r);
    vsip_vdestroy_d(r_r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride crst = r->block->cstride,
                  rast = a->block->rstride;
      vsip_scalar_d *ap  = (vsip_scalar_d*) ((a->block->array) + a->offset * rast),
                    *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
      vsip_scalar_d  temp;
      /* register */ vsip_stride ast = a->stride * rast,
                                 rst = (crst * r->stride);
      while(n-- > 0){
          temp = cos(*ap);
          *rpi = sin(*ap);
          *rpr = temp;
          ap  += ast; 
          rpr += rst; rpi += rst;
      }

  }
}

