/* Modified RJudd June 28, 1998 */ 
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
/* $Id: vsip_cmget_d.c,v 1.1 1999/12/04 06:32:34 judd Exp judd $ */
/* To add complex block support */
/* Modified RJudd February 15, 1999 */
/* to _d from _f for core profile */
/* vsip_cmget_d.c 
// 
// This file contains the vsip_cmget_d function definition.
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
#include<vsip_cmviewattributes_d.h>

extern void (vsip_cmcheck_valid_d)(const char*,
  const vsip_cmview_d*);
extern int (vsip_report_error)(const char*, ...);

vsip_cscalar_d (vsip_cmget_d)(
  const vsip_cmview_d* M, vsip_index i, vsip_index j) {/* M_ij */
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_d("vsip_cmget_d", M);
    }
  if (vsip_check_error(vsip_view_index_exceeds_length)) {
    vsip_length	m = vsip_cmgetcollength_d(M);
    vsip_length	n = vsip_cmgetrowlength_d(M);
    if (m <= i) {
      vsip_report_error("In function vsip_cmget_d,\n"
	"columns = %lu <= %lu = column index.\n",
	(unsigned long int)n, (unsigned long int)j);
      exit(EXIT_FAILURE);
      }
    if (n <= j) {
      vsip_report_error("In function vsip_cmget_d,\n"
	"rows = %lu <= %lu = row index.\n",
	(unsigned long int)m, (unsigned long int)i);
      exit(EXIT_FAILURE);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    vsip_cblock_d*	b = M->block;
    vsip_offset	offset = (M->offset + i * M->col_stride + j * M->row_stride) * b->cstride;
    return vsip_cmplx_d(b->R->array[offset], b->I->array[offset]);
  }
}


