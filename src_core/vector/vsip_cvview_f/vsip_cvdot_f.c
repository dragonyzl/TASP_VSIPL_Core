/* Modified RJudd December 29, 1997 */
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
/* $Id: vsip_cvdot_f.c,v 1.1 1999/12/02 19:02:35 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* vsip_cvdot_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvdot_f function definition.
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

extern void (vsip_cvcheck_valid_f)(const char*,
  const vsip_cvview_f*);
extern void (vsip_cvcheck_lengths_f)(const char*,
  int, const vsip_cvview_f*,
  int, const vsip_cvview_f*);

vsip_cscalar_f (vsip_cvdot_f)(
  const vsip_cvview_f* a,
  const vsip_cvview_f* b) {
			/* a_0*b_0 + a_1*b_1 + ... + a_n-1*b_n-1	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cvcheck_valid_f("vsip_vdot_f", a);
    vsip_cvcheck_valid_f("vsip_vdot_f", b);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_cvcheck_lengths_f("vsip_cvdot_f", 1, a, 2, b);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
      /* register */ vsip_length n = a->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride cbst = b->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_f*) ((b->block->R->array) + cbst * b->offset);
      vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_f*) ((b->block->I->array) + cbst * b->offset);
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride);
    vsip_cscalar_f r;
    r.r = 0; r.i = 0;
    while(n-- > 0){
        r.r += (*apr * *bpr - *api * *bpi);
        r.i += (*api * *bpr + *apr * *bpi);
        apr += ast; bpr += bst;
        api += ast; bpi += bst;
    }
    return r;
  }
}
