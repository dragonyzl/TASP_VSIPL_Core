/* Modified RJudd December 31, 1997 */
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
/* $Id: vsip_cvsam_d.c,v 1.1 1999/12/05 01:45:26 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* vsip_cvsam_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvsam_d function definition.
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
#include<vsip_cvviewattributes_d.h>

extern void (vsip_cvcheck_valid_d)(const char*,
  const vsip_cvview_d*);
extern void (vsip_cvcheck_lengths_d)(const char*,
  int, const vsip_cvview_d*,
  int, const vsip_cvview_d*);
extern void (vsip_cvcheck_clobber_d)(const char*,
  const vsip_cvview_d*, const vsip_cvview_d*);

void (vsip_cvsam_d)(
  const vsip_cvview_d* a,
  vsip_cscalar_d beta,
  const vsip_cvview_d* c,
  const vsip_cvview_d* r) {/* r_j = (a_j + beta)*c_j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_d("vsip_cvsam_d", a);
    vsip_cvcheck_valid_d("vsip_cvsam_d", c);
    vsip_cvcheck_valid_d("vsip_cvsam_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvcheck_lengths_d("vsip_cvsam_d", 1, a, 4, r);
    vsip_cvcheck_lengths_d("vsip_cvsam_d", 3, c, 4, r);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_cvcheck_clobber_d("vsip_cvsam_d", a, r);
    vsip_cvcheck_clobber_d("vsip_cvsam_d", c, r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  ccst = c->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                    *cpr = (vsip_scalar_d *)((c->block->R->array) + ccst * c->offset),
                    *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                    *cpi = (vsip_scalar_d *)((c->block->I->array) + ccst * c->offset),
                    *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_d  temp;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 cst = (ccst * c->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
        temp = (*apr + beta.r) * *cpr - (*api + beta.i) * *cpi;
        *rpi = (*apr + beta.r) * *cpi + (*api + beta.i) * *cpr;
        *rpr = temp;
        apr += ast; api += ast;
        cpr += cst; cpi += cst;
        rpr += rst; rpi += rst;
      }  
  }
}

