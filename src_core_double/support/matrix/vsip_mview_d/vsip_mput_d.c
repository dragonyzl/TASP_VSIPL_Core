/* Modified RJudd April 20, 1998 */
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
/* $Id: vsip_mput_d.c,v 1.1 1999/12/04 06:30:39 judd Exp judd $ */
/* 1,2 to row,col */
/* Modified RJudd July 14, 1998 */
/* to add attributes support */
/* Modified RJudd January 1, 1999 */
/* to add real block stride */
/* Modified RJudd February 15, 1999 */
/* to _d from _f for core profile */
/* vsip_mput_d.c
// 
// This file contains the vsip_mput_d function definition.
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
#include<vsip_mviewattributes_d.h>

extern void (vsip_mcheck_valid_d)(const char*,
  const vsip_mview_d*);
extern int (vsip_report_error)(const char*, ...);

void (vsip_mput_d)(const vsip_mview_d *M,
  vsip_index i, vsip_index j, vsip_scalar_d zeta) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_d("vsip_mput_d", M);
    }
  if (vsip_check_error(vsip_view_index_exceeds_length)) {
    vsip_length	m = vsip_mgetcollength_d(M);
    vsip_length	n = vsip_mgetrowlength_d(M);
    if (m <= i) {
      vsip_report_error("In function vsip_mput_d,\n"
	"columns = %lu <= %lu = column -1.\n",
	(unsigned long int)n, (unsigned long int)j);
      exit(EXIT_FAILURE);
      }
    if (n <= j) {
      vsip_report_error("In function vsip_mput_d,\n"
	"rows = %lu <= %lu = row -1.\n",
	(unsigned long int)m, (unsigned long int)i);
      exit(EXIT_FAILURE);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    vsip_block_d    *b = M->block;
    vsip_offset	offset = (M->offset + i * M->col_stride + j * M->row_stride) * b->rstride;
    b->array[offset] = zeta;
  }
}

