/* Modified R. Judd March 12, 1998 */
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
/* $Id: vsip_mprodt_d.c,v 1.1 1999/12/05 16:08:02 judd Exp judd $ */
/* modified to vsip_mprodt_d.c     */
/* April 21, 1998 1,2 to row,col */
/* vsip_mprod_d.c
// 
// This file contains the vsip_mprod_d function definition.
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
#include<VI_functions_d.h>

extern void (vsip_mcheck_valid_d)(const char*,
  const vsip_mview_d*);
extern void (vsip_vcheck_lengths_d)(const char*,
  int, const vsip_vview_d*,
  int, const vsip_vview_d*);

void (vsip_mprodt_d)(
  const vsip_mview_d* A,
  const vsip_mview_d* B,
  const vsip_mview_d* R) {
		/* R_ij = A_i0*B_0j + A_i1*B_1j + ... + A_i,n-1*B_n-1,j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_d("vsip_mprodt_d", A);
    vsip_mcheck_valid_d("vsip_mprodt_d", B);
    vsip_mcheck_valid_d("vsip_mprodt_d", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_d*	r_A = vsip_mrowview_d(A, 0);
    vsip_vview_d*	c_A = vsip_mcolview_d(A, 0);
    vsip_vview_d*	r_B = vsip_mrowview_d(B, 0);
    vsip_vview_d*	c_B = vsip_mcolview_d(B, 0);
    vsip_vview_d*	r_R = vsip_mrowview_d(R, 0);
    vsip_vview_d*	c_R = vsip_mcolview_d(R, 0);
    vsip_vcheck_lengths_d("vsip_mprodt_d",
      1, r_A, 2, r_B);
    vsip_vcheck_lengths_d("vsip_mprodt_d",
      1, c_A, 2, c_R);
    vsip_vcheck_lengths_d("vsip_mprodt_d",
      1, c_B, 2, r_R);
    vsip_vdestroy_d(c_R);
    vsip_vdestroy_d(r_R);
    vsip_vdestroy_d(c_B);
    vsip_vdestroy_d(r_B);
    vsip_vdestroy_d(c_A);
    vsip_vdestroy_d(r_A);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    vsip_length M = A->col_length,
                N = B->col_length;
    vsip_length i,j;
    vsip_vview_d bb,aa,rr;
    for(i = 0; i < M; i++){
      vsip_vview_d  *a = VI_mrowview_d(A, i,&aa), 
                    *r = VI_mrowview_d(R, i,&rr);
      vsip_scalar_d *r_p = r->block->array + r->offset * r->block->rstride; 
      for(j =0; j < N; j++){
         vsip_vview_d *b = VI_mrowview_d(B,j,&bb);
         *r_p = vsip_vdot_d(a,b);
          r_p += r->stride;
      }
    }
  }
}

