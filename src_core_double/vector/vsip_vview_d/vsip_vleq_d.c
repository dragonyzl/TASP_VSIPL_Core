/* Modified RJudd January 1, 1998 */
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
/* $Id: vsip_vleq_d.c,v 1.1 1999/12/05 01:43:13 judd Exp judd $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* vsip_vleq_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vleq_d function definition.
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
#include<vsip_vviewattributes_bl.h>

extern void (vsip_vcheck_valid_d)(const char*,
  const vsip_vview_d*);
extern void (vsip_vcheck_valid_bl)(const char*, const vsip_vview_bl*);
extern void (vsip_vcheck_lengths_bl_d)(const char*,
  int, const vsip_vview_d*, int, const vsip_vview_bl*);
extern vsip_length (vsip_vgetlength_bl)(const vsip_vview_bl*);

void (vsip_vleq_d)(
  const vsip_vview_d* a,
  const vsip_vview_d* b,
  const vsip_vview_bl* r) {	/* r_j = a_j == b_j		*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_d("vsip_vleq_d", a);
    vsip_vcheck_valid_d("vsip_vleq_d", b);
    vsip_vcheck_valid_bl("vsip_vleq_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vcheck_lengths_bl_d("vsip_vleq_d", 1, a, 3, r);
    vsip_vcheck_lengths_bl_d("vsip_vleq_d", 2, b, 3, r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
    {
      /*define variables*/
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                         bst = b->stride * b->block->rstride,
                         rst = r->stride;
      vsip_scalar_d  *ap = (a->block->array) + a->offset * a->block->rstride,
                     *bp = (b->block->array) + b->offset * b->block->rstride;
      vsip_scalar_bl *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
           *rp = (*ap  == *bp);
            ap += ast; bp += bst; rp += rst;
      }
    }
}
