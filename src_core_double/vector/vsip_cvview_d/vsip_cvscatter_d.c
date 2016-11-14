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
/* $Id: vsip_cvscatter_d.c,v 1.1 1999/12/05 01:45:27 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* vsip_cvscatter_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvscatter_d function definition.
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
#include<vsip_vviewattributes_vi.h>
#include<vsip_cvviewattributes_d.h>

extern void (vsip_vcheck_valid_vi)(const char*, const vsip_vview_vi*);
extern void (vsip_cvcheck_valid_d)(const char*,
  const vsip_cvview_d*);
extern int (vsip_report_error)(const char*, ...);

void (vsip_cvscatter_d)(
  const vsip_cvview_d* a,
  const vsip_cvview_d* r,
  const vsip_vview_vi* x) {			/* r[x_j] = a_j		*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_vi("vsip_cvscatter_d", x);
    vsip_cvcheck_valid_d("vsip_cvscatter_d", a);
    vsip_cvcheck_valid_d("vsip_cvscatter_d", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_length	n = vsip_cvgetlength_d(a);
    if (vsip_vgetlength_vi(x) != n) {
      vsip_report_error("In function vsip_cvscatter_d,\n"
	"index array length = %lu != %lu = source operand length.\n",
	(unsigned long int)vsip_vgetlength_vi(x),
	(unsigned long int)n);
      exit(EXIT_FAILURE);
      }
    }
  if (vsip_check_error(vsip_view_index_exceeds_length)) {
    vsip_length	n = vsip_cvgetlength_d(r);
    {
        /* register */ unsigned int n_x  = (unsigned int) x->length;
        /* register */ int xst = x->stride;
        vsip_scalar_vi *xp = (x->block->array) + x->offset,
                        max;
        max  = *xp;
        while(n_x-- > 0){
             if( max < *xp) max = *xp;
              xp += xst;
       } 
       if (max >= n) {
           vsip_report_error("In function vsip_cvscatter_d,\n"
           "maximum array index = %lu >= %lu = the source operand length.\n",
           (unsigned long int)max, /*vsip_vmaxval_vi(x, &j)*/
           (unsigned long int)n);
         exit(EXIT_FAILURE);
       }
    }
  }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
    /* register */ vsip_length n = x->length;
    vsip_stride cast = a->block->cstride,
                crst = r->block->cstride;
    vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                  *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset);
    vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
                  *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
    vsip_scalar_vi *xp = (x->block->array) + x->offset;
    /* register */ vsip_stride ast = (cast * a->stride),
                               rst = (crst * r->stride);
    int xinc = 0;
    while(n-- >0){
        xinc = *xp * rst;
       *(rpr + xinc) = *apr;
       *(rpi + xinc) = *api;
        apr += ast; api += ast;
        xp += x->stride;
    }
  }
}
