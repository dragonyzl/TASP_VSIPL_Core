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
/* $Id: vsip_cvmprod_d.c,v 1.1 1999/12/05 16:07:49 judd Exp judd $ */
/* April 20, 1998 1,2 to row,col */
/* vsip_cvmprod_d.c 
// 
// This file contains the vsip_cvmprod_d function definition.
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

void (vsip_cvmprod_d)(
  const vsip_cvview_d* a,
  const vsip_cmview_d* B,
  const vsip_cvview_d* r) {
		/* r_j = a_0*B_0j + a_1*B_1j + ... + a_n-1*B_n-1,j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_d("vsip_cvmprod_d", a);
    vsip_cmcheck_valid_d("vsip_cvmprod_d", B);
    vsip_cvcheck_valid_d("vsip_cvmprod_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvview_d*	r_B = vsip_cmrowview_d(B, 0);
    vsip_cvview_d*	c_B = vsip_cmcolview_d(B, 0);
    vsip_cvcheck_lengths_d("vsip_cvmprod_d",
      1, a, 2, c_B);
    vsip_cvcheck_lengths_d("vsip_cvmprod_d",
      2, r_B, 2, r);
    vsip_cvdestroy_d(c_B);
    vsip_cvdestroy_d(r_B);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
      vsip_length nx = 0, mx = 0;
      int cast = a->block->cstride, crst = r->block->cstride, cBst = B->block->cstride;
      vsip_scalar_d  *ap_r  = (vsip_scalar_d*)(a->block->R->array + cast * a->offset),
                     *ap_i  = (vsip_scalar_d*)(a->block->I->array + cast * a->offset),
                     *rp_r  = (vsip_scalar_d*)(r->block->R->array + crst * r->offset),
                     *rp_i  = (vsip_scalar_d*)(r->block->I->array + crst * r->offset),
                     *Byp_r = (vsip_scalar_d*)(B->block->R->array + cBst * B->offset),
                     *Byp_i = (vsip_scalar_d*)(B->block->I->array + cBst * B->offset),
                     *Bxpr = Byp_r,
                     *Bxpi = Byp_i;
       int sta = cast * a->stride, str = crst * r->stride, stB = cBst * B->col_stride;
       while(nx++ < B->row_length){
           *rp_r = 0; *rp_i = 0;
           mx = 0;
           while(mx++ < B->col_length){
               *rp_r += *ap_r * *Byp_r - *ap_i * *Byp_i;
               *rp_i += *ap_r * *Byp_i + *ap_i * *Byp_r;
               ap_r += sta; Byp_r += stB;
               ap_i += sta; Byp_i += stB;
           }
           ap_r = (vsip_scalar_d*)(a->block->R->array + cast * a->offset);
           ap_i = (vsip_scalar_d*)(a->block->I->array + cast * a->offset);
           Byp_r = (Bxpr += (cBst * B->row_stride));
           Byp_i = (Bxpi += (cBst * B->row_stride));
           rp_r += str; rp_i += str;
     }   
  }
}

