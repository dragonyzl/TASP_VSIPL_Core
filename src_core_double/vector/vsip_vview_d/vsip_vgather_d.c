/* Modified RJudd January 3, 1998 */
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
/* $Id: vsip_vgather_d.c,v 1.1 1999/12/05 01:43:11 judd Exp judd $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* vsip_vgather_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vgather_d function definition.
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
#include<vsip_vviewattributes_vi.h>

extern void (vsip_vcheck_valid_vi)(const char*, const vsip_vview_vi*);
extern void (vsip_vcheck_valid_d)(const char*,
  const vsip_vview_d*);
extern int (vsip_report_error)(const char*, ...);

void (vsip_vgather_d)(
  const vsip_vview_d* a,
  const vsip_vview_vi* x,
  const vsip_vview_d* r) {	/* r_j = a[x_j]		*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_vi("vsip_vgather_d", x);
    vsip_vcheck_valid_d("vsip_vgather_d", a);
    vsip_vcheck_valid_d("vsip_vgather_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_length	n = vsip_vgetlength_d(r);
    if (vsip_vgetlength_vi(x) != n) {
      vsip_report_error("In function vsip_vgather_d,\n"
	"index array length = %lu != %lu = destination operand length.\n",
	(unsigned long int)vsip_vgetlength_vi(x),
	(unsigned long int)n);
      exit(EXIT_FAILURE);
      }
    }
  if (vsip_check_error(vsip_view_index_exceeds_length)) {
    vsip_length	n = vsip_vgetlength_d(a);
    {
       /* find maximum vi */
       vsip_length n_x = x->length;
       /* register */ int xst = x->stride;
       vsip_scalar_vi *xp = (x->block->array) + x->offset,
                       max;
       max  = *xp;
       while(n_x-- > 0){
              if( max < *xp) max = *xp;
              xp += xst;
       }  
       if (max >= n) {
         vsip_report_error("In function vsip_vgather_d,\n"
	   "maximum array index = %lu >= %lu = the source operand length.\n",
	   (unsigned long int)max,
           (unsigned long int)n);
           exit(EXIT_FAILURE);
       }
    }
  }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    /* register */ vsip_length n =  x->length;
    /* register */ vsip_stride ast = a->stride * a->block->rstride,
                       xst = x->stride,
                       rst = r->stride * r->block->rstride;
    vsip_scalar_d  *ap = (a->block->array) + a->offset * a->block->rstride,
                   *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_vi *xp = (x->block->array) + x->offset;
    while(n-- >0){
       *rp = *(ap + *xp * ast);
        rp += rst; xp += xst;
    }
  }
}
