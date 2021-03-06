/* Modified R. Judd March 11, 1998 */
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
/* $Id: vsip_mprod_f.c,v 1.2 1999/12/02 18:43:16 judd Exp judd $ */
/* April 21, 1998 1,2 to row,col */
/* vsip_mprod_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mprod_f function definition.
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
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>

extern void (vsip_mcheck_valid_f)(const char*,
  const vsip_mview_f*);
extern void (vsip_vcheck_lengths_f)(const char*,
  int, const vsip_vview_f*,
  int, const vsip_vview_f*);

void (vsip_mprod_f)(
  const vsip_mview_f* A,
  const vsip_mview_f* B,
  const vsip_mview_f* R) {
		/* R_ij = A_i0*B_0j + A_i1*B_1j + ... + A_i,n-1*B_n-1,j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_f("vsip_mprod_f", A);
    vsip_mcheck_valid_f("vsip_mprod_f", B);
    vsip_mcheck_valid_f("vsip_mprod_f", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_f*	r_A = vsip_mrowview_f(A, 0);
    vsip_vview_f*	c_A = vsip_mcolview_f(A, 0);
    vsip_vview_f*	r_B = vsip_mrowview_f(B, 0);
    vsip_vview_f*	c_B = vsip_mcolview_f(B, 0);
    vsip_vview_f*	r_R = vsip_mrowview_f(R, 0);
    vsip_vview_f*	c_R = vsip_mcolview_f(R, 0);
    vsip_vcheck_lengths_f("vsip_mprod_f",
      1, r_A, 2, c_B);
    vsip_vcheck_lengths_f("vsip_mprod_f",
      1, c_A, 2, c_R);
    vsip_vcheck_lengths_f("vsip_mprod_f",
      1, r_B, 2, r_R);
    vsip_vdestroy_f(c_R);
    vsip_vdestroy_f(r_R);
    vsip_vdestroy_f(c_B);
    vsip_vdestroy_f(r_B);
    vsip_vdestroy_f(c_A);
    vsip_vdestroy_f(r_A);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    vsip_length M = A->col_length,
                N = B->row_length;
    vsip_length i,j;
    vsip_vview_f aa,bb,rr,*a,*b,*r;
    a = &aa; b = &bb; r = &rr;
    /*row view of A */
    a->block  = A->block;
    a->offset = A->offset;
    a->stride = A->row_stride;
    a->length = A->row_length;
    /*col view -f B */
    b->block  = B->block;
    b->offset = B->offset;
    b->stride = B->col_stride;
    b->length = B->col_length;
    /*row view of R */
    r->block  = R->block;
    r->offset = R->offset;
    r->stride = R->row_stride;
    r->length = R->row_length;
#ifdef VSIP_DEVELOPMENT_MODE
    a->markings = vsip_valid_structure_object;
    b->markings = vsip_valid_structure_object;
    r->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */
 
    {
      vsip_stride str  = r->stride * r->block->rstride;
      vsip_stride str1 = R->col_stride * R->block->rstride;
      vsip_scalar_f  *r_pr =(vsip_scalar_f*) (r->block->array + r->offset * r->block->rstride),
                     *r_pr1 = r_pr;
      for(i = 0; i < M; i++){
        r_pr = r_pr1;
        b->offset = B->offset;
        for(j =0; j < N; j++){
            *r_pr  = vsip_vdot_f(a,b);
             r_pr += str;
             b->offset += B->row_stride;
        }  
        a->offset += A->col_stride;
        r_pr1 += str1;
      }
    }
  }  
}
