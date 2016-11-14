/* Modified RJudd March 14, 1998 */
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
/* $Id: vsip_mvprod_d.c,v 1.1 1999/12/05 16:08:03 judd Exp judd $ */
/* Modified to vsip_mvpord_d.c */
/* April 21, 1998 1,2 to row,col */
/* vsip_vmprod_d.c 
// 
// This file contains the vsip_vmprod_d function definition.
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
#include<vsip_mviewattributes_d.h>

extern void (vsip_vcheck_valid_d)(const char*,
  const vsip_vview_d*);
extern void (vsip_mcheck_valid_d)(const char*,
  const vsip_mview_d*);
extern void (vsip_vcheck_lengths_d)(const char*,
  int, const vsip_vview_d*,
  int, const vsip_vview_d*);

void (vsip_mvprod_d)(
  const vsip_mview_d* A,
  const vsip_vview_d* b,
  const vsip_vview_d* r) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_d("vsip_mvprod_d", b);
    vsip_mcheck_valid_d("vsip_mvprod_d", A);
    vsip_vcheck_valid_d("vsip_mvprod_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_d*	r_A = vsip_mrowview_d(A, 0);
    vsip_vview_d*	c_A = vsip_mcolview_d(A, 0);
    vsip_vcheck_lengths_d("vsip_mvprod_d",
      1, b, 2, r_A);
    vsip_vcheck_lengths_d("vsip_mvprod_d",
      2, c_A, 2, r);
    vsip_vdestroy_d(c_A);
    vsip_vdestroy_d(r_A);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
     vsip_length nx = 0, mx = 0;
                  
     vsip_scalar_d  *bp = b->block->array + b->offset * b->block->rstride,
                    *rp = r->block->array + r->offset * r->block->rstride,
                   *Ayp = A->block->array + A->offset * A->block->rstride,
                   *Axp = Ayp;
     vsip_stride rst = r->stride * r->block->rstride,
                 ARst = A->row_stride * A->block->rstride,
                 ACst = A->col_stride * A->block->rstride,
                 bst = b->stride * b->block->rstride;
     while(nx++ < A->col_length){
         *rp = 0;
         mx = 0;
         while(mx++ < A->row_length){
             *rp += *bp * *Axp;
             bp += bst; Axp += ARst;
         }
         bp = b->block->array + b->offset * b->block->rstride;
         Axp = (Ayp += ACst);
         rp += rst;
     }
  }
}

