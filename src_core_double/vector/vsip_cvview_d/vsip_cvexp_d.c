/* Modified RJudd September 25, 1997 */
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
/* $Id: vsip_cvexp_d.c,v 1.1 1999/12/05 01:45:16 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* vsip_cvexp_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvexp_d function definition.
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
#include<vsip_cvviewattributes_d.h>

extern void (vsip_cvcheck_valid_d)(const char*,
  const vsip_cvview_d*);
extern void (vsip_cvcheck_lengths_d)(const char*,
  int, const vsip_cvview_d*, int, const vsip_cvview_d*);
extern void (vsip_cvcheck_clobber_d)(const char*,
  const vsip_cvview_d*, const vsip_cvview_d*);

void (vsip_cvexp_d)(
  const vsip_cvview_d *a,
  const vsip_cvview_d *r) {	/* v_j = exp(u_j)		*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_d("vsip_cvexp_d", a);
    vsip_cvcheck_valid_d("vsip_cvexp_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvcheck_lengths_d("vsip_cvexp_d", 1, a, 2, r);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_cvcheck_clobber_d("vsip_cvexp_d", a, r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
      /* register */ unsigned int n = (unsigned int) r->length;
      int cast = a->block->cstride;
      int crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
      /* register */ int ast = (int)(cast * a->stride),
                         rst = (int)(crst * r->stride);
      vsip_scalar_d mag  = 0;
      while(n-- > 0){
          mag  = (vsip_scalar_d)exp(*apr);
          *rpr = mag * cos(*api);
          *rpi = mag * sin(*api);
          apr += ast; api += ast; 
          rpr += rst; rpi += rst;
      }

    }
}
