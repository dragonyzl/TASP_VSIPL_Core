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
/* $Id: vsip_cvexpoavg_d.c,v 1.1 1999/12/05 01:45:16 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* vsip_cvexpoavg_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvexpoavg_d function definition.
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

void (vsip_cvexpoavg_d)(
  vsip_scalar_d alpha,
  const vsip_cvview_d* b,
  const vsip_cvview_d* c) {/* c_j += alpha*(b_j - c_j)	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_d("vsip_cvexpoavg_d", b);
    vsip_cvcheck_valid_d("vsip_cvexpoavg_d", c);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvcheck_lengths_d("vsip_cvexpoavg_d", 2, b, 3, c);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_cvcheck_clobber_d("vsip_cvexpoavg_d", b, c);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
      /* register */ vsip_length n = c->length;
      vsip_stride cbst = b->block->cstride,
                  ccst = c->block->cstride;
      vsip_scalar_d *bpr = (vsip_scalar_d*) ((b->block->R->array) + cbst * b->offset),
                    *cpr = (vsip_scalar_d*) ((c->block->R->array) + ccst * c->offset);
      vsip_scalar_d *bpi = (vsip_scalar_d*) ((b->block->I->array) + cbst * b->offset),
                    *cpi = (vsip_scalar_d*) ((c->block->I->array) + ccst * c->offset);
      /* register */ vsip_stride bst = (cbst * b->stride),
                                 cst = (ccst * c->stride);

    while(n-- > 0){
       *cpr = alpha * *bpr + (1 - alpha) * *cpr;
       *cpi = alpha * *bpi + (1 - alpha) * *cpi;
        bpr += bst; bpi += bst;
        cpr += cst; cpi += cst;
    }
  }
}
