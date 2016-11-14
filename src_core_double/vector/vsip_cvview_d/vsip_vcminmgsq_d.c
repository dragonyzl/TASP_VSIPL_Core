/* Modified RJudd January 4, 1998 */
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
/* $Id: vsip_vcminmgsq_d.c,v 1.1 1999/12/05 01:46:29 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1999 */
/* to incorporate rstride */
/* vsip_vcminmgsq_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vcminmgsq_d function definition.
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
#include<vsip_cvviewattributes_d.h>

extern void (vsip_vcheck_valid_d)(const char*,
  const vsip_vview_d*);
extern void (vsip_cvcheck_valid_d)(const char*,
  const vsip_cvview_d*);
extern void (vsip_vcheck_lengths_d)(const char*,
  int, const vsip_vview_d*,
  int, const vsip_vview_d*);
extern void (vsip_vcheck_clobber_d)(const char*,
  const vsip_vview_d*, const vsip_vview_d*);

void (vsip_vcminmgsq_d)(
  const vsip_cvview_d* a,
  const vsip_cvview_d* b,
  const vsip_vview_d* r) {	/* r_j = min{|a_j|^2, |b_j|^2}	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_d("vsip_vcminmgsq_d", a);
    vsip_cvcheck_valid_d("vsip_vcminmgsq_d", b);
    vsip_vcheck_valid_d("vsip_vcminmgsq_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vview_d*	r_a = vsip_vrealview_d(a);
    vsip_vview_d*	r_b = vsip_vrealview_d(b);
    vsip_vcheck_lengths_d("vsip_vcminmgsq_d", 1, r_a, 3, r);
    vsip_vcheck_lengths_d("vsip_vcminmgsq_d", 2, r_b, 3, r);
    vsip_vdestroy_d(r_a);
    vsip_vdestroy_d(r_b);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_vview_d*	r_a = vsip_vrealview_d(a);
    vsip_vview_d*	i_a = vsip_vimagview_d(a);
    vsip_vview_d*	r_b = vsip_vrealview_d(b);
    vsip_vview_d*	i_b = vsip_vimagview_d(b);
    vsip_vcheck_clobber_d("vsip_vcminmgsq_d", r_a, r);
    vsip_vcheck_clobber_d("vsip_vcminmgsq_d", i_a, r);
    vsip_vcheck_clobber_d("vsip_vcminmgsq_d", r_b, r);
    vsip_vcheck_clobber_d("vsip_vcminmgsq_d", i_b, r);
    vsip_vdestroy_d(i_b);
    vsip_vdestroy_d(r_b);
    vsip_vdestroy_d(i_a);
    vsip_vdestroy_d(r_a);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
{
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  cbst = b->block->cstride,
                  rrst = r->block->rstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset),
                    *rp  = (vsip_scalar_d *)((r->block->array) +    rrst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset);
      vsip_scalar_d  magasq=0, magbsq=0;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride),
                                 rst =  rrst * r->stride;
      while(n-- > 0){
        magasq = *apr * *apr + *api * *api;
        magbsq = *bpr * *bpr + *bpi * *bpi;
        *rp = (magasq < magbsq) ? magasq : magbsq;
        apr += ast; api += ast;
        bpr += bst; bpi += bst; 
        rp  += rst;
      }  
   }   
}


