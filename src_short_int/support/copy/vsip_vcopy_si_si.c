/* Modified RJudd July 27, 1998 */
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
/* $Id: vsip_vcopy_si_si.c,v 1.1 1999/12/05 16:21:31 judd Exp judd $ */
/* to include attributes support */
/* vsip_vcopy_si_si.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vcopy_si_si function definition.
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

extern int (vsip_report_error)(const char*, ...);

void (vsip_vcopy_si_si)(
  const vsip_vview_si* a,
  const vsip_vview_si* r) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_si("vsip_vcopy_si_si", a);
    vsip_vcheck_valid_si("vsip_vcopy_si_si", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_length	n_r = r->length;
    if (0 < n_r) {
      vsip_length	n_a = a->length;
      if (0 < n_a) {
	if (n_a != n_r) { /* Both operands must have the same length. */
	  vsip_report_error("In function vsip_vcopy_si_si,\n"
	    "operand #1 length = %lu != %lu = operand #2 length.\n",
	    (unsigned long int)n_a, (unsigned long int)n_r);
	  exit(EXIT_FAILURE);
	  }
	}
      else {				/* 0 == n_a			*/
	vsip_report_error("In function vsip_vcopy_si_si, "
	  "operand #1 has zero length.\n");
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n_r			*/
      vsip_report_error("In function vsip_vcopy_si_si, "
	"operand #2 has zero length.\n");
      exit(EXIT_FAILURE);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  {
      /* register */ vsip_length n   = r->length;
      /* register */ vsip_stride ast = a->stride,
                                 rst = r->stride;
      vsip_scalar_si *ap = (a->block->array) + a->offset,
                     *rp = (r->block->array) + r->offset;
      /*end define*/
      ap -= ast; rp -= rst;
      while(n-- > 0)
           *(rp += rst) = *(ap += ast);
   }
}
