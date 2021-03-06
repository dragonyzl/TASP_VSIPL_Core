/* Modified RJudd December 27, 1997 */
/* SPAWARSYSCEN */
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
/* $Id: vsip_svsub_i.c,v 1.1 1999/12/02 19:11:03 judd Exp judd $ */
/* Modified RJudd March 20, 1998 */
/* to vsip_vsub_i.c */
/* vsip_vsub_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vsub_d function definition.
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
#include<vsip_vviewattributes_i.h>

extern void (vsip_vcheck_valid_i)(const char*,
  const vsip_vview_i*);
extern void (vsip_vcheck_lengths_i)(const char*,
  int, const vsip_vview_i*, int, const vsip_vview_i*);
extern void (vsip_vcheck_clobber_i)(const char*,
  const vsip_vview_i*, const vsip_vview_i*);
void (vsip_svsub_i)(
  vsip_scalar_i alpha,
  const vsip_vview_i *b,
  const vsip_vview_i *r) {	/* r_j = alpha - b_j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_i("vsip_svsub_i", b);
    vsip_vcheck_valid_i("vsip_svsub_i", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vcheck_lengths_i("vsip_svsub_i", 2, b, 3, r);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_vcheck_clobber_i("vsip_svsub_i", b, r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    /* register */ unsigned int n = (unsigned int) r->length;
    /* register */ int bst = (int) b->stride,
                       rst = (int) r->stride;
    vsip_scalar_i *bp = (b->block->array) + b->offset,
                  *rp = (r->block->array) + r->offset;
       bp -= bst; rp -= rst;
       while(n-- > 0)
          *(rp += rst) = alpha - *(bp += bst);
  }
}
