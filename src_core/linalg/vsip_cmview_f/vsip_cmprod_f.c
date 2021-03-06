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
/* $Id: vsip_cmprod_f.c,v 1.2 1999/12/02 18:39:23 judd Exp judd $ */
/* vsip_cmprod_f.c Version 0.000 February 28, 1997
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
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

extern void (vsip_cmcheck_valid_f)(const char*,
  const vsip_cmview_f*);
extern void (vsip_cvcheck_lengths_f)(const char*,
  int, const vsip_cvview_f*,
  int, const vsip_cvview_f*);

void (vsip_cmprod_f)(
  const vsip_cmview_f* A,
  const vsip_cmview_f* B,
  const vsip_cmview_f* R) {
                /* R_ij = A_i0*B_0j + A_i1*B_1j + ... + A_i,n-1*B_n-1,j */
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_f("vsip_cmprod_f", A);
    vsip_cmcheck_valid_f("vsip_cmprod_f", B);
    vsip_cmcheck_valid_f("vsip_cmprod_f", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvview_f*      r_A = vsip_cmrowview_f(A, 0);
    vsip_cvview_f*      c_A = vsip_cmcolview_f(A, 0);
    vsip_cvview_f*      r_B = vsip_cmrowview_f(B, 0);
    vsip_cvview_f*      c_B = vsip_cmcolview_f(B, 0);
    vsip_cvview_f*      r_R = vsip_cmrowview_f(R, 0);
    vsip_cvview_f*      c_R = vsip_cmcolview_f(R, 0);
    vsip_cvcheck_lengths_f("vsip_cmprod_f",
      1, r_A, 2, c_B);
    vsip_cvcheck_lengths_f("vsip_cmprod_f",
      1, c_A, 2, c_R);
    vsip_cvcheck_lengths_f("vsip_cmprod_f",
      1, r_B, 2, r_R);
    vsip_cvdestroy_f(c_R);
    vsip_cvdestroy_f(r_R);
    vsip_cvdestroy_f(c_B);
    vsip_cvdestroy_f(r_B);
    vsip_cvdestroy_f(c_A);
    vsip_cvdestroy_f(r_A);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    vsip_length M = A->col_length,
                N = B->row_length;
    int cRst = R->block->cstride;
    vsip_cscalar_f tmp;
    vsip_length i,j;
    vsip_cvview_f aa,bb,rr,*a,*b,*r;
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

    
    for(i = 0; i < M; i++){
      vsip_scalar_f  *r_pr =(vsip_scalar_f*) (r->block->R->array + cRst * r->offset); 
      vsip_scalar_f  *r_pi =(vsip_scalar_f*) (r->block->I->array + cRst * r->offset); 
      int str = cRst * r->stride;
      b->offset = B->offset;
      for(j =0; j < N; j++){
          tmp  = vsip_cvdot_f(a,b);
          *r_pr = tmp.r; *r_pi =tmp.i; 
          r_pr += str;
          r_pi += str;
         b->offset += B->row_stride;
      }
      a->offset += A->col_stride;
      r->offset += R->col_stride;
    }
  }
}

