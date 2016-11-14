/* Modify RJudd March 12, 1998 */
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
/* $Id: vsip_vouter_d.c,v 1.1 1999/12/05 16:08:04 judd Exp judd $ */
/* April 21, 1998 1,2 to row,col */
/* Modified RJudd Feb 14, 1999 */
/* to fix cmbind */
/* vsip_vouter_d.c 
// 
// This file contains the vsip_vouter_d function definition.
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
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>

extern void (vsip_vcheck_valid_d)(const char*,
  const vsip_vview_d*);
extern void (vsip_mcheck_valid_d)(const char*,
  const vsip_mview_d*);
extern void (vsip_vcheck_lengths_d)(const char*,
  int, const vsip_vview_d*,
  int, const vsip_vview_d*);

void (vsip_vouter_d)(
  const vsip_scalar_d alpha,
  const vsip_vview_d* a,
  const vsip_vview_d* b,
  const vsip_mview_d* R) {	/* R_ij = a_i*b_j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_d("vsip_vouter_d", a);
    vsip_vcheck_valid_d("vsip_vouter_d", b);
    vsip_mcheck_valid_d("vsip_vouter_d", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_d*	r = vsip_mrowview_d(R, 0);
    vsip_vview_d*	c = vsip_mcolview_d(R, 0);
    vsip_vcheck_lengths_d("vsip_vouter_d", 1, a, 3, c);
    vsip_vcheck_lengths_d("vsip_vouter_d", 2, b, 3, r);
    vsip_vdestroy_d(c);
    vsip_vdestroy_d(r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
     /* register */ vsip_length n = a->length,
                                m = b->length;
     vsip_scalar_d  *a_p = a->block->array + a->offset * a->block->rstride; 
     vsip_length i,j;
     vsip_stride Rrst = R->row_stride * R->block->rstride,
                 bst  = b->stride * b->block->rstride,
                 ast  = a->stride * a->block->rstride;
     vsip_offset bo  = b->offset * b->block->rstride,
                 Ro  = R->offset * R->block->rstride,
                 Rco = R->col_stride * R->block->rstride;
     for(i=0; i<n; i++){
         vsip_scalar_d *R_p = R->block->array + Ro + i * Rco,
                       *b_p = b->block->array + bo;
         vsip_scalar_d temp = *a_p * alpha;
         for(j=0; j<m; j++){
             *R_p = temp * *b_p;
              R_p += Rrst; b_p += bst;
         }
         a_p += ast;
     }
  }
  return;
}

