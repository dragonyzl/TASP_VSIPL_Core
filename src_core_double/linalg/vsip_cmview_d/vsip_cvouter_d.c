/* Modified RJudd March 12, 1998 */
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
/* $Id: vsip_cvouter_d.c,v 1.1 1999/12/05 16:07:50 judd Exp judd $ */
/* April 20, 1998 1,2 to row,col */
/* Modified RJudd Feb 14, 1999 */
/* to fix cmbind */
/* vsip_cvouter_d.c 
// 
// This file contains the vsip_cvouter_d function definition.
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
#include<vsip_cmviewattributes_d.h>

extern void (vsip_cvcheck_valid_d)(const char*,
  const vsip_cvview_d*);
extern void (vsip_cmcheck_valid_d)(const char*,
  const vsip_cmview_d*);
extern void (vsip_cvcheck_lengths_d)(const char*,
  int, const vsip_cvview_d*,
  int, const vsip_cvview_d*);

void (vsip_cvouter_d)(
  const vsip_cscalar_d alpha,
  const vsip_cvview_d* a,
  const vsip_cvview_d* b,
  const vsip_cmview_d* R) {	/* R_ij = a_i*b_j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_d("vsip_vouter_d", a);
    vsip_cvcheck_valid_d("vsip_vouter_d", b);
    vsip_cmcheck_valid_d("vsip_vouter_d", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvview_d*	r = vsip_cmrowview_d(R, 0);
    vsip_cvview_d*	c = vsip_cmcolview_d(R, 0);
    vsip_cvcheck_lengths_d("vsip_cvouter_d", 1, a, 3, c);
    vsip_cvcheck_lengths_d("vsip_cvouter_d", 2, b, 3, r);
    vsip_cvdestroy_d(c);
    vsip_cvdestroy_d(r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
     vsip_length  n = a->length,
                  m = b->length;
     vsip_stride cRst = R->block->cstride, cast = a->block->cstride, cbst = b->block->cstride;
     vsip_scalar_d  *a_pr = (vsip_scalar_d*)(a->block->R->array + cast * a->offset),
                    *a_pi = (vsip_scalar_d*)(a->block->I->array + cast * a->offset);
     vsip_length i,j;
     vsip_stride stR = cRst * R->row_stride,
                 sta = cast * a->stride,
                 stb = cbst * b->stride;
     vsip_offset Ro  = cRst * R->offset,
                 Rco = cRst * R->col_stride,
                 bo  = cbst * b->offset;
     for(i=0; i<n; i++){
         vsip_scalar_d *R_pr = (vsip_scalar_d*)(R->block->R->array + Ro + i * Rco),
                       *R_pi = (vsip_scalar_d*)(R->block->I->array + Ro + i * Rco),
                       *b_pr = (vsip_scalar_d*)(b->block->R->array + bo),
                       *b_pi = (vsip_scalar_d*)(b->block->I->array + bo);
         vsip_cscalar_d temp = vsip_cmul_d(alpha,vsip_cmplx_d(*a_pr,*a_pi));
         for(j=0; j<m; j++){
             *R_pr = (temp.r * *b_pr + temp.i * *b_pi);
             *R_pi = (temp.i * *b_pr - temp.r * *b_pi);
              R_pr += stR; b_pr += stb;
              R_pi += stR; b_pi += stb;
         }
         a_pr += sta;
         a_pi += sta;
     }  
  }
}

