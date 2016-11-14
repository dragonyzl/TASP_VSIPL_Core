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
/* $Id: vsip_mvprod_f.c,v 1.2 1999/12/02 18:43:18 judd Exp judd $ */
/* Modified to vsip_mvpord_f.c */
/* April 21, 1998 1,2 to row,col */
/* vsip_vmprod_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vmprod_f function definition.
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
#include<vsip_mviewattributes_f.h>

extern void (vsip_vcheck_valid_f)(const char*,
  const vsip_vview_f*);
extern void (vsip_mcheck_valid_f)(const char*,
  const vsip_mview_f*);
extern void (vsip_vcheck_lengths_f)(const char*,
  int, const vsip_vview_f*,
  int, const vsip_vview_f*);

void (vsip_mvprod_f)(
  const vsip_mview_f* A,
  const vsip_vview_f* b,
  const vsip_vview_f* r) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_f("vsip_mvprod_f", b);
    vsip_mcheck_valid_f("vsip_mvprod_f", A);
    vsip_vcheck_valid_f("vsip_mvprod_f", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_f*	r_A = vsip_mrowview_f(A, 0);
    vsip_vview_f*	c_A = vsip_mcolview_f(A, 0);
    vsip_vcheck_lengths_f("vsip_mvprod_f",
      1, b, 2, r_A);
    vsip_vcheck_lengths_f("vsip_mvprod_f",
      2, c_A, 2, r);
    vsip_vdestroy_f(c_A);
    vsip_vdestroy_f(r_A);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
     vsip_length nx = 0, mx = 0;
                  
     vsip_scalar_f  *bp = b->block->array + b->offset * b->block->rstride,
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

