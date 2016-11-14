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
/* $Id: vsip_cmcopy_d_d.c,v 1.1 1999/12/04 06:29:08 judd Exp judd $ */
/* To add complex block support */
/* vsip_cmcopy_d_d.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cmcopy_d_d function definition.
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
#include<vsip_cvviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>

extern void (vsip_cmcheck_valid_d)(const char*,
  const vsip_cmview_d*);
extern void (vsip_cmcheck_valid_d)(const char*,
  const vsip_cmview_d*);

extern int (vsip_report_error)(const char*, ...);
extern vsip_length (vsip_cmgetrowlength_d)(const vsip_cmview_d*);
extern vsip_length (vsip_cmgetcollength_d)(const vsip_cmview_d*);
extern vsip_cvview_d* (vsip_cmrowview_d)(
  const vsip_cmview_d*, vsip_index);
extern vsip_cblock_d* (vsip_cvdestroy_d)(vsip_cvview_d*);

void (vsip_cmcopy_d_d)(
  const vsip_cmview_d* A,
  const vsip_cmview_d* R) {
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cmcheck_valid_d("vsip_cmcopy_d_d", A);
    vsip_cmcheck_valid_d("vsip_cmcopy_d_d", R);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_length	n2_R = vsip_cmgetcollength_d(R);
    vsip_length	n1_R = vsip_cmgetrowlength_d(R);
    if (0 < n1_R) {
      vsip_length	n1_A = vsip_cmgetrowlength_d(A);
      if (0 < n1_A) {
	if (n1_A != n1_R) { /* Both operands must have equal columns.	*/
	  vsip_report_error("In function vsip_cmcopy_d_d,\n"
	    "operand #1 columns = %lu != %lu = operand #2 columns.\n",
	    (unsigned long int)n1_A, (unsigned long int)n1_R);
	  exit(EXIT_FAILURE);
	  }
	}
      else {				/* 0 == n1_A			*/
	vsip_report_error("In function vsip_cmcopy_d_d, "
	  "operand #1 has no columns.\n");
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n1_R			*/
      vsip_report_error("In function vsip_cmcopy_d_d, "
	"operand #2 has no columns.\n");
      exit(EXIT_FAILURE);
      }
    if (0 < n2_R) {
      vsip_length	n2_A = vsip_cmgetcollength_d(A);
      if (0 < n2_A) {
	if (n2_A != n2_R) { /* Both operands must have equal rows.	*/
	  vsip_report_error("In function vsip_cmcopy_d_d,\n"
	    "operand #1 rows = %lu != %lu = operand #2 rows.\n",
	    (unsigned long int)n2_A, (unsigned long int)n2_R);
	  exit(EXIT_FAILURE);
	  }
	}
      else {				/* 0 == n2_A			*/
	vsip_report_error("In function vsip_cmcopy_d_d, "
	  "operand #1 has no rows.\n");
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n2_R			*/
      vsip_report_error("In function vsip_cmcopy_d_d, "
	"operand #2 has no rows.\n");
      exit(EXIT_FAILURE);
      }
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
    vsip_length	m = R->col_length;
    vsip_index	i = 0;
    vsip_cvview_d a, r;
    (&a)->block    = A->block;
    (&a)->offset   = A->offset;
    (&a)->length   = A->row_length;
    (&a)->stride   = A->row_stride;
    (&r)->block    = R->block;
    (&r)->offset   = R->offset;
    (&r)->length   = R->row_length;
    (&r)->stride   = R->row_stride;
#ifdef VSIP_DEVELOPMENT_MODE
    (&a)->markings = A->markings;
    (&r)->markings = R->markings;
#endif /* VSIP_DEVELOPMENT_MODE */
    for (i = 0; i < m; i++) {
      vsip_cvcopy_d_d(&a, &r);
      (&a)->offset += A->col_stride;
      (&r)->offset += R->col_stride;
    }
  }
}
