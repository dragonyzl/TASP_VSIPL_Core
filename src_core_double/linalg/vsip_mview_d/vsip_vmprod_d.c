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
/* $Id: vsip_vmprod_d.c,v 1.1 1999/12/05 16:08:04 judd Exp judd $ */
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

void (vsip_vmprod_d)(
  const vsip_vview_d* a,
  const vsip_mview_d* B,
  const vsip_vview_d* r) {
		/* r_j = a_0*B_0j + a_1*B_1j + ... + a_n-1*B_n-1,j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_d("vsip_vmprod_d", a);
    vsip_mcheck_valid_d("vsip_vmprod_d", B);
    vsip_vcheck_valid_d("vsip_vmprod_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_d*	r_B = vsip_mrowview_d(B, 0);
    vsip_vview_d*	c_B = vsip_mcolview_d(B, 0);
    vsip_vcheck_lengths_d("vsip_vmprod_d",
      1, a, 2, c_B);
    vsip_vcheck_lengths_d("vsip_vmprod_d",
      2, r_B, 2, r);
    vsip_vdestroy_d(c_B);
    vsip_vdestroy_d(r_B);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
     vsip_length nx = 0, mx = 0;
     vsip_scalar_d  *ap = a->block->array + a->offset * a->block->rstride,
                    *ap0 = ap,
                    *rp = r->block->array + r->offset * a->block->rstride,
                   *Byp = B->block->array + B->offset * a->block->rstride,
                   *Bxp = Byp;
     vsip_stride BCst = B->col_stride * B->block->rstride,
                 BRst = B->row_stride * B->block->rstride,
                 rst  = r->stride * r->block->rstride;
     while(nx++ < B->row_length){
         *rp = 0;
         mx = 0;
         while(mx++ < B->col_length){
             *rp += *ap * *Byp;
             ap += a->stride; Byp += BCst;
         }
         ap = ap0;
         Byp = (Bxp += BRst);
         rp += rst;
     }
  }
}

