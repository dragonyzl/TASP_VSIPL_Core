/* Modified RJudd March 18, 1998 */
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
/* $Id: vsip_cmherm_f.c,v 1.2 1999/12/02 18:39:23 judd Exp judd $ */
/* Modified to produce vsip_cmherm_f.c */
/* April 20, 1998 RJudd Modified 1,2 to row,col */
/* vsip_cmtrans_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cmtrans_f function definition.
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

extern void (vsip_cmcheck_valid_f)(const char*,
  const vsip_cmview_f*);
extern void (vsip_cmcheck_lengths_f)(const char*,
  int, const vsip_cmview_f*,
  int, const vsip_cmview_f*);

void (vsip_cmherm_f)(
  const vsip_cmview_f* A,
  const vsip_cmview_f* R) {	/* transpose matrix	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_f("vsip_cmherm_f", A);
    vsip_cmcheck_valid_f("vsip_cmherm_f", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cmview_f*	T = vsip_cmtransview_f(A);
    vsip_cmcheck_lengths_f("vsip_cmherm_f",
      1, T, 2, R);
    vsip_cmdestroy_f(T);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    unsigned int lx = A->row_length,
                 ly = A->col_length;
    int cAst = A->block->cstride;
    int cRst = R->block->cstride;
    vsip_scalar_f tmp;
    vsip_scalar_f *a_p_r = (vsip_scalar_f*)(A->block->R->array + cAst * A->offset),
                  *a_p_i = (vsip_scalar_f*)(A->block->I->array + cAst * A->offset),
                  *r_p_r = (vsip_scalar_f*)(R->block->R->array + cRst * R->offset),
                  *r_p_i = (vsip_scalar_f*)(R->block->I->array + cRst * R->offset);
    unsigned int i, j;
    int stAx = cAst * A->row_stride, stAy = cAst *A->col_stride;
    int stRx = cRst * R->row_stride, stRy = cRst *R->col_stride;
    if((lx == ly) && (a_p_r == r_p_r)){
      for(i=1; i<lx; i++){
        *(a_p_i + (i-1) * (stAy + stAx)) = - *(a_p_i + (i-1) * (stAx + stAy));
        for(j=0; j<i; j++){ 
           tmp = *(a_p_r + j * stAy + i * stAx);
           *(a_p_r + j * stAy + i * stAx) = *(a_p_r + j * stAx + i * stAy);
           *(a_p_r + j * stAx + i * stAy) = tmp; 
           tmp = - *(a_p_i + j * stAy + i * stAx);
           *(a_p_i + j * stAy + i * stAx) = - *(a_p_i + j * stAx + i * stAy);
           *(a_p_i + j * stAx + i * stAy) = tmp; 
        }
      }
      *(a_p_i + (i-1) * (stAy + stAx)) = - *(a_p_i + (i-1) * (stAx + stAy));
    } else {
       for(i=0; i<ly; i++){
         r_p_r = (vsip_scalar_f*)(R->block->R->array + cRst * R->offset + i * stRx);
         r_p_i = (vsip_scalar_f*)(R->block->I->array + cRst * R->offset + i * stRx);
         a_p_r = (vsip_scalar_f*)(A->block->R->array + cAst * A->offset + i * stAy);
         a_p_i = (vsip_scalar_f*)(A->block->I->array + cAst * A->offset + i * stAy);
         for(j=0; j<lx; j++){
            *r_p_r = *a_p_r;
            *r_p_i = - *a_p_i;
            r_p_r += stRy; a_p_r += stAx;
            r_p_i += stRy; a_p_i += stAx;
         }
      }
    }
  }
}
