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
/* $Id: vsip_mcopy_d_d.c,v 1.1 1999/12/04 06:29:10 judd Exp judd $ */
/* 1,2 to row,col */
/* vsip_mcopy_d_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mcopy_d_d function definition.
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
#include<vsip_mviewattributes_d.h>

extern void (vsip_mcheck_valid_d)(const char*,
  const vsip_mview_d*);
extern void (vsip_mcheck_valid_d)(const char*,
  const vsip_mview_d*);

extern int (vsip_report_error)(const char*, ...);
extern vsip_length (vsip_mgetrowlength_d)(const vsip_mview_d*);
extern vsip_length (vsip_mgetcollength_d)(const vsip_mview_d*);
extern vsip_vview_d* (vsip_mrowview_d)(
  const vsip_mview_d*, vsip_index);
extern vsip_block_d* (vsip_vdestroy_d)(vsip_vview_d*);

void (vsip_mcopy_d_d)(
  const vsip_mview_d* A,
  const vsip_mview_d* R) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_mcheck_valid_d("vsip_mcopy_d_d", A);
    vsip_mcheck_valid_d("vsip_mcopy_d_d", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_length	n2_R = vsip_mgetcollength_d(R);
    vsip_length	n1_R = vsip_mgetrowlength_d(R);
    if (0 < n1_R) {
      vsip_length	n1_A = vsip_mgetrowlength_d(A);
      if (0 < n1_A) {
	if (n1_A != n1_R) { /* Both operands must have equal columns.	*/
	  vsip_report_error("In function vsip_mcopy_d_d,\n"
	    "operand #1 columns = %lu != %lu = operand #2 columns.\n",
	    (unsigned long int)n1_A, (unsigned long int)n1_R);
	  exit(EXIT_FAILURE);
	  }
	}
      else {				/* 0 == n1_A			*/
	vsip_report_error("In function vsip_mcopy_d_d, "
	  "operand #1 has no columns.\n");
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n1_R			*/
      vsip_report_error("In function vsip_mcopy_d_d, "
	"operand #2 has no columns.\n");
      exit(EXIT_FAILURE);
      }
    if (0 < n2_R) {
      vsip_length	n2_A = vsip_mgetcollength_d(A);
      if (0 < n2_A) {
	if (n2_A != n2_R) { /* Both operands must have equal rows.	*/
	  vsip_report_error("In function vsip_mcopy_d_d,\n"
	    "operand #1 rows = %lu != %lu = operand #2 rows.\n",
	    (unsigned long int)n2_A, (unsigned long int)n2_R);
	  exit(EXIT_FAILURE);
	  }
	}
      else {				/* 0 == n2_A			*/
	vsip_report_error("In function vsip_mcopy_d_d, "
	  "operand #1 has no rows.\n");
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n2_R			*/
      vsip_report_error("In function vsip_mcopy_d_d, "
	"operand #2 has no rows.\n");
      exit(EXIT_FAILURE);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
    {
    vsip_length	m = R->col_length;
    vsip_index	i = 0;
    vsip_vview_d a;
    vsip_vview_d r;
    (&a)->block  = A->block;
    (&a)->offset = A->offset;
    (&a)->stride = A->row_stride;
    (&a)->length = A->row_length;
    (&r)->block  = R->block;
    (&r)->offset = R->offset;
    (&r)->stride = R->row_stride;
    (&r)->length = R->row_length;
#ifdef VSIP_DEVELOPMENT_MODE
    (&a)->markings = vsip_valid_structure_object;
    (&r)->markings = vsip_valid_structure_object;
#endif /* VSIP_DEVELOPMENT_MODE */
    for (i = 0; i < m; i++) {
      vsip_vcopy_d_d(&a, &r);
      (&a)->offset += A->col_stride;
      (&r)->offset += R->col_stride;
      }
    }
  }
