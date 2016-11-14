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
/* $Id: vsip_cmvprod_f.c,v 1.2 1999/12/02 18:39:27 judd Exp judd $ */
/* Modified to vsip_cmvprod_f.c */
/* vsip_cvmprod_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvmprod_f function definition.
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
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

extern void (vsip_cvcheck_valid_f)(const char*,
  const vsip_cvview_f*);
extern void (vsip_cmcheck_valid_f)(const char*,
  const vsip_cmview_f*);
extern void (vsip_cvcheck_lengths_f)(const char*,
  int, const vsip_cvview_f*,
  int, const vsip_cvview_f*);

void (vsip_cmvprod_f)(
  const vsip_cmview_f* A,
  const vsip_cvview_f* b,
  const vsip_cvview_f* r) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_f("vsip_cmvprod_f", b);
    vsip_cmcheck_valid_f("vsip_cmvprod_f", A);
    vsip_cvcheck_valid_f("vsip_cmvprod_f", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvview_f*	r_A = vsip_cmrowview_f(A, 0);
    vsip_cvview_f*	c_A = vsip_cmcolview_f(A, 0);
    vsip_cvcheck_lengths_f("vsip_cmvprod_f",
      1, b, 2, r_A);
    vsip_cvcheck_lengths_f("vsip_cmvprod_f",
      2, c_A, 2, r);
    vsip_cvdestroy_f(c_A);
    vsip_cvdestroy_f(r_A);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
      vsip_length nx = 0, mx = 0;
      int cbst = b->block->cstride, crst = b->block->cstride, cAst = A->block->cstride;
      vsip_scalar_f  *bp_r  = (vsip_scalar_f*)(b->block->R->array + cbst * b->offset),
                     *bp_i  = (vsip_scalar_f*)(b->block->I->array + cbst * b->offset),
                     *rp_r  = (vsip_scalar_f*)(r->block->R->array + crst * r->offset),
                     *rp_i  = (vsip_scalar_f*)(r->block->I->array + crst * r->offset),
                     *Axp_r = (vsip_scalar_f*)(A->block->R->array + cAst * A->offset),
                     *Axp_i = (vsip_scalar_f*)(A->block->I->array + cAst * A->offset),
                     *Aypr = Axp_r,
                     *Aypi = Axp_i;
       int stb = cbst * b->stride, str = crst * r->stride, stA = cAst * A->row_stride;
       while(nx++ < A->col_length){
           *rp_r = 0; *rp_i = 0;
           mx = 0;
           while(mx++ < A->row_length){
               *rp_r += *bp_r * *Axp_r - *bp_i * *Axp_i;
               *rp_i += *bp_r * *Axp_i + *bp_i * *Axp_r;
               bp_r += stb; Axp_r += stA;
               bp_i += stb; Axp_i += stA;
           }
           bp_r = (vsip_scalar_f*)(b->block->R->array + cbst * b->offset);
           bp_i = (vsip_scalar_f*)(b->block->I->array + cbst * b->offset);
           Axp_r = (Aypr += (cAst * A->col_stride));
           Axp_i = (Aypi += (cAst * A->col_stride));
           rp_r += str; rp_i += str;
     }   
  }
}

