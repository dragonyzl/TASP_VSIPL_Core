/* Modified RJudd January 3, 1998 */
/* SPAWARSYSCEN */
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
/* $Id: vsip_vscatter_i.c,v 1.1 1999/12/02 19:11:09 judd Exp judd $ */
/* Modified RJudd March 22, 1998 */
/* to vsip_vscatter_i.c */
/* vsip_vscatter_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vscatter_d function definition.
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
#include<vsip_vviewattributes_i.h>
#include<vsip_vviewattributes_vi.h>

extern void (vsip_vcheck_valid_vi)(const char*, const vsip_vview_vi*);
extern void (vsip_vcheck_valid_i)(const char*,
  const vsip_vview_i*);
extern int (vsip_report_error)(const char*, ...);

void (vsip_vscatter_i)(
  const vsip_vview_i* a,
  const vsip_vview_i* r,
  const vsip_vview_vi* x) {			/* r[x_j] = a_j		*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_vi("vsip_vscatter_i", x);
    vsip_vcheck_valid_i("vsip_vscatter_i", a);
    vsip_vcheck_valid_i("vsip_vscatter_i", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_length	n = vsip_vgetlength_i(a);
    if (vsip_vgetlength_vi(x) != n) {
      vsip_report_error("In function vsip_vscatter_i,\n"
	"index array length = %lu != %lu = source operand length.\n",
	(unsigned long int)vsip_vgetlength_vi(x),
	(unsigned long int)n);
      exit(EXIT_FAILURE);
      }
    }
  if (vsip_check_error(vsip_view_index_exceeds_length)) {
    vsip_length	n = vsip_vgetlength_i(r);
    {
         /* register */ unsigned int n_x  = (unsigned int) x->length ;
         /* register */ int xst = x->stride;
         vsip_scalar_vi *xp = (x->block->array) + x->offset,
                         max;
         max  = *xp;
         while(n_x-- > 0){
                if( max < *xp) max = *xp;
                xp += xst;
         }
       if (max >= n) {
        vsip_report_error("In function vsip_vscatter_i,\n"
	"maximum array index = %lu >= %lu = destination operand length.\n",
	(unsigned long int)max, /* vsip_vmaxval_vi(x, &j) */
	(unsigned long int)n);
      exit(EXIT_FAILURE);
      }
    }
  }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    /* register */ unsigned int n = (unsigned int) x->length;
    /* register */ int ast = (int) a->stride,
                       rst = (int) r->stride,
                       xst = (int) x->stride;
    vsip_scalar_i  *ap = (a->block->array) + a->offset,
                   *rp = (r->block->array) + r->offset; 
    vsip_scalar_vi *xp = (x->block->array) + x->offset;
    while(n-- >0){
       *(rp + *xp * rst) = *ap;
        ap += ast; xp += xst;
    }
  }
}

