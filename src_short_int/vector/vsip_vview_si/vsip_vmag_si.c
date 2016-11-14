/* Modified RJudd October 22, 1997 */
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
/* $Id: vsip_vmag_si.c,v 1.1 1999/12/05 16:38:58 judd Exp judd $ */
/* Modified RJudd January 3, 1999 */
/* to vsip_vmag_si.c */
/*
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
#include<vsip_vviewattributes_si.h>

extern void (vsip_vcheck_valid_si)(const char*,
  const vsip_vview_si*);
extern void (vsip_vcheck_valid_si)(const char*,
  const vsip_vview_si*);
extern void (vsip_vcheck_lengths_si)(const char*,
  int, const vsip_vview_si*,
  int, const vsip_vview_si*);
extern void (vsip_vcheck_clobber_si)(const char*,
  const vsip_vview_si*, const vsip_vview_si*);

void (vsip_vmag_si)(
  const vsip_vview_si* a,
  const vsip_vview_si* r) {		/* r_j = |a_j|		*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_si("vsip_vmag_si", a);
    vsip_vcheck_valid_si("vsip_vmag_si", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vcheck_valid_si("vsip_vmag_si", r);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_vcheck_clobber_si("vsip_vmag_si", a, r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride ast = a->stride,
                               rst = r->stride;
    vsip_scalar_si *ap = (vsip_scalar_si*) ((a->block->array) + a->offset);
    vsip_scalar_si *rp = (vsip_scalar_si*) ((r->block->array) + r->offset);
    while(n-- > 0){
       *rp = (*ap < 0) ? -(*ap) : *ap;
       ap += ast; rp += rst;
    }
  }
}

